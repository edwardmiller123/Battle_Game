#include <iostream>
#include <random>
#include <windows.h>
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
  int i;
  srand(time(0));
  switch (section) {
    case 1:
    // Choose character
      i = 3;
      break;
    case 2:
    // Choose action
      i = 5;
      break;
  }
  Sleep(3);
return 1 + rand() % i;
}