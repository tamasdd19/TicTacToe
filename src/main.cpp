#include "../include/TicTacToe.h"

int main()
{
    Player p[2];
    char a[9];
    bool game, rematch;
    short s;
    begin:
    rematch=true;
    game=true;
    s = inceput();
    if (s == 0)
    {
        inceputPlay(&p[0]);
        while (rematch)
        {
            while(GetAsyncKeyState(VK_RETURN)) {}
            init(&a[0], &p[0]);
            joc(&a[0], &p[0],game,rematch);
        }
        if (final(p))
            goto begin;
    }
    else if (s == 1)
    {
        if(showLeaderBoard())   
            goto begin;
    }
    system("cls");
    resetBuffer();
    while(GetAsyncKeyState(VK_RETURN)) {}
    return 0;
}

