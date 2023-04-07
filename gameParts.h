#include "characters.h"

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