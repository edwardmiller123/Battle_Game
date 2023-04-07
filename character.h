#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "functions.h"

class character
{
public:
  std::string name, texturePath, currentAction, testTexturePathR;
  int hp, baseSpeed, baseAttack, accuracy, stamina, defence, speed, attack, player, startPlace;
  sf::Vector2f currentPosition;
  bool guarding, preparingToDodge, prepCounterAttack, isBot, actionChosen, animating, doingAction;
  sf::Sprite sprite;
  sf::Texture texture;
  sf::Rect<int> defaultRectR, defaultRectL, lightAttackRectR, lightAttackRectL, heavyAttackRectR, heavyAttackRectL, guardRectR, guardRectL;

  void new_character(std::string newName, int newHp, int newBaseSpeed, int newBaseAttack, int newDefence, int newAccuracy, int newStamina, std::string newTexturePath,
                     sf::Rect<int> newDefaultRectR, sf::Rect<int> newDefaultRectL, sf::Rect<int> newLightAttackRectR, sf::Rect<int> newLightAttackRectL,
                     sf::Rect<int> newHeavyAttackRectR, sf::Rect<int> newHeavyAttackRectL, sf::Rect<int> newGuardRectR, sf::Rect<int> newGuardRectL,
                     bool initGuard = false, bool initDodge = false, bool initCounterAttack = false, bool initBot = false, bool initActionChosen = false,
                     std::string initCurrentAction = "", int newAttack = 0, int newSpeed = 0)
  {
    name = newName;
    hp = newHp;
    baseSpeed = newBaseSpeed;
    baseAttack = newBaseAttack;
    speed = newSpeed;
    attack = newAttack;
    defence = newDefence;
    accuracy = newAccuracy;
    stamina = newStamina;
    texturePath = newTexturePath;
    defaultRectR = newDefaultRectR;
    defaultRectL = newDefaultRectL;
    lightAttackRectR = newLightAttackRectR;
    lightAttackRectL = newLightAttackRectL;
    heavyAttackRectR = newHeavyAttackRectR;
    heavyAttackRectL = newHeavyAttackRectL;
    guardRectR = newGuardRectR;
    guardRectL = newGuardRectL;
    guarding = initGuard;
    preparingToDodge = initDodge;
    prepCounterAttack = initCounterAttack;
    isBot = initBot;
    actionChosen = initActionChosen;
    currentAction = initCurrentAction;
  }

  std::string displayStats()
  {
    return "HP: " + std::to_string(hp) + "\n" +
           "Atk: " + std::to_string(baseAttack) + "\n" +
           "Def: " + std::to_string(defence) + "\n" +
           "Sp: " + std::to_string(baseSpeed) + "\n" +
           "Acc: " + std::to_string(accuracy) + "\n";
    "Stm: " + std::to_string(stamina) + "\n";
  }

  std::string displayCurrentStats()
  {
    return name + " \n" + "HP: " + std::to_string(hp) + " \n" +
           "STM: " + std::to_string(stamina) + " \n" +
           currentAction + " \n";
  }

  bool light_attack()
  {
    int *attackPtr = &attack;
    int *speedPtr = &speed;
    int *staminaPtr = &stamina;
    bool *actionChosenPtr = &actionChosen;
    std::string *currentActionPtr = &currentAction;
    if (stamina > 3)
    {
      *attackPtr = baseAttack - 5;
      *speedPtr = baseSpeed + 15;
      *staminaPtr -= 3;
      *currentActionPtr = "Light Attack";
      *actionChosenPtr = true;
      return true;
    }
    else
    {
      *actionChosenPtr = false;
      return false;
    }
  }

  bool heavy_attack()
  {
    int *attackPtr = &attack;
    int *speedPtr = &speed;
    int *staminaPtr = &stamina;
    bool *actionChosenPtr = &actionChosen;
    std::string *currentActionPtr = &currentAction;
    if (stamina > 5)
    {
      *attackPtr = baseAttack + 10;
      *speedPtr = baseSpeed - 20;
      *staminaPtr -= 5;
      *currentActionPtr = "Heavy Attack";
      *actionChosenPtr = true;
      return true;
    }
    else
    {
      *actionChosenPtr = false;
      return false;
    }
  }

  bool dodge()
  {
    bool *dodgePtr = &preparingToDodge;
    int *speedPtr = &speed;
    int *staminaPtr = &stamina;
    bool *actionChosenPtr = &actionChosen;
    std::string *currentActionPtr = &currentAction;
    if (stamina > 2)
    {
      *dodgePtr = true;
      *speedPtr = baseSpeed + 15;
      *staminaPtr -= 2;
      *currentActionPtr = "Dodge";
      *actionChosenPtr = true;
      return true;
    }
    else
    {
      *actionChosenPtr = true;
      return false;
    }
  }

  void guard()
  {
    std::string *currentActionPtr = &currentAction;
    bool *guardPtr = &guarding;
    bool *actionChosenPtr = &actionChosen;
    *guardPtr = true;
    *currentActionPtr = "Guard";
    *actionChosenPtr = true;
  }

