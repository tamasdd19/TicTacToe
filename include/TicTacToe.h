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
    Player()
    {        
        puncte = 0;
    }
};

class Bot : public Player
{
public:
    std::vector<int> positionsLeft;

    Bot(const Player& p)
    {
        positionsLeft.reserve(9);
        for(int i=0; i<9; i++)
            positionsLeft.emplace_back(i);
        nume=p.nume;
        status='\0';
        x0='O';
        puncte=0;
    }
    Bot()
    {
    }
    void erasePosition(int position)
    {
        positionsLeft.erase(positionsLeft.begin()+position);
    }
    void printVector()
    {
        for(int i : positionsLeft)
            std::cout << i << std::endl;
    }
    int findPosition(int position)
    {
        int contor=0;
        for(int i : positionsLeft)
        {
            if(i==position)
                break;
            contor++;
        }
        return contor;
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