This project is my implementation of the classic game TicTacToe in C++;

---
## Setup
Clone the repository, and just run the main.exe file, the game should start.<br>
If you want to modify and recompile the program, then you should open Makefile and change the WIN_USER32 path to find your User32.lib<br>
Your path should be similar to mine, but your windows version may differ.<br>
You need to do that because in the project I use the **windows.h** library which needs the path to User32.lib in order to compile with Makefile.<br>
After you've done that, just use *make run* in a terminal and everything will compile and run.

---
##  Features
When you open the app, you are welcomed with the main menu. You can go through the whole app using *arrows* or *WASD* and **[ENTER]** to select an option.<br>
If you choose to play, then you will enter the 2 players names and the game will begin. At the moment you can only play with another friend using the same system, but I will add a bot mode soon.<br>

![Interfata2](https://user-images.githubusercontent.com/118727728/228666711-74182079-16a7-4768-8c32-7eeaf41718cd.png)
<br>
After the match, the scores will be added in the leaderboard system. This system is counting everyone that has ever played the game on your system. If the player wins, 1 point will be added to his score and if the player looses, 1 point will be taken.<br>

![LeaderBoard](https://user-images.githubusercontent.com/118727728/228670028-60d72c5b-61e9-403b-8c92-fe475e56f931.png)

---

## Other
Project made by [tamasdd19](https://github.com/tamasdd19) 
