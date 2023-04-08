#include "characters.h"

void initCombatants(std::vector<character> &players, std::vector<character> &characters, std::vector<character> &combatants)
{
 for (int j = 0; j < players.size(); j++)
    {
      for (int i = 0; i < characters.size(); i++)
      {
        if (players[j].name == characters[i].name)
        {
          characters[i].player = j + 1;
          combatants.push_back(characters[i]);
          if (players[j].isBot)
          {
            combatants[1].isBot = true;
          }
        }
      }
    }
}

void chooseAction(int &action, bool &enoughStamina, character &combatant, std::string &infoTextString)
{
  switch (action)
  {
  case 1:
    enoughStamina = combatant.light_attack();
    if (enoughStamina)
    {
      break;
    }
    else
    {
      infoTextString = "Not enough stamina\n";
      break;
    }
  case 2:
    enoughStamina = combatant.heavy_attack();
    if (enoughStamina)
    {
      break;
    }
    else
    {
      infoTextString = "Not enough stamina\n";
      break;
    }
  case 3:
    enoughStamina = combatant.dodge();
    if (enoughStamina)
    {
      break;
    }
    else
    {
      infoTextString = "Not enough stamina\n";
      break;
    }

  case 4:
    combatant.guard();
    break;
  default:
    break;
  }

  action = 0;
}

void applyActions(std::vector<character> &combatants, actionTracker &tracker, std::vector<actionTracker> &actionRecord)
{
  // To clarify: attacker applys action to target as such
  // target.applyAction(attacker)
  if (combatants[0].speed > combatants[1].speed)
  {
    for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
    {
      tracker.outcomeString = combatants[n].applyAction(combatants[m]);
      tracker.player = combatants[m].player;
      tracker.action = combatants[m].currentAction;
      actionRecord.push_back(tracker);
    }
  }
  else
  {
    for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
    {
      tracker.outcomeString = combatants[m].applyAction(combatants[n]);
      tracker.player = combatants[n].player;
      tracker.action = combatants[n].currentAction;
      actionRecord.push_back(tracker);
    }
  }

  // Counter attacks are applied if there are any.
  for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
  {
    if (combatants[m].prepCounterAttack)
    {
      tracker.outcomeString = combatants[n].receiveCounterAttack(combatants[m]);
      tracker.player = combatants[m].player;
      tracker.action = "Counter";
      actionRecord.push_back(tracker);
    }
  }
}