#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class actionCard
{
public:
  sf::Sprite sprite;
  sf::Texture texture;
  std::string texturePath;
  float posX, posY, scaleX, scaleY;
  int actionNumber;

  void newActionCard(std::string newTexturePath, float newPosX, float newPosY, float newScaleX, float newScaleY, int newActionNumber)
  {
    texturePath = newTexturePath;
    posX = newPosX;
    posY = newPosY;
    scaleX = newScaleX;
    scaleY = newScaleY;
    actionNumber = newActionNumber;
  }
};

std::vector<actionCard> initActionCards() {
  actionCard lightAttackCard, heavyAttackCard, dodgeCard, guardCard;
  std::vector<actionCard> actionCards;
  lightAttackCard.newActionCard("assets/light_attack_card.png", 200, 500, 0.125, 0.125, 1);
  heavyAttackCard.newActionCard("assets/heavy_attack_card.png", 500, 500, 0.125, 0.125, 2);
  dodgeCard.newActionCard("assets/dodge_card.png", 800, 500, 0.125, 0.125, 3);
  guardCard.newActionCard("assets/guard_card.png", 1200, 500, 0.125, 0.125, 4);
  actionCards = {lightAttackCard, heavyAttackCard, dodgeCard, guardCard};
  return actionCards;
}