  std::string receiveCounterAttack(character attacker)
  {
    int *hpPtr = &hp;
    int damage = attacker.baseAttack + 20;
    std::string outcome;
    if (actionSucceeds(attacker.speed) && actionSucceeds(attacker.accuracy))
    {
      *hpPtr = hp - damage;
      outcome = attacker.name + " successfully counter attacked.\n";
    }
    else
    {
      outcome = attacker.name + " attempted to counter attack but failed.\n";
    }
    return outcome;
  }

  std::string
  applyAction(character attacker)
  {
    std::string eventDescription;
    bool *dodgePtr = &preparingToDodge;
    bool *guardPtr = &guarding;
    bool *counterAttackPtr = &prepCounterAttack;
    int *hpPtr = &hp;

    if (preparingToDodge)
    {
      if (actionSucceeds(speed))
      {
        if (!attacker.preparingToDodge)
        {
          eventDescription = "\n" + name + " evaded " + attacker.name + "\'s attack.\n";
        }
        else
        {
          eventDescription = "\n" + name + " dodged.\n";
        }
        *counterAttackPtr = true;
      }
      else
      {
        *dodgePtr = false;
        eventDescription = "\n" + name + " attempted to dodge but failed.\n";
      }
    }
    else if (guarding)
    {
      if (actionSucceeds(defence))
      {
        eventDescription = "\n" + name + " guarded against " + attacker.name + "\'s attack.\n";
      }
      else
      {
        *guardPtr = false;
        eventDescription = "\n" + name + " attempted to guard but failed.\n";
      }
    }
    if (!preparingToDodge && !guarding)
    {
      if (attacker.attack > 0)
      {
        if (actionSucceeds(attacker.accuracy))
        {
          *hpPtr = hp - attacker.attack;
          eventDescription += "\n" + attacker.name + " hit " + name + " for " + std::to_string(attacker.attack) + " Hp.\n";
        }
        else
        {
          eventDescription += "\n" + attacker.name + "\'s attack missed.\n";
        }
      }
    }
    return eventDescription;
  }

  void resetTempStats()
  {
    int *attackPtr = &attack;
    int *speedPtr = &speed;
    bool *dodgePtr = &preparingToDodge;
    bool *guardPtr = &guarding;
    bool *counterPtr = &prepCounterAttack;
    bool *actionChosenPtr = &actionChosen;
    std::string *currentActionPtr = &currentAction;
    *attackPtr = 0;
    *speedPtr = 0;
    *dodgePtr = false;
    *guardPtr = false;
    *counterPtr = false;
    *actionChosenPtr = false;
    *currentActionPtr = "";

    // Reset start positions
    float x;
    switch (startPlace)
    {
    case 0:
      x = 400;
      sprite.setTextureRect(defaultRectL);
      break;
    case 1:
      x = 1000;
      sprite.setTextureRect(defaultRectR);
    }
    sprite.setPosition(sf::Vector2f(x, 500.f));
  }

  bool exitState()
  {
    bool *actionChosenPtr = &actionChosen;
    bool *animatingPtr = &animating;
    *actionChosenPtr = true;
    *animatingPtr = false;
    return true;
  }

  void increaseStamina()
  {
    int *staminaPtr = &stamina;
    *staminaPtr += 1;
  }

  void animateCharacter(actionTracker tracker, sf::Sprite opponentSprite, sf::Time timeElapsed)
  {
    sf::Vector2f *currentPositionPtr = &currentPosition;
    bool *animatingPtr = &animating;
    bool *doingActionPtr = &doingAction;
    float shiftX;
    *currentPositionPtr = sprite.getPosition();

    switch (startPlace)
    {
    case 0:
      shiftX = speed / 20;
      break;
    case 1:
      shiftX = -(speed / 20);
    }

    if (!doingAction)
    {
      sprite.move(shiftX, 0);
      if (sprite.getGlobalBounds().intersects(opponentSprite.getGlobalBounds()))
      {
        *doingActionPtr = true;
      }
    }

    if (doingAction)
    {
      if (tracker.action == "Light Attack" || tracker.action == "Counter")
      {
        switch (startPlace)
        {
        case 0:
          sprite.setTextureRect(lightAttackRectL);
          break;
        case 1:
          sprite.setTextureRect(lightAttackRectR);
          break;
        }
      }
      else if (tracker.action == "Heavy Attack")
      {
        if (name == "BigBoi")
        {
          // The heavy attack texture is too tall so here is a janky fix.
          sprite.setPosition(sf::Vector2f(currentPosition.x, 380.f));
        }
        switch (startPlace)
        {
        case 0:
          sprite.setTextureRect(heavyAttackRectL);
          break;
        case 1:
          sprite.setTextureRect(heavyAttackRectR);
          break;
        }
      }
      else if (tracker.action == "Dodge")
      {
        // To prevent from dodging off the screen.
        if (currentPosition.x < 1400.f && currentPosition.x > 200.f)
        {
          sprite.move(-shiftX, 0);
        }
      }
      else if (tracker.action == "Guard")
      {
        switch (startPlace)
        {
        case 0:
          sprite.setTextureRect(guardRectL);
          break;
        case 1:
          sprite.setTextureRect(guardRectR);
          break;
        }
      }
    }
    if (timeElapsed > sf::milliseconds(3000))
    {
      *animatingPtr = false;
      *doingActionPtr = false;
    }
  }
};
