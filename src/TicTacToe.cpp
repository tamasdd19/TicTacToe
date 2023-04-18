#include "../include/TicTacToe.h"

void textcolor(int color) // 112 - white background
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        color + (__BACKGROUND << 4));
}

void gotoxy(short x, short y)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(h, coord);
}

void resetBuffer()
{
    while (_kbhit())
        _getch();
}

void draw(char* a)
{
    system("cls");
    int i;
    for (i = 0; i < 9; i++)
    {
        std::cout << *(a + i);
        if ((i + 1) % 3 == 0)
            std::cout << "\n";
        else
            std::cout << " | ";
    }
}

void verificare(char* a, Player* p, bool& game)
{
    int i;
    char castigator;
    bool egal = true;
    for (i = 0; i < 9; i++)
    {
        if (a[i] != ' ')
        {
            if (i == 0)
            {
                if ((a[i] == a[i + 1] && a[i] == a[i + 2]) || (a[i] == a[i + 3] && a[i] == a[i + 6]) || (a[i] == a[i + 4] && a[i] == a[i + 8]))
                {
                    castigator = a[i];
                    game = false;
                }
            }
            else if (i == 1)
            {
                if ((a[i] == a[i + 3] && a[i] == a[i + 6]))
                {
                    castigator = a[i];
                    game = false;
                }
            }
            else if (i == 2)
            {
                if ((a[i] == a[i + 2] && a[i] == a[i + 4]) || (a[i] == a[i + 3] && a[i] == a[i + 6]))
                {
                    castigator = a[i];
                    game = false;
                }
            }
            else if ((i == 3 || i == 6) && (a[i] == a[i + 1] && a[i] == a[i + 2]))
            {
                castigator = a[i];
                game = false;
            }
        }
        else
            egal = false;
    }
    if (egal)
    {
        p->status = 'e';
        game = false;
        return;
    }
    if (!game)
    {
        if (castigator == p->x0)
            p->status = 'c';
        else
            (p + 1)->status = 'c';
    }
}

void inceputPlay(Player* p, std::string gameMode)
{
    while (GetAsyncKeyState(VK_RETURN)) {}
    resetBuffer();
    system("cls");
    std::cout << "TIC TAC TOE\n";
    if(gameMode=="1v1")
    {
        std::cout << "Player1's name:";
        std::cin >> p->nume;
        std::cout << "Player2's name:";
        std::cin >> (p + 1)->nume;
        while (p->nume == (p + 1)->nume)
        {
            std::cout << "You must choose different names!\nPlayer nr 2:";
            std::cin >> (p + 1)->nume;
        }
    }
    else if(gameMode=="bot")
    {
        std::cout << "Player's name:";
        std::cin >> p->nume;
        p[1].nume = "Bot";
    }
    p[1].x0 = 'O';
    p->x0 = 'X';
    for(int i=0; i<2; i++)
    {
        p[i].status='\0';
        p[i].puncte=0;
    }
}

void Rematch(bool& game, bool& rematch)
{
    int k = 0, x=0, y=6;
    std::cout << "\nRematch?\n";
    std::cout << "YES | NO";
    gotoxy(x, y);
    while (true)
    {
        if ((GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) && k == 0)//a
        {
            k = 1;
            x = 0;
            gotoxy(x, y);
        }
        else if (GetAsyncKeyState(0x41) == 0 && GetAsyncKeyState(VK_LEFT)==0)
            k = 0;
        if ((GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)) && k == 0)//d
        {
            k = 1;
            x = 7;
            gotoxy(x, y);
        }
        else if (GetAsyncKeyState(0x44) == 0 && GetAsyncKeyState(VK_RIGHT)==0) 
            k = 0;
        if (GetAsyncKeyState(VK_RETURN) && k == 0)
        {
            while(GetAsyncKeyState(VK_RETURN)) {}
            break; 
        }
    }
    if (x == 0)
        game = true;
    else
        rematch = false;
}

