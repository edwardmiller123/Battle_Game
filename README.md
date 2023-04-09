To compile:
g++ -I C:\Users\edwar\Documents\codeProjects\C++\SFML-2.5.1\include -c main.cpp -o main.o
without console:
g++ -L C:\Users\edwar\Documents\codeProjects\C++\SFML-2.5.1\lib .\main.o -o game.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows
with console:
g++ -L C:\Users\edwar\Documents\codeProjects\C++\SFML-2.5.1\lib .\main.o -o game.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main

# Battle Game
First sfml project. Pretty janky but hey.
Thankyou to my fiance for doing the drawings.
## Compilation Instructions
For windows using MinGW. Download sfml and the matching compiler version
from the [website](https://www.sfml-dev.org/download/sfml/2.5.1/). The versions MUST
match 100 percent. 
To make the .o file:
```
g++ -I path\to\sfml\SFML-2.5.1\include -c main.cpp -o main.o
```
To make the game.exe:
```
g++ -L path\to\sfml\SFML-2.5.1\lib .\main.o -o game.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows
```
With console output:

```
g++ -L path\to\sfml\SFML-2.5.1\lib .\main.o -o game.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main
```


