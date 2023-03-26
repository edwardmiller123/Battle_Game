#include <iostream>
#include <vector>

#include "character.h"

std::vector<character> initCharacters()
{
  character speedyMcSpeed, bigBoi, joe, veryBadCharacter;
  std::vector<character> characters;

  speedyMcSpeed.new_character("SpeedyMcSpeed", 60, 85, 10, 50, 90, 30, "assets/speedy.png");
  bigBoi.new_character("BigBoi", 90, 30, 20, 85, 70, 20, "assets/big_boi.png");
  joe.new_character("Joe", 70, 60, 15, 75, 90, 25, "assets/joe.png");
  veryBadCharacter.new_character("BadStats", 50, 1, 1, 1, 1, 1, "assets/bad_stats.png");

  characters = {speedyMcSpeed, bigBoi, joe, veryBadCharacter};
  return characters;
}
