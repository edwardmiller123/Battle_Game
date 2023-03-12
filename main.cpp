#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "actionCard.h"
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
  std::string choicePlayer1, choicePlayer2, outcome, choice;
  int action;
  int player = 1;
  std::string displayString;
  std::vector<actionCard> actionCards;

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
    std::cout << "Error loading bot icon";
    return 0;
  };

  botSprite.setTexture(botIcon);
  botSprite.setPosition(sf::Vector2f(1450.f, 400.f));
  botSprite.scale(sf::Vector2f(0.5, 0.5));

  sf::Font font;
  sf::Text text, stats1, stats2;
  if (!font.loadFromFile("assets/8bitOperatorPlus8-Regular.ttf"))
  {
    std::cout << "Error loading font\n";
    return 0;
  }
  text.setFont(font);
  text.setCharacterSize(50);
  text.setFillColor(sf::Color::Black);
  text.setPosition(sf::Vector2f(300.f, 200.f));

  // Start Game loop.
  while (window.isOpen())
  {
    // Start Character selection menu.
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
        characters[i].sprite.setPosition(sf::Vector2f(i * 200 + 10.f, 400.f));
        window.draw(characters[i].sprite);
      }
      window.draw(botSprite);

      combatants = {};

      displayString = "Player " + std::to_string(player) + " Choose your character:\n";
      text.setString(displayString);
      window.draw(text);

      while (window.pollEvent(event))
      {

        switch (event.type)
        {
        case sf::Event::Closed:
          menu = false;
          window.close();
          break;
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left)
          {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            for (int j = 0; j < characters.size(); j++)
            {

              if (characters[j].sprite.getGlobalBounds().contains(mousePosition))
              {
                players.push_back(characters[j].name);
                player++;
              }
            }
            if (botSprite.getGlobalBounds().contains(mousePosition) && player == 2)
            {
              choicePlayer2 = "bot";
              player++;
            }
          }
          break;

        default:
          break;
        }
      }

      window.display();

      if (player == 3)
      {
        menu = false;
      }
    }
    // Menu closes. Character choices are prepared for the game.

    if (choicePlayer2 == "bot")
    {
      player2Bot = true;
      choicePlayer2 = characters[bot(1)].name;
    }

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

    std::string stats1String, stats2String;

    stats1.setFont(font);
    stats1.setCharacterSize(30);
    stats1.setFillColor(sf::Color::Black);
    stats1.setPosition(sf::Vector2f(0.f, 0.f));

    stats2.setFont(font);
    stats2.setCharacterSize(30);
    stats2.setFillColor(sf::Color::Black);
    stats2.setPosition(sf::Vector2f(1400.f, 0.f));

    actionCards = initActionCards();
    for (int n = 0; n < actionCards.size(); n++)
    {
      if (!actionCards[n].texture.loadFromFile(actionCards[n].texturePath))
      {
        std::cout << "Error loading action card" + std::to_string(n) + "\n";
        return 0;
      };
      actionCards[n].sprite.setTexture(actionCards[n].texture);
      actionCards[n].sprite.setPosition(sf::Vector2f(actionCards[n].posX, actionCards[n].posY));
      actionCards[n].sprite.scale(sf::Vector2f(actionCards[n].scaleX, actionCards[n].scaleY));
    }
    std::cout << "\nBegin!\n";
    // Apply action Loop
    while (!victory)
    {
      window.clear();
      stats1String = "Name: " + combatants[0].name + " \n" + "HP: " + std::to_string(combatants[0].hp) + " \n" + "STM: " + std::to_string(combatants[0].stamina) + " \n";
      stats1.setString(stats1String);
      stats2String = "Name: " + combatants[1].name + " \n" + "HP: " + std::to_string(combatants[1].hp) + " \n" + "STM: " + std::to_string(combatants[1].stamina) + " \n";
      stats2.setString(stats2String);
      window.draw(background);
      window.draw(stats1);
      window.draw(stats2);
      window.display();

      for (int i = 0; i < 2; i++)
      {
        // Choose action loop
        while (!combatants[i].actionChosen)
        {
          window.clear();
          window.draw(background);
          window.draw(stats1);
          window.draw(stats2);

          for (int m = 0; m < actionCards.size(); m++)
          {
            window.draw(actionCards[m].sprite);
          }

          window.display();

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
          case 5:
            combatants[i].resetTempStats();
            std::cout << "Do nothing\n\n";
            combatants[i].actionChosen = true;
            break;
          default:
            break;
          }
          action = 0;

          while (window.pollEvent(event))
          {

            switch (event.type)
            {
            case sf::Event::Closed:
              victory = false;
              menu = false;
              combatants[0].actionChosen = true;
              combatants[1].actionChosen = true;
              window.close();
              break;
            case sf::Event::MouseButtonPressed:
              if (event.mouseButton.button == sf::Mouse::Left)
              {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int j = 0; j < actionCards.size(); j++)
                {
                  if (actionCards[j].sprite.getGlobalBounds().contains(mousePosition))
                  {
                    action = actionCards[j].actionNumber;
                  }
                }
              }
              break;

            default:
              break;
            }
          }
        }
      }
      // Actions are applied. Whoever has the highest
      // speed goes first.
      if (combatants[0].actionChosen && combatants[1].actionChosen)
      {
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
      }

      for (int m = 0; m < 2; m++)
      {
        if (combatants[m].hp <= 0)
        {
          victory = true;
          window.close();
        }
      }
    }
  }
  return 0;
}