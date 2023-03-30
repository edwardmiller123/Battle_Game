#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "functions.h"

class character
{
public:
  std::string name, texturePath, currentAction;
  int hp, baseSpeed, baseAttack, accuracy, stamina, defence, speed, attack, player, startPlace;
  sf::Vector2f currentPosition;
  bool guarding, preparingToDodge, prepCounterAttack, isBot, actionChosen, animating, doingAction;
  sf::Sprite sprite;
  sf::Texture texture;

  void new_character(std::string newName, int newHp, int newSpeed, int newAttack, int newDefence, int newAccuracy, int newStamina, std::string newTexturePath,
                     bool initGuard = false, bool initDodge = false, bool initCounterAttack = false, bool initBot = false, bool initActionChosen = false,
                     std::string initCurrentAction = "")
  {
    name = newName;
    hp = newHp;
    baseSpeed = newSpeed;
    baseAttack = newAttack;
    defence = newDefence;
    accuracy = newAccuracy;
    stamina = newStamina;
    texturePath = newTexturePath;
    guarding = initGuard;
    preparingToDodge = initDodge;
    prepCounterAttack = initCounterAttack;
    isBot = initBot;
    actionChosen = initActionChosen;
    currentAction = initCurrentAction;
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
      *speedPtr = baseSpeed + 35;
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
      outcome = attacker.name + " successfully counter attacked." + "\n";
    }
    else
    {
      outcome = attacker.name + " attempted to counter attack but failed.\n";
    }
    return outcome;
  }

  std::string applyAction(character attacker)
  {
    std::stringstream stream;
    std::string eventDescription, damageTakenStr;
    bool *dodgePtr = &preparingToDodge;
    bool *guardPtr = &guarding;
    bool *counterAttackPtr = &prepCounterAttack;
    int *hpPtr = &hp;

    if (preparingToDodge)
    {
      if (actionSucceeds(speed))
      {
        eventDescription = "\n" + name + " evaded " + attacker.name + "\'s attack.\n";
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
      if (attacker.attack)
      {
        if (actionSucceeds(attacker.accuracy))
        {
          *hpPtr = hp - attacker.attack;

          stream << attacker.attack;
          stream >> damageTakenStr;
          eventDescription += "\n" + attacker.name + " hit " + name + " for " + damageTakenStr + " Hp.\n";
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
      break;
    case 1:
      x = 1000;
    }
    sprite.setPosition(sf::Vector2f(x, 500.f));
  }

  void exitState()
  {
    bool *actionChosenPtr = &actionChosen;
    bool *animatingPtr = &animating;
    *actionChosenPtr = true;
    *animatingPtr = false;
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

    if (!doingAction)
    {
      switch (startPlace)
      {
      case 0:
        shiftX = speed / 15;
        break;
      case 1:
        shiftX = -(speed / 15);
      }
      sprite.move(shiftX, 0);
      if (sprite.getGlobalBounds().intersects(opponentSprite.getGlobalBounds()))
      {
        *doingActionPtr = true;
      }
    }

    if (doingAction)
    {
      // Place holders for now. Maybe make a switch later.
      if (tracker.action == "Light Attack")
      {
       std::cout << "light attack\n";
      }
      else if (tracker.action == "Heavy Attack")
      {
        std::cout << "heavy attack\n";
      }
      else if (tracker.action == "Dodge")
      {
        std::cout << "dodge\n";
      }
      else if (tracker.action == "Guard")
      {
        std::cout << "guard\n";
      }
      else if (tracker.action == "Counter")
      {
        std::cout << "counter\n";
      }
    }
    if (timeElapsed > sf::milliseconds(900))
        {
          *animatingPtr = false;
          *doingActionPtr = false;
        }
  }
};
