#include <iostream>
#include <windows.h>
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
  std::string outcome;
  int action;
  int animationCounter = 0;
  int player = 1;
  std::string displayString;
  std::vector<actionCard> actionCards;
  std::vector<struct actionTracker> actionRecord;

  sf::RenderWindow window(sf::VideoMode(1600, 800), "Battle Game");
  sf::Event event;

  sf::Sprite botSprite, background;
  sf::Texture botIcon, backgroundTexture;
  if (!backgroundTexture.loadFromFile("assets/arena_edit_2.png"))
  {
    std::cout << " background texture didnt load";
    return 0;
  };
  background.setTexture(backgroundTexture);
  background.setPosition(0, 0);

  if (!botIcon.loadFromFile("assets/bot.png"))
  {
    std::cout << "Error loading bot icon";
    return 0;
  };

  botSprite.setTexture(botIcon);
  botSprite.setPosition(sf::Vector2f(1450.f, 500.f));
  botSprite.scale(sf::Vector2f(0.5, 0.5));

  sf::Font font;
  sf::Text text, stats1, stats2, infoText;
  if (!font.loadFromFile("assets/8bitOperatorPlus8-Regular.ttf"))
  {
    std::cout << "Error loading font\n";
    return 0;
  }
  text.setFont(font);
  text.setCharacterSize(50);
  text.setOutlineColor(sf::Color::Black);
  text.setOutlineThickness(4);
  text.setFillColor(sf::Color::Magenta);
  text.setPosition(sf::Vector2f(350.f, 200.f));

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
        characters[i].sprite.scale(sf::Vector2f(0.25, 0.25));
        characters[i].sprite.setPosition(sf::Vector2f(i * 200 + 275.f, 475.f));
        window.draw(characters[i].sprite);
      }
      if (player == 2)
      {
        window.draw(botSprite);
      }

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
              player2Bot = true;
              players.push_back(characters[bot(1)].name);
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

    std::string stats1String, stats2String, infoTextString;

    infoText.setFont(font);
    infoText.setCharacterSize(30);
    infoText.setFillColor(sf::Color::Magenta);
    infoText.setOutlineColor(sf::Color::Black);
    infoText.setOutlineThickness(4);
    infoText.setPosition(sf::Vector2f(550.f, 100.f));

    stats1.setFont(font);
    stats1.setCharacterSize(25);
    stats1.setFillColor(sf::Color::Magenta);
    stats1.setOutlineColor(sf::Color::Black);
    stats1.setOutlineThickness(4);
    stats1.setPosition(sf::Vector2f(10.f, 0.f));

    stats2.setFont(font);
    stats2.setCharacterSize(25);
    stats2.setFillColor(sf::Color::Magenta);
    stats2.setOutlineColor(sf::Color::Black);
    stats2.setOutlineThickness(4);
    stats2.setPosition(sf::Vector2f(1390.f, 0.f));

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

    // draw combatants default positions
    for (int l = 0; l < 2; l++)
    {
      if (!combatants[l].texture.loadFromFile(combatants[l].texturePath))
      {
        std::cout << "a character icon texture didnt load";
        return 0;
      };
      combatants[l].sprite.setTexture(combatants[l].texture);
      float x;
      switch (l)
      {
      case 0:
        x = 400;
        break;
      case 1:
        x = 1000;
        break;
      };
      // Keeps track of which side the character starts on as a 0 or 1.
      combatants[l].startPlace = l;
      combatants[l].sprite.setPosition(sf::Vector2f(x, 500.f));
    }

    int counter = 0;
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(650.f, 225.f));
    text.setString("\nBegin!\n");
    if (!victory && !menu)
    {
      while (counter <= 500)
      {
        window.clear();
        window.draw(text);
        window.display();
        counter++;
      }
    }
    // Apply action Loop
    while (!victory)
    {
      stats1String = combatants[0].name + " \n" + "HP: " + std::to_string(combatants[0].hp) + " \n" + "STM: " + std::to_string(combatants[0].stamina) + " \n" + combatants[0].currentAction + " \n";
      stats1.setString(stats1String);
      stats2String = combatants[1].name + " \n" + "HP: " + std::to_string(combatants[1].hp) + " \n" + "STM: " + std::to_string(combatants[1].stamina) + " \n" + combatants[1].currentAction + " \n";
      stats2.setString(stats2String);

      for (int i = 0; i < 2; i++)
      {
        // This ensures the correct stamina message is displayed each turn.
        enoughStamina = true;

        // Choose action loop
        while (!combatants[i].actionChosen)
        {
          window.clear();
          window.draw(background);
          window.draw(stats1);
          window.draw(stats2);
          for (int l = 0; l < 2; l++)
          {
            window.draw(combatants[l].sprite);
          }

          for (int m = 0; m < actionCards.size(); m++)
          {
            window.draw(actionCards[m].sprite);
          }

          if (enoughStamina)
          {
            if (combatants[i].isBot)
            {
              infoTextString = combatants[i].name + " (CPU) chooses...\n";
              action = bot(2);
            }
            else
            {
              infoTextString = "Player " + std::to_string(i + 1) + " : Choose action...\n";
            }
          }

          infoText.setString(infoTextString);
          window.draw(infoText);
          window.display();

          if (combatants[i].isBot)
          {
            // Slows the bots choices a bit
            Sleep(2000);
          }

          switch (action)
          {
          case 1:
            enoughStamina = combatants[i].light_attack();
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
            enoughStamina = combatants[i].heavy_attack();
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
            enoughStamina = combatants[i].dodge();
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
            combatants[i].guard();
            break;
          default:
            break;
          }

          action = 0;

          while (window.pollEvent(event))
          {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            switch (event.type)
            {
            case sf::Event::Closed:
              victory = true;
              menu = false;
              combatants[0].actionChosen = true;
              combatants[1].actionChosen = true;
              window.close();
              break;
            case sf::Event::MouseButtonPressed:
              if (event.mouseButton.button == sf::Mouse::Left)
              {
                for (int j = 0; j < actionCards.size(); j++)
                {
                  if (actionCards[j].sprite.getGlobalBounds().contains(mousePosition))
                  {
                    action = actionCards[j].actionNumber;
                  }
                }
              }
              break;
            case sf::Event::MouseMoved:
              for (int j = 0; j < actionCards.size(); j++)
              {
                if (actionCards[j].sprite.getGlobalBounds().contains(mousePosition))
                {
                  if (!actionCards[j].texture.loadFromFile(actionCards[j].selectedTexturePath))
                  {
                    std::cout << "Error loading selected action card" + std::to_string(j) + "\n";
                    return 0;
                  };
                }
                else
                {
                  if (!actionCards[j].texture.loadFromFile(actionCards[j].texturePath))
                  {
                    std::cout << "Error loading action card" + std::to_string(j) + "\n";
                    return 0;
                  };
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
        struct actionTracker tracker;
        if (combatants[0].speed > combatants[1].speed)
        {
          for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
          {
            outcome = combatants[n].applyAction(combatants[m]);
            tracker.name = combatants[n].name;
            tracker.action = combatants[n].currentAction;
            actionRecord.push_back(tracker);
          }
        }
        else
        {
          for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
          {
            outcome = combatants[m].applyAction(combatants[n]);
            tracker.name = combatants[n].name;
            tracker.action = combatants[n].currentAction;
            actionRecord.push_back(tracker);
          }
        }

        // Counter attacks are applied if there are any.
        for (int m = 0, n = 1; m <= 1, n >= 0; m++, n--)
        {
          if (combatants[m].prepCounterAttack)
          {
            outcome += combatants[n].receiveCounterAttack(combatants[m]);
            tracker.name = combatants[m].name;
            tracker.action = "counter";
            actionRecord.push_back(tracker);
          }
        }
      }

      // Character animations
      infoText.setString(outcome);
      int animationFrame = 0;
      sf::Sprite opponentSprite;
      for (int k = 0; k < actionRecord.size(); k++)
      {
        for (int j = 0; j < combatants.size(); j++)
        {
          if (combatants[j].name == actionRecord[k].name)
          {
            combatants[j].animating = true;

            // Locate opponent sprite

            for (int m = 0; m < 2; m++)
            {
              if (combatants[j].name != combatants[m].name)
              {
                opponentSprite = combatants[m].sprite;
              }
            }

            while (combatants[j].animating)
            {
              window.clear();
              window.draw(background);
              window.draw(infoText);
              combatants[j].animateCharacter(actionRecord[k], opponentSprite);
              window.draw(combatants[0].sprite);
              window.draw(combatants[1].sprite);
              window.display();
              animationFrame++;
              while (window.pollEvent(event))
              {
                switch (event.type)
                {
                case sf::Event::Closed:
                  victory = true;
                  menu = false;
                  for (int i = 0; i < 2; i++)
                  {
                    combatants[i].exitState();
                  }
                  window.close();
                  break;
                }
              }
            }
          }
        }
      }

      // Reset the action dependant stats after every turn
      // and regain stamina.

      for (int n = 0; n < 2; n++)
      {
        combatants[n].resetTempStats();
        combatants[n].increaseStamina();
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
