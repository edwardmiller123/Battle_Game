#include <iostream>
#include <vector>

#include "character.h"

std::vector<character> initCharacters()
{
  character speedyMcSpeed, bigBoi, joe, veryBadCharacter;
  std::vector<character> characters;

  // TODO: Fix speedys sprite sheet.
  speedyMcSpeed.new_character("SpeedyMcSpeed", 60, 85, 10, 50, 90, 30, "assets/speedy_sheet.png", sf::Vector2f(0.75, 0.75),
                              {798, 529, 292, 900}, {452, 75, 283, 268}, {1137, 531, 346, 264}, {22, 47, 333, 261},
                              {350, 465, 417, 340}, {769, 6, 385, 343}, {27, 544, 277, 253}, {1213, 100, 262, 257});
  bigBoi.new_character("BigBoi", 90, 30, 20, 85, 70, 20, "assets/bigboi_sheet.png", sf::Vector2f(0.25, 0.25),
                       {3493, 2025, 785, 805}, {225, 581, 741, 789}, {2345, 1973, 1061, 869}, {1045, 545, 1073, 845},
                       {1097, 1473, 1129, 1365}, {2213, 29, 1125, 1377}, {173, 1997, 897, 849}, {3429, 537, 893, 901});
  joe.new_character("Joe", 70, 60, 15, 75, 90, 25, "assets/joe_sheet.png", sf::Vector2f(0.25, 0.25),
                    {96, 119, 664, 756}, {2945, 1345, 773, 753}, {2093, 1345, 821, 789}, {901, 105, 725, 773},
                    {905, 1293, 1109, 809}, {1789, 101, 1009, 757}, {9, 1293, 813, 821}, {3049, 41, 717, 809});
  veryBadCharacter.new_character("BadStats", 50, 1, 1, 1, 1, 1, "assets/bad_stats.png", sf::Vector2f(0.25, 0.25),
                                 {127, 18, 581, 504}, {127, 18, 581, 504}, {127, 18, 581, 504}, {127, 18, 581, 504},
                                 {127, 18, 581, 504}, {127, 18, 581, 504}, {127, 18, 581, 504}, {127, 18, 581, 504});

  characters = {speedyMcSpeed, bigBoi, joe, veryBadCharacter};
  return characters;
}
