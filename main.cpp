#include <iostream>

#include <string>
#include <vector>

class character {
  public:
    std::string name;
    int hp;
    int speed;
    bool guarding;
    bool preparing_to_dodge;

    void new_character(std::string new_name, int new_hp, int new_speed, bool init_guard = false, bool init_dodge = false) {
      name = new_name;
      hp = new_hp;
      speed = new_speed;
      guarding = init_guard;
      preparing_to_dodge = init_dodge;
    }

    void light_attack() {

    }

    void heavy_attack() {

    }

    void dodge() {

    }

    void guard() {

    }

};

character speedy_mc_speed, big_boi, allrounder;


int main() {
  speedy_mc_speed.new_character("SpeedyMcSpeed", 45, 85);
  big_boi.new_character("BigBoi", 90, 30);
  allrounder.new_character("Joe", 60, 60);

  bool victory = true;
  std::vector<character> combatants, characters;
  std::string choice1, choice2;

  characters = {speedy_mc_speed, big_boi, allrounder};
  combatants = {};

  std::cout << "Player1, Choose your character:\n";

  std::cin >> choice1;

  std::cout << "Player2, Choose your character:\n";

  std::cin >> choice2;

  for (int i = 0; i < sizeof(characters); i++) {
    if (choice1 == characters[i].name || choice2 == characters[i].name) {
      combatants.push_back(characters[i]);
    }
  } 


  while (victory != true) {
    std::cout << "Begin!\n";

    for (int i = 0; i < sizeof(combatants); i++) {

    } 

    
  }
}