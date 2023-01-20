# 2048

This is my final project for Introduction to Programming Practicum course @ Faculty of Mathematics and Informatics, Sofia University - remake of the clasical game 2048 with new levels.

### Features
___
- Written in C++
- Stupidly easy to play
- Works on Mac and (hopefully) Windows

### Installation
___
1. Make sure gcc is installed 
2. Open Terminal and copy the following code:
```
git clone https://github.com/KostadinRusalov/2048.git
cd 2048/code
g++ *.cpp -o 2048
./2048
```

### Usage
___
#### Menu commands
```
1. start game
2. leaderboard
3. quit
```
##### Start game
The game asks you to choose a nickname and dimension. This version of 2048 supports from a 4x4 to a 10x10 board. 
If you beat someone's score, you enter the Top 5 in the leaderboard!

##### Leaderboard
You can check the high scores of each board to see if you are good enough to win.

##### Quit
Only allowed if you have to study for DIS.

#### In-Game commands
___

```
w // move up
a // move left
d // move right
s // move down
q // quit the round
```