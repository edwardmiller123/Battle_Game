# Battle Game
First sfml project. Pretty janky but hey.
Thankyou to my fiance for doing the drawings.
## Compilation Instructions (Windows)
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
### Static Linking
To run .exe outside of the directory it was complied in you need to link to the static versions of the sfml libaries. Just remember to copy 
the assets folder over to where ever the .exe goes.
Can complile in one step:
```
g++ -DSFML_STATIC -I path\to\sfml\SFML-2.5.1\include -L path\to\sfml\SFML-2.5.1\lib main.cpp -o game.exe -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -static -static-libgcc -static-libstdc++
```
## Compilation Instructions (Linux)
The simplest way is to install SFML with: 
```
sudo apt-get install libsfml-dev
```
You can then compile with:
```
g++ -c main.cpp
```
and create the application with:
```
g++ main.o -o game.exe sfml-app -lsfml-graphics -lsfml-window -lsfml-system
```