void castig(Player* p,bool& game, bool& rematch)
{
    std::string raspuns;
    for (int i = 0; i < 2; i++)
    {
        if ((p + i)->status == 'c')
        {
            std::cout << "The winner is: " << (p + i)->nume;
            (p + i)->puncte += 1;
        }
        else if ((p + i)->status == 'e')
        {
            std::cout << "Draw!";
            break;
        }
        else
        {
            (p + i)->puncte -= 1;
        }
    }
    Rematch(game,rematch);
}

int mutareCursor(short x, short y)
{
    while (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) {}
    while (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) {}
    while (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) {}
    while (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)) {}
    while (GetAsyncKeyState(VK_RETURN)) {}
    
    int k = 0;
    const short MAX_X = 9, MIN = -1, MAX_Y = 3;
    gotoxy(x, y);
    while (true)
    {
        if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)))//w
        {
            y -= 1;
            if (y <= MIN)
            {
                x = 4;
                y = 1;
            }
            while (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) {}
            gotoxy(x, y);
        }
        if ((GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)))//a
        {
            x -= 4;
            if (x <= MIN)
            {
                x = 4;
                y = 1;
            }
            while (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) {}
            gotoxy(x, y);
        }
        if ((GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)))//s
        {
            y++;
            if (y >= MAX_Y)
            {
                x = 4;
                y = 1;
            }
            while (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) {}
            gotoxy(x, y);
        }
        if ((GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)))//d
        {
            x += 4;
            if (x >= MAX_X)
            {
                x = 4;
                y = 1;
            }
            while (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)) {}
            gotoxy(x, y);
        }
        if (GetAsyncKeyState(VK_RETURN))
        {
            while(GetAsyncKeyState(VK_RETURN)) {}
            break;
        }
        Sleep(150);
    }
    Sleep(100);
    return (x / 4 + 3 * y);
}

int randomInt(Bot* bot)
{                 
    srand((unsigned) time(NULL));
    int random=rand()%bot->positionsLeft.size();
    int toReturn=bot->positionsLeft[random];
    bot->erasePosition(random);
    return toReturn;
}

void joc(char* a, Player* p, bool& game, bool& rematch, std::string gameMode)
{
    resetBuffer();
    Bot* bot;
    int s;
    short x = 4, y = 1;
    if(gameMode=="bot")
    {
        bot = new Bot(p[1]);
    }
    for (int i = 0; game; i++)
    {
        draw(&a[0]);
        std::cout << (p + i % 2)->nume << "'s turn!";
        s = mutareCursor(4, 1);
        while (a[s] == 'X' || a[s] == 'O')
            s = mutareCursor(4, 1);
        a[s] = p[i % 2].x0;
        verificare(a, p, game);
        if(gameMode=="bot" && game)
        {
            bot->erasePosition(bot->findPosition(s));
            i++;
            draw(a);
            std::cout << (p + i % 2)->nume << "'s turn!";
            s=randomInt(bot);
            a[s] = p[i%2].x0;
            verificare(a, p, game);
        }
    }
    if(gameMode=="bot")
        delete bot;
    resetBuffer();
    draw(a);
    std::cout << "==========\n";
    castig(p,game,rematch);
}

void init(char* a, Player* p)
{
    while(GetAsyncKeyState(VK_RETURN)) {}
    for (int i = 0; i < 9; i++)
        a[i] = ' ';
    for (int i = 0; i < 2; i++)
        p[i].status = '\0';
}

void sortare(PlayerLead* p, const short n) // sorteaza leaderboard-ul dupa finalul meciului
{
    std::sort(p,p+n,[](const PlayerLead& p1, const PlayerLead& p2)
    {
        return p1>p2;
    });
}

bool final(const Player* p, const std::string gameMode)
{
    system("cls");
    std::ifstream f("src/input/leaderboard.txt");
    short n=0;
    bool samePlayer[2] = { false,false };
    f >> n;
    PlayerLead* p2 = new PlayerLead[n + 2];
    if (n != 0)
    {       
        for (short i = 0; i < n; i++)
        {
            f >> p2[i].nume;
            f >> p2[i].puncte;
            if (samePlayer[0] == false || samePlayer[1] == false)
            {
                for (short j = 0; j < 2; j++)
                {
                    if (p2[i].nume == (p + j)->nume)
                    {
                        p2[i].puncte += (p + j)->puncte;
                        if(p2[i].puncte < 0)
                            p2[i].puncte = 0;
                        samePlayer[j] = true;
                        break;
                    }
                }
            }
        }
        for (short i = 0; i < 2; i++)
        {
            if (!samePlayer[i])
            {
                p2[n].nume = (p + i)->nume;
                p2[n].puncte = (p + i)->puncte;
                n++;
            }
            if(gameMode=="bot")
                break;
        }
        sortare(p2, n);
    }
    else
    {
        if(gameMode=="bot")
            n=1;
        else
            n=2;
        for (short i = 0; i < n; i++)
        {
            p2[i].nume = (p + i)->nume;
            p2[i].puncte = (p + i)->puncte;
        }
    }
    f.close();
    std::ofstream d("src/input/leaderboard.txt");
    textcolor(112);
    std::cout << "LeaderBoard\n";
    textcolor(7);
    d << n << "\n";
    for (short i = 0; i < n; i++)
    {
        d << p2[i].nume << " " << p2[i].puncte << "\n";
        std::cout << i+1 << ". " << p2[i].nume << ": " << p2[i].puncte << "\n";
    }
    d.close();
    delete [] p2;
    std::cout << "Press ENTER to go back and ESC to exit";
    while(GetAsyncKeyState(VK_RETURN)) {}
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN)) //enter
        {
            return true;
        }
        if (GetAsyncKeyState(VK_ESCAPE)) // esc
        {
            return false;
        }
    }
}

short inceput()
{
    short k=0, y=3, MAX_Y = 7, MIN=2, culoare=0;
    bool gasit = false;
    std::string optiuni[4] = { "Play 1v1","Play against Bot","LeaderBoard","Exit" };
    while(GetAsyncKeyState(VK_RETURN)) {}
    while (!gasit)
    {
        system("cls");
        std::cout << "TicTacToe!\n\n\n";
        for (short i = 0; i < 4; i++)
        {
            if (culoare == i)
            {
                textcolor(112);
                std::cout << optiuni[i] << "\n";
                textcolor(7);
            }
            else
                std::cout << optiuni[i] << "\n";
        }
        gotoxy(0, y);
        while (true)
        {
            if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP))//w
            {
                y -= 1;
                culoare--;
                if (y <= MIN)
                {
                    y = 3;
                    culoare = 0;
                }
                while(GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) {}
                break;
            }
            if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN))//s
            {
                y++;
                culoare++;
                if (y >= MAX_Y)
                {
                    y = 6;
                    culoare=3;
                }
                while(GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) {}
                break;
            }
            if (GetAsyncKeyState(VK_RETURN))
            {
                while (GetAsyncKeyState(VK_RETURN)) {}
                gasit = true;
                break;
            }
            Sleep(200);
        }
    }
    return(y - 3);
}

bool showLeaderBoard()
{
    std::ifstream f("src/input/leaderboard.txt");
    std::string nume;
    short puncte;
    short n=0;
    system("cls");
    textcolor(112);
    std::cout << "LeaderBoard\n";
    textcolor(7);
    f >> n;
    if(n!=0)
    {
        for (short i=0; i < n; i++)
        {
            f >> nume >> puncte;
            std::cout << i + 1 << ". " << nume << ": " << puncte << "\n";
        }
    }
    else
    {
        std::cout << "\nNo players registered yet\n\n";
    }
    f.close();
    std::cout << "Press ENTER to go back and ESC to exit";
    while(GetAsyncKeyState(VK_RETURN)){}
    Sleep(100);
    resetBuffer();
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN)) //enter
        {
            while (GetAsyncKeyState(VK_RETURN)) {}
            return true;
        }
        if (GetAsyncKeyState(VK_ESCAPE)) // esc
        {
            return false;
        }
    }
}

