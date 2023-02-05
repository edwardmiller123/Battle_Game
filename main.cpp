#include <iostream>

#include <string>
#include <vector>

class character {
  public:
    std::string name;
    int hp;
    int baseSpeed;
    int baseAttack;
    int speed;
    int attack;
    int damageInflicted;
    int player;
    bool guarding;
    bool preparingToDodge;

    void new_character(std::string newName, int newHp, int newSpeed, int newAttack, bool initGuard = false, bool initDodge = false) {
      name = newName;
      hp = newHp;
      baseSpeed = newSpeed;
      baseAttack = newAttack;
      guarding = initGuard;
      preparingToDodge = initDodge;
    }

    void light_attack() {
      int *attackPtr = &attack;
      int *speedPtr = &speed;
      *attackPtr = baseAttack - 5;
      *speedPtr = baseSpeed + 15;
    }

    void heavy_attack() {
      int *attackPtr = &attack;
      int *speedPtr = &speed;
      *attackPtr = baseAttack + 10;
      *speedPtr = baseSpeed - 20;
    }

    void dodge() {
      
    }

    void guard() {
      
    }

};

character speedy_mc_speed, big_boi, allrounder;

void resetStats(std::vector<character> combatants) {
  for (int i = 0; i < 2; i++) {
    character* playerPtr = &combatants[i];
    // playerPtr.attack = 0;
    // playerPtr.speed = 0;
  }
}

int main() {
  speedy_mc_speed.new_character("SpeedyMcSpeed", 45, 85, 10);
  big_boi.new_character("BigBoi", 90, 30, 20);
  allrounder.new_character("Joe", 60, 60, 15);

  bool victory = false;
  std::vector<character> combatants, characters;
  std::string choicePlayer1, choicePlayer2;
  int action;

  characters = {speedy_mc_speed, big_boi, allrounder};
  combatants = {};

  std::cout << "Player1, Choose your character:\n";

  std::cin >> choicePlayer1;

  std::cout << "Player2, Choose your character:\n";

  std::cin >> choicePlayer2;

  std::vector<std::string> players = {choicePlayer1, choicePlayer2};

  for (int j = 0; j < players.size(); j++) {
    for (int i = 0; i < characters.size(); i++) {
      if (players[j] == characters[i].name) {
        combatants.push_back(characters[i]);
        // combatants[j].player = j;
      }
    } 
  }


  std::cout << "\nBegin!\n";

  while (victory != true) {

    // resetStats(combatants);

    for (int i = 0; i < 2; i++) {
      std::cout << "Player " << i + 1 << ": Choose action...\n";
      std::cin >> action;

      switch (action) {
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
    victory = true;
  }
  std::cout << combatants[0].attack << "\n";
  std::cout << combatants[1].attack << "\n";
}