#include <string>
#include <sstream>

#include "functions.h"

class character
{
public:
  std::string name;
  int hp, baseSpeed, baseAttack, accuracy, stamina, defence, speed, attack, player;
  bool guarding, preparingToDodge, prepCounterAttack, isBot, actionChosen;

  void new_character(std::string newName, int newHp, int newSpeed, int newAttack, int newDefence, int newAccuracy, int newStamina, bool initGuard = false, bool initDodge = false, bool initCounterAttack = false, bool initBot = false, bool initActionChosen = false)
  {
    name = newName;
    hp = newHp;
    baseSpeed = newSpeed;
    baseAttack = newAttack;
    defence = newDefence;
    accuracy = newAccuracy;
    stamina = newStamina;
    guarding = initGuard;
    preparingToDodge = initDodge;
    prepCounterAttack = initCounterAttack;
    isBot = initBot;
    actionChosen = initActionChosen;

  }

  bool light_attack()
  {
    int *attackPtr = &attack;
    int *speedPtr = &speed;
    int *staminaPtr = &stamina;
    if (stamina > 3)
    {
      *attackPtr = baseAttack - 5;
      *speedPtr = baseSpeed + 15;
      *staminaPtr -= 3;
      return true;
    }
    else
    {
      return false;
    }
  }

  bool heavy_attack()
  {
    int *attackPtr = &attack;
    int *speedPtr = &speed;
    int *staminaPtr = &stamina;
    if (stamina > 5)
    {
      *attackPtr = baseAttack + 10;
      *speedPtr = baseSpeed - 20;
      *staminaPtr -= 5;
      return true;
    }
    else
    {
      return false;
    }
  }

  bool dodge()
  {
    bool *dodgePtr = &preparingToDodge;
    int *speedPtr = &speed;
    int *staminaPtr = &stamina;
    if (stamina > 2)
    {
      *dodgePtr = true;
      *speedPtr = baseSpeed + 35;
      *staminaPtr -= 2;
      return true;
    }
    else
    {
      return false;
    }
  }

  void guard()
  {
    bool *guardPtr = &guarding;
    *guardPtr = true;
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
    } else {
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
      if (attacker.attack != 0)
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
    *attackPtr = 0;
    *speedPtr = 0;
    *dodgePtr = false;
    *guardPtr = false;
    *counterPtr = false;
    *actionChosenPtr = false;
  }

  void increaseStamina()
  {
    int *staminaPtr = &stamina;
    stamina += 1;
  }
};