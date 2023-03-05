#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "characters.h"

// To compile:
//  g++ -I C:\Users\edwar\Documents\codeProjects\C++\SFML-2.5.1\include -c main.cpp -o main.o
//  g++ -L C:\Users\edwar\Documents\codeProjects\C++\SFML-2.5.1\lib .\main.o -o game.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

int main()
{
  bool enoughStamina;
  bool victory = false;
  bool player2Bot = false;
  bool menu = true;
  std::vector<character> combatants, characters;
  std::vector<std::string> players;
  std::string choicePlayer1, choicePlayer2, outcome;
  int action;

  sf::RenderWindow window(sf::VideoMode(1600, 800), "Battle Game");

  sf::Event event;

  sf::Sprite botSprite, background;
  sf::Texture botIcon, backgroundTexture;
  if (!backgroundTexture.loadFromFile("assets/background.png"))
  {
    std::cout << " background texture didnt load";
    return 0;
  };
  background.setTexture(backgroundTexture);
  background.setPosition(0, 0);
  background.scale(sf::Vector2f(2.2, 2.2));

  if (!botIcon.loadFromFile("assets/bot.png"))
  {
    std::cout << " bot texture didnt load";
    return 0;
  };

  botSprite.setTexture(botIcon);
  botSprite.setPosition(sf::Vector2f(1450.f, 200.f));
  botSprite.scale(sf::Vector2f(0.5, 0.5));

  sf::Font font;
  if (!font.loadFromFile("assets/8bitOperatorPlus8-Regular.ttf"))
  {
    std::cout << "Error loading font\n";
    return 0;
  }

  // Start Game.
  while (window.isOpen())
  {
    while (menu)
    {
      // Draw character icons on the menu.
      characters = initCharacters();
      window.clear();
      window.draw(background);
      for (int i = 0; i < characters.size(); i++)
      {
        if (!characters[i].texture.loadFromFile(characters[i].texturePath))
        {
          std::cout << "a character icon texture didnt load";
          return 0;
        };
        characters[i].sprite.setTexture(characters[i].texture);
        characters[i].sprite.scale(sf::Vector2f(0.125, 0.125));
        characters[i].sprite.setPosition(sf::Vector2f(i * 200 + 10.f, 200.f));
        window.draw(characters[i].sprite);
      }
      window.draw(botSprite);

      combatants = {};

      std::cout << "Player1, Choose your character:\n";

      std::cin >> choicePlayer1;

      std::cout << "Player2, Choose your character:\n";

      std::cin >> choicePlayer2;

      while (window.pollEvent(event))
      {

        if (event.type == sf::Event::Closed)
        {
          window.close();
          menu = false;
        }
      }

      window.display();
    }

    // Menu closes. Character choices are prepared for the game.

    if (choicePlayer2 == "bot")
    {
      player2Bot = true;
      choicePlayer2 = characters[bot(1)].name;
      std::cout << "bot chooses " << choicePlayer2 << "\n";
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

    // std::cout << "\nBegin!\n";

    // while (victory != true)
    // {
    //   for (int i = 0; i < 2; i++)
    //   {
    //     while (!combatants[i].actionChosen)
    //     {
    //       if (combatants[i].isBot)
    //       {
    //         std::cout << combatants[i].name << " (CPU) chooses...\n";
    //         action = bot(2);
    //       }
    //       else
    //       {
    //         std::cout << "Player " << i + 1 << ": Choose action...\n";
    //         std::cin >> action;
    //       }

    //       switch (action)
    //       {
    //       case 1:
    //         enoughStamina = combatants[i].light_attack();
    //         if (enoughStamina)
    //         {
    //           std::cout << "Light Attack\n\n";
    //           combatants[i].actionChosen = true;
    //           break;
    //         }
    //         else
    //         {
    //           std::cout << "Not enough stamina\n";
    //           break;
    //         }
    //       case 2:
    //         enoughStamina = combatants[i].heavy_attack();
    //         if (enoughStamina)
    //         {
    //           std::cout << "Heavy Attack\n\n";
    //           combatants[i].actionChosen = true;
    //           break;
    //         }
    //         else
    //         {
    //           std::cout << "Not enough stamina\n";
    //           break;
    //         }
    //       case 3:
    //         enoughStamina = combatants[i].dodge();
    //         if (enoughStamina)
    //         {
    //           std::cout << "Dodge\n\n";
    //           combatants[i].actionChosen = true;
    //           break;
    //         }
    //         else
    //         {
    //           std::cout << "Not enough stamina\n";
    //           break;
    //         }

    //       case 4:
    //         combatants[i].guard();
    //         std::cout << "Guard\n\n";
    //         combatants[i].actionChosen = true;
    //         break;
    //       default:
    //         combatants[i].resetTempStats();
    //         std::cout << "Do nothing\n\n";
    //         combatants[i].actionChosen = true;
    //         break;
    //       }
    //     }
    //   }
    //   // Actions are applied. Whoever has the highest
    //   // speed goes first.
    //   if (combatants[0].speed > combatants[1].speed)
    //   {
    //     for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
    //     {
    //       outcome = combatants[n].applyAction(combatants[m]);
    //       std::cout << outcome + "\n";
    //       Sleep(2);
    //     }
    //   }
    //   else
    //   {
    //     for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
    //     {
    //       outcome = combatants[m].applyAction(combatants[n]);
    //       std::cout << outcome + "\n";
    //       Sleep(2);
    //     }
    //   }

    //   // Counter attacks are applied if there are any.
    //   for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
    //   {
    //     if (combatants[m].prepCounterAttack)
    //     {
    //       outcome = combatants[n].receiveCounterAttack(combatants[m]);
    //       std::cout << outcome + "\n";
    //     }
    //   }

    //   // Reset the action dependant stats after every turn
    //   // and regain stamina.
    //   for (int n = 0; n < 2; n++)
    //   {
    //     combatants[n].resetTempStats();
    //     combatants[n].increaseStamina();
    //   }

    //   std::cout << "========================================\n";
    //   std::cout << "Name: " << combatants[0].name << " // HP: " << combatants[0].hp << " // Stamina: " << combatants[0].stamina << "\n";
    //   std::cout << "Name: " << combatants[1].name << " // HP: " << combatants[1].hp << " // Stamina: " << combatants[1].stamina << "\n";
    //   std::cout << "========================================\n";

    //   for (int m = 0; m < 2; m++)
    //   {
    //     if (combatants[m].hp <= 0)
    //     {
    //       victory = true;
    //     }
    //   }
    // }
  }
  return 0;
}