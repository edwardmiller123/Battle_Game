#include <iostream>
#include <random>
#include <time.h>

bool actionSucceeds(int number)
{
  srand(time(0));
  int randNumber = 0 + rand() % 100;
  switch (number >= randNumber)
  {
  case true:
    return true;
  case false:
    return false;
  }
}

// "Bot" actually just randomly selects numbers.
int bot(int section) {
  int i, j;
  srand(time(0));
  switch (section) {
    case 1:
    // Choose character
      i = 3;
      j = 0;
      break;
    case 2:
    // Choose action
      i = 4;
      j = 1;
      break;
  }
return j + rand() % i;
}