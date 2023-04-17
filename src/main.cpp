#include "../include/TicTacToe.h"

int main()
{
    Player p[2];
    std::string optiune;
    char a[9];
    bool game, rematch;
    short s;
    begin:
    rematch=true;
    game=true;
    s = inceput();
    if (s == 0)
        optiune="1v1";
    else if (s == 1)
        optiune="bot";
    else if (s == 2)
    {
        if(showLeaderBoard())   
            goto begin;
    }
    if(s==0 || s==1)
    {
        inceputPlay(&p[0],optiune);
        while (rematch)
        {
            init(a, p);
            joc(a, p, game, rematch, optiune);
        }
        if (final(p, optiune))
            goto begin;
    }
    system("cls");
    resetBuffer();
    while(GetAsyncKeyState(VK_RETURN)) {}
    return 0;
}

