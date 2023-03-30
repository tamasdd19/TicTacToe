#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <algorithm>

struct Player
{
    std::string nume;
    char status;   // c - winner, e - equal
    char x0;
    int puncte;
    Player()
    {        
        puncte = 0;
    }
};

struct PlayerLead
{
    std::string nume;
    short puncte;

    bool operator<(const PlayerLead& p) const
    {
        return(puncte < p.puncte);
    }
    
    bool operator>(const PlayerLead& p) const
    {
        return(puncte > p.puncte);
    }

    void operator=(const PlayerLead& p)
    {
        nume = p.nume;
        puncte = p.puncte;
    }
};

void textcolor(int color);
void gotoxy(short x, short y);
void resetBuffer();
void draw(char* a);
void verificare(char* a, Player* p, bool& game);
void inceputPlay(Player* p);
void Rematch(bool& game, bool& rematch);
void castig(Player* p,bool& game, bool& rematch);
int mutareCursor(short x, short y);
void joc(char* a, Player* p, bool& game, bool& rematch);
void init(char* a, Player* p);
void sortare(PlayerLead* p, const short n);
bool final(const Player* p);
short inceput();
bool showLeaderBoard();

#endif