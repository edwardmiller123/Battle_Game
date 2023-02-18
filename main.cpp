#include <iostream>

#include "character.h"

character speedy_mc_speed, big_boi, joe, veryBadCharacter;

int main()
{
  speedy_mc_speed.new_character("SpeedyMcSpeed", 60, 85, 10, 50, 90, 30);
  big_boi.new_character("BigBoi", 90, 30, 20, 85, 80, 20);
  joe.new_character("Joe", 70, 60, 15, 75, 90, 25);
  veryBadCharacter.new_character("BadStats", 50, 1, 1, 1, 1, 1);

  bool enoughStamina;
  bool victory = false;
  bool player2Bot = false;
  std::vector<character> combatants, characters;
  std::vector<std::string> players;
  std::string choicePlayer1, choicePlayer2, outcome;
  int action;

  characters = {speedy_mc_speed, big_boi, joe, veryBadCharacter};
  combatants = {};

  std::cout << "Player1, Choose your character:\n";

  std::cin >> choicePlayer1;

  std::cout << "Player2, Choose your character:\n";

  std::cin >> choicePlayer2;

  if (choicePlayer2 == "bot")
  {
    player2Bot = true;
    choicePlayer2 = characters[bot(1)].name;
  }

  players = {choicePlayer1, choicePlayer2};

  for (int j = 0; j < players.size(); j++)
  {
    for (int i = 0; i < characters.size(); i++)
    {
      if (players[j] == characters[i].name)
      {
        combatants.push_back(characters[i]);
      }
    }
  }

  if (player2Bot)
  {
    combatants[1].isBot = true;
  }

  std::cout << "\nBegin!\n";

  while (victory != true)
  {
    for (int i = 0; i < 2; i++)
    {
      while (!combatants[i].actionChosen)
      {
        if (combatants[i].isBot)
        {
          std::cout << combatants[i].name << " (CPU) chooses...\n";
          action = bot(2);
        }
        else
        {
          std::cout << "Player " << i + 1 << ": Choose action...\n";
          std::cin >> action;
        }

        switch (action)
        {
        case 1:
          enoughStamina = combatants[i].light_attack();
          if (enoughStamina)
          {
            std::cout << "Light Attack\n\n";
            combatants[i].actionChosen = true;
            break;
          }
          else
          {
            std::cout << "Not enough stamina\n";
            break;
          }
        case 2:
          enoughStamina = combatants[i].heavy_attack();
          if (enoughStamina)
          {
            std::cout << "Heavy Attack\n\n";
            combatants[i].actionChosen = true;
            break;
          }
          else
          {
            std::cout << "Not enough stamina\n";
            break;
          }
        case 3:
          enoughStamina = combatants[i].dodge();
          if (enoughStamina)
          {
            std::cout << "Dodge\n\n";
            combatants[i].actionChosen = true;
            break;
          }
          else
          {
            std::cout << "Not enough stamina\n";
            break;
          }

        case 4:
          combatants[i].guard();
          std::cout << "Guard\n\n";
          combatants[i].actionChosen = true;
          break;
        default:
          combatants[i].resetTempStats();
          std::cout << "Do nothing\n\n";
          combatants[i].actionChosen = true;
          break;
        }
      }
    }
    // Actions are applied. Whoever has the highest
    // speed goes first.
    if (combatants[0].speed > combatants[1].speed)
    {
      for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
      {
        outcome = combatants[n].applyAction(combatants[m]);
        std::cout << outcome + "\n";
        Sleep(2);
      }
    }
    else
    {
      for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
      {
        outcome = combatants[m].applyAction(combatants[n]);
        std::cout << outcome + "\n";
        Sleep(2);
      }
    }

    // Counter attacks are applied if there are any.
    for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
    {
      if (combatants[m].prepCounterAttack)
      {
        outcome = combatants[n].receiveCounterAttack(combatants[m]);
        std::cout << outcome + "\n";
      }
    }

    // Reset the action dependant stats after every turn
    // and regain stamina.
    for (int n = 0; n < 2; n++)
    {
      combatants[n].resetTempStats();
      combatants[n].increaseStamina();
    }

    std::cout << "========================================\n";
    std::cout << "Name: " << combatants[0].name << " // HP: " << combatants[0].hp << " // Stamina: " << combatants[0].stamina << "\n";
    std::cout << "Name: " << combatants[1].name << " // HP: " << combatants[1].hp << " // Stamina: " << combatants[1].stamina << "\n";
    std::cout << "========================================\n";

    for (int m = 0; m < 2; m++)
    {
      if (combatants[m].hp <= 0)
      {
        victory = true;
      }
    }
  }
}