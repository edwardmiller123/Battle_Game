#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class actionCard
{
public:
  sf::Sprite sprite;
  sf::Texture texture;
  std::string texturePath, selectedTexturePath;
  float posX, posY, scaleX, scaleY;
  int actionNumber;

  void newActionCard(std::string newTexturePath, std::string newSelectedTexturePath, float newPosX, float newPosY, float newScaleX, float newScaleY, int newActionNumber)
  {
    texturePath = newTexturePath;
    posX = newPosX;
    posY = newPosY;
    scaleX = newScaleX;
    scaleY = newScaleY;
    actionNumber = newActionNumber;
    selectedTexturePath = newSelectedTexturePath;
  }
};

std::vector<actionCard> initActionCards() {
  actionCard lightAttackCard, heavyAttackCard, dodgeCard, guardCard;
  std::vector<actionCard> actionCards;
  lightAttackCard.newActionCard("assets/light_attack_card.png","assets/selected_light_attack_card.png", 200, 450, 0.125, 0.125, 1);
  heavyAttackCard.newActionCard("assets/heavy_attack_card.png", "assets/selected_heavy_attack_card.png", 500, 450, 0.125, 0.125, 2);
  dodgeCard.newActionCard("assets/dodge_card.png", "assets/selected_dodge_card.png", 800, 450, 0.125, 0.125, 3);
  guardCard.newActionCard("assets/guard_card.png", "assets/selected_guard_card.png", 1200, 450, 0.125, 0.125, 4);
  actionCards = {lightAttackCard, heavyAttackCard, dodgeCard, guardCard};
  return actionCards;
}
