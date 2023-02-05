#include <iostream>
#include <random>
#include <string>
#include <vector>

class character
{
public:
  std::string name;
  int hp;
  int baseSpeed;
  int baseAttack;
  int baseDefence;
  int accuracy;
  int stamina;
  int defence;
  int speed;
  int attack;
  int player;
  bool guarding;
  bool preparingToDodge;
  bool actionCompleted;

  void new_character(std::string newName, int newHp, int newSpeed, int newAttack, int newDefence, int newAccuracy, int newStamina, bool initGuard = false, bool initDodge = false)
  {
    name = newName;
    hp = newHp;
    baseSpeed = newSpeed;
    baseAttack = newAttack;
    baseDefence = newDefence;
    accuracy = newAccuracy;
    stamina = newStamina;
    guarding = initGuard;
    preparingToDodge = initDodge;
  }

  void light_attack()
  {
    int *attackPtr = &attack;
    int *speedPtr = &speed;
    *attackPtr = baseAttack - 5;
    *speedPtr = baseSpeed + 15;
  }

  void heavy_attack()
  {
    int *attackPtr = &attack;
    int *speedPtr = &speed;
    *attackPtr = baseAttack + 10;
    *speedPtr = baseSpeed - 20;
  }

  void dodge()
  {
    bool *dodgePtr = &preparingToDodge;
    int *speedPtr = &speed;
    *dodgePtr = true;
    *speedPtr = baseSpeed + 35;
  }

  void guard()
  {
    bool *guardPtr = &guarding;
    *guardPtr = true;
  }
};

character speedy_mc_speed, big_boi, allrounder;

void resetStats(std::vector<character> combatants)
{
  for (int i = 0; i < 2; i++)
  {
    int *attackPtr = &combatants[i].attack;
    int *speedPtr = &combatants[i].speed;
    bool *dodgePtr = &combatants[i].preparingToDodge;
    *attackPtr, *speedPtr = 0;
    *dodgePtr = false;
  }
}

bool actionSucceeds(character player)
{
  int randNumber = 0 + rand() % 100;
  if (player.guarding)
  {
    if (player.defence >= randNumber)
    {
      return true;
    }
    return false;
  }
  else if (player.preparingToDodge)
  {
    if (player.speed > randNumber)
    {
      return true;
    }
  }
  if (player.accuracy > randNumber)
  {
    return true;
  }
  return false;
}

std::string calculateOutcome(std::vector<character> combatants)
{
  std::string outcomeMessage;
  std::vector<character> actionOrder;
  int damageInflicted;
  if (combatants[0].speed >= combatants[1].speed)
  {
    actionOrder.push_back(combatants[0]);
    actionOrder.push_back(combatants[1]);
  }
  else
  {
    actionOrder.push_back(combatants[1]);
    actionOrder.push_back(combatants[0]);
  }

  // First strike

  int *hpPtr2 = &actionOrder[1].hp;
  if (actionOrder[1].preparingToDodge == false && actionOrder[1].guarding == false)
  {
    if (actionSucceeds(actionOrder[0]))
    {
      *hpPtr2 = actionOrder[1].hp - actionOrder[0].attack;
      outcomeMessage = actionOrder[0].name + " hit " + actionOrder[1].name + " for " + std::to_string(actionOrder[0].attack) + " HP.\n";
    }
    else
    {
      outcomeMessage = "Attack missed\n";
    }
  }

  // Retaliation
  if (actionOrder[1].hp > 0)
  {
    int *hpPtr1 = &actionOrder[0].hp;
    if (actionOrder[0].preparingToDodge == false && actionOrder[0].guarding == false)
    {
      if (actionSucceeds(actionOrder[1]))
      {
        *hpPtr1 = actionOrder[0].hp - actionOrder[1].attack;
        outcomeMessage += actionOrder[1].name + " hit " + actionOrder[0].name + " for " + std::to_string(actionOrder[1].attack) + " HP.\n";
      }
      else
      {
        outcomeMessage = "Attack missed\n";
      }
    }
  }
  return outcomeMessage;
}

int main()
{
  speedy_mc_speed.new_character("SpeedyMcSpeed", 45, 85, 10, 60, 90, 50);
  big_boi.new_character("BigBoi", 90, 30, 20, 85, 80, 50);
  allrounder.new_character("Joe", 60, 60, 15, 75, 90, 50);

  bool victory = false;
  std::vector<character> combatants, characters;
  std::string choicePlayer1, choicePlayer2, outcome;
  int action;

  characters = {speedy_mc_speed, big_boi, allrounder};
  combatants = {};

  std::cout << "Player1, Choose your character:\n";

  std::cin >> choicePlayer1;

  std::cout << "Player2, Choose your character:\n";

  std::cin >> choicePlayer2;

  std::vector<std::string> players = {choicePlayer1, choicePlayer2};

  for (int j = 0; j < players.size(); j++)
  {
    for (int i = 0; i < characters.size(); i++)
    {
      if (players[j] == characters[i].name)
      {
        combatants.push_back(characters[i]);
        // combatants[j].player = j;
      }
    }
  }

  std::cout << "\nBegin!\n";

  while (victory != true)
  {

    resetStats(combatants);

    for (int i = 0; i < 2; i++)
    {
      std::cout << "Player " << i + 1 << ": Choose action...\n";
      std::cin >> action;

      switch (action)
      {
      case 1:
        combatants[i].light_attack();
        break;
      case 2:
        combatants[i].heavy_attack();
        break;
      case 3:
        combatants[i].dodge();
        break;
      case 4:
        combatants[i].guard();
        break;
      }
    }
    outcome = calculateOutcome(combatants);
    std::cout << "\n" << outcome << "\n";
    std::cout << "Name: "<< combatants[0].name << " HP:" << combatants[0].hp << "\n";
    std::cout << "Name: "<< combatants[1].name << " HP:" << combatants[1].hp << "\n";



    for (int m = 0; m < 2; m++)
    {
      if (combatants[m].hp <= 0)
      {
        victory = true;
      }
    }
  }
}