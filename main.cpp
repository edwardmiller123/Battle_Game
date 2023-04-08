#include <iostream>
#include <windows.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "actionCard.h"
#include "gameParts.h"

int main()
{
  bool enoughStamina;
  bool victory = false;
  bool player2Bot = false;
  bool menu = true;
  bool exitState, showCharacterStats;
  std::vector<character> combatants, characters, players;
  int action;
  int player = 1;
  std::string displayString;
  std::vector<actionCard> actionCards;
  actionTracker tracker;
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

  initText(text, font, 50, sf::Color::Magenta, sf::Color::Black, 4, sf::Vector2f(350.f, 200.f));

  // Start Game loop.
  while (window.isOpen())
  {
    // Start Character selection menu.
    while (menu)
    {

      // Draw character icons on the menu.
      window.clear();
      window.draw(background);
      characters = initCharacters();
      for (int i = 0; i < characters.size(); i++)
      {
        if (!characters[i].texture.loadFromFile(characters[i].texturePath))
        {
          std::cout << "a character icon texture didnt load";
          return 0;
        };
        characters[i].sprite.setTexture(characters[i].texture);
        characters[i].sprite.setTextureRect(characters[i].defaultRectR);
        characters[i].sprite.scale(sf::Vector2f(0.25, 0.25));
        characters[i].sprite.setPosition(sf::Vector2f(i * 250 + 300.f, 475.f));
        window.draw(characters[i].sprite);
      }

      if (player == 2)
      {
        window.draw(botSprite);
      }

      displayString = "Player " + std::to_string(player) + " Choose your character:\n";

      while (window.pollEvent(event))
      {
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        switch (event.type)
        {
        case sf::Event::Closed:
          menu = false;
          window.close();
          break;
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left)
          {
            for (int j = 0; j < characters.size(); j++)
            {

              if (characters[j].sprite.getGlobalBounds().contains(mousePosition))
              {
                players.push_back(characters[j]);
                player++;
              }
            }
            if (botSprite.getGlobalBounds().contains(mousePosition) && player == 2)
            {
              // player2Bot = true;
              players.push_back(characters[bot(1)]);
              players[1].isBot = true;
              player++;
            }
          }
          break;
        case sf::Event::MouseMoved:
          showCharacterStats = false;
          for (int m = 0; m < characters.size(); m++)
          {
            if (characters[m].sprite.getGlobalBounds().contains(mousePosition))
            {
              text.setPosition(sf::Vector2f(650.f, 100.f));
              text.setString(characters[m].displayStats());
              showCharacterStats = true;
            }
          }
          if (!showCharacterStats)
          {
            text.setString(displayString);
            text.setPosition(sf::Vector2f(350.f, 200.f));
          }
        default:
          break;
        }
      }
      window.draw(text);
      window.display();

      if (player == 3)
      {
        menu = false;
      }
    }

    // Menu closes. Character choices are prepared for the game.
    initCombatants(players, characters, combatants);
   
    std::string infoTextString;

    initText(infoText, font, 30, sf::Color::Magenta, sf::Color::Black, 4, sf::Vector2f(550.f, 100.f));
    initText(stats1, font, 25, sf::Color::Magenta, sf::Color::Black, 4, sf::Vector2f(10.f, 0.f));
    initText(stats2, font, 25, sf::Color::Magenta, sf::Color::Black, 4, sf::Vector2f(1390.f, 0.f));

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
        std::cout << "character sheet " << l << " didnt load\n";
        return 0;
      };
      combatants[l].sprite.setTexture(combatants[l].texture);
      float x;
      switch (l)
      {
      case 0:
        x = 400;
        combatants[l].sprite.setTextureRect(combatants[l].defaultRectL);
        break;
      case 1:
        x = 1000;
        combatants[l].sprite.setTextureRect(combatants[l].defaultRectR);
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
      stats1.setString(combatants[0].displayCurrentStats());
      stats2.setString(combatants[1].displayCurrentStats());

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

          chooseAction(action, enoughStamina, combatants[i], infoTextString);

          while (window.pollEvent(event))
          {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            switch (event.type)
            {
            case sf::Event::Closed:
              victory = true;
              menu = false;
              for (int j = 0; j < 2; j++)
              {
                exitState = combatants[j].exitState();
              }
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
      applyActions(combatants, tracker, actionRecord);

      // Character animations
      sf::Sprite opponentSprite;
      if (!exitState)
      {
        for (int k = 0; k < actionRecord.size(); k++)
        {
          infoText.setString(actionRecord[k].outcomeString);
          for (int j = 0; j < combatants.size(); j++)
          {
            if (combatants[j].player == actionRecord[k].player)
            {
              combatants[j].animating = true;
              std::cout << actionRecord[k].player << " " << actionRecord[k].action << "\n";

              // Locate opponent sprite
              for (int m = 0; m < 2; m++)
              {
                if (combatants[j].player != combatants[m].player)
                {
                  opponentSprite = combatants[m].sprite;
                  break;
                }
              }

              // Total time elapsed
              sf::Clock clock1;
              clock1.restart();
              // Time since last animation
              sf::Clock clock2;
              clock2.restart();
              while (combatants[j].animating)
              {
                window.clear();
                window.draw(background);
                window.draw(infoText);
                if (clock2.getElapsedTime() > sf::milliseconds(5))
                {
                  combatants[j].animateCharacter(actionRecord[k], opponentSprite, clock1.getElapsedTime());
                  clock2.restart();
                }
                window.draw(combatants[0].sprite);
                window.draw(combatants[1].sprite);
                window.display();
                while (window.pollEvent(event))
                {
                  switch (event.type)
                  {
                  case sf::Event::Closed:
                    victory = true;
                    menu = false;
                    for (int i = 0; i < 2; i++)
                    {
                      exitState = combatants[i].exitState();
                    }
                    window.close();
                    break;
                  }
                }
              }
            }
          }
        }
      }

      // Reset the action dependant stats, regain stamina
      // and clear the actionRecord ready for next turn.
      for (int n = 0; n < 2; n++)
      {
        combatants[n].resetTempStats();
        combatants[n].increaseStamina();
        actionRecord.clear();
      }

      for (int m = 0; m < 2; m++)
      {
        if (combatants[m].hp <= 0)
        {
          victory = true;
          window.close();
          continue;
        }
      }
    }
  }
  return 0;
}