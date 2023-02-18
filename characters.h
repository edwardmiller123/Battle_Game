#include <iostream>
#include <vector>

#include "character.h"

std::vector<character> initCharacters() {
  character speedyMcSpeed, bigBoi, joe, veryBadCharacter, korok;
  std::vector<character> characters;

  speedyMcSpeed.new_character("SpeedyMcSpeed", 60, 85, 10, 50, 90, 30);
  bigBoi.new_character("BigBoi", 90, 30, 20, 85, 70, 20);
  joe.new_character("Joe", 70, 60, 15, 75, 90, 25);
  veryBadCharacter.new_character("BadStats", 50, 1, 1, 1, 1, 1);
  korok.new_character("Korok", 90, 70, 8, 35, 60, 25);

  characters = {speedyMcSpeed, bigBoi, joe, veryBadCharacter, korok};
  return characters;
}