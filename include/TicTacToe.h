#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <algorithm>
#include <vector>

class Player
{
public:
    std::string nume;
    char status;   // c - winner, e - equal
    char x0;
    int puncte;
    Player();
};

class Bot : public Player
{
public:
    std::vector<int> positionsLeft;

    Bot(const Player& p);
    void erasePosition(int position);
    int findPosition(int position);
};

struct PlayerLead
{
    std::string nume;
    short puncte;

    bool operator<(const PlayerLead& p) const;
    bool operator>(const PlayerLead& p) const;
    void operator=(const PlayerLead& p);
};

void textcolor(int color);
void gotoxy(short x, short y);
void resetBuffer();
void draw(char* a);
void verificare(char* a, Player* p, bool& game);
void inceputPlay(Player* p, std::string gameMode);
void Rematch(bool& game, bool& rematch);
void castig(Player* p,bool& game, bool& rematch);
int mutareCursor(short x, short y);
int randomInt(Bot* bot);
void joc(char* a, Player* p, bool& game, bool& rematch, std::string gameMode);
void init(char* a, Player* p);
void sortare(PlayerLead* p, const short n);
bool final(const Player* p, const std::string gameMode);
short inceput();
bool showLeaderBoard();

#endif