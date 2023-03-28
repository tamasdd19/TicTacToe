#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <algorithm>
#include <vector>

bool game;
bool rematch;

struct Player
{
    std::string nume;
    char status;   // c - castigator, e - egal
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

void textcolor(int color) // 112 - fundal alb scris negru
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

void verificare(char* a, Player* p)
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

void inceputPlay(Player* p)
{
    while (GetAsyncKeyState(VK_RETURN)) {}
    resetBuffer();
    system("cls");
    std::cout << "TIC TAC TOE\n";
    std::cout << "Playerul nr 1:";
    std::cin >> p->nume;
    std::cout << "Playerul nr 2:";
    std::cin >> (p + 1)->nume;
    while (p->nume == (p + 1)->nume)
    {
        std::cout << "Trebuie sa fie nume diferite!\nPlayerul nr 2:";
        std::cin >> (p + 1)->nume;
    }
    (p + 1)->x0 = '0';
    p->x0 = 'X';
    for(int i=0; i<2; i++)
        p[i].status='\0';
}

void Rematch()
{
    int k = 0, x=0, y=6;
    std::cout << "\nRematch?\n";
    std::cout << "DA | NU";
    gotoxy(x, y);
    while (true)
    {
        if (GetAsyncKeyState(0x41) && k == 0)//a
        {
            k = 1;
            x = 0;
            gotoxy(x, y);
        }
        else if (GetAsyncKeyState(0x41) == 0)
            k = 0;
        if (GetAsyncKeyState(0x44) && k == 0)//d
        {
            k = 1;
            x = 6;
            gotoxy(x, y);
        }
        else if (GetAsyncKeyState(0x44) == 0)
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

void castig(Player* p)
{
    std::string raspuns;
    for (int i = 0; i < 2; i++)
    {
        if ((p + i)->status == 'c')
        {
            std::cout << "Castigatorul este: " << (p + i)->nume;
            (p + i)->puncte += 1;
        }
        else if ((p + i)->status == 'e')
        {
            std::cout << "Egal!";
            break;
        }
        else
            (p + i)->puncte--;
    }
    Rematch();
}

int mutareCursor(short x, short y)
{
    while (GetAsyncKeyState(0x41)) {}
    while (GetAsyncKeyState(0x57)) {}
    while (GetAsyncKeyState(0x53)) {}
    while (GetAsyncKeyState(0x44)) {}
    while (GetAsyncKeyState(VK_RETURN)) {}
    
    int k = 0;
    const short MAX_X = 9, MIN = -1, MAX_Y = 3;
    gotoxy(x, y);
    while (true)
    {
        if (GetAsyncKeyState(0x57) && k == 0)//w
        {
            k = 1;
            y -= 1;
            if (y <= MIN)
            {
                x = 4;
                y = 1;
            }
        
            gotoxy(x, y);
        }
        else if (GetAsyncKeyState(0x57) == 0)
            k = 0;
        if (GetAsyncKeyState(0x41) && k == 0)//a
        {
            k = 1;
            x -= 4;
            if (x <= MIN)
            {
                x = 4;
                y = 1;
            }
            gotoxy(x, y);
        }
        else if (GetAsyncKeyState(0x41) == 0)
            k = 0;
        if (GetAsyncKeyState(0x53) && k == 0)//s
        {
            k = 1;
            y++;
            if (y >= MAX_Y)
            {
                x = 4;
                y = 1;
            }
            gotoxy(x, y);
        }
        else if (GetAsyncKeyState(0x53) == 0)
            k = 0;
        if (GetAsyncKeyState(0x44) && k == 0)//d
        {
            k = 1;
            x += 4;
            if (x >= MAX_X)
            {
                x = 4;
                y = 1;
            }
            gotoxy(x, y);
        }
        else if (GetAsyncKeyState(0x44) == 0)
            k = 0;
        if (GetAsyncKeyState(VK_RETURN) && k == 0)
        {
            k = 1;
            break;
        }
        Sleep(150);
    }
    Sleep(100);
    return (x / 4 + 3 * y);
}

void joc(char* a, Player* p)
{
    resetBuffer();
    int* s = new int;
    short x = 4, y = 1;
    for (int i = 0; game; i++)
    {
        system("cls");
        draw(&a[0]);
        std::cout << "Alege pozitia, " << (p + i % 2)->nume << "!";
        *s = mutareCursor(4, 1);
        if (a[*s] != 'X' && a[*s] != '0' && a[*s] != 'x')
            a[*s] = p[i % 2].x0;
        else
            i++;
        verificare(&a[0], &p[0]);
    }
    delete s;
    resetBuffer();
    system("cls");
    draw(a);
    std::cout << "==========\n";
    castig(p);
}

void init(char* a, Player* p)
{
    for (int i = 0; i < 9; i++)
        a[i] = ' ';
    for (int i = 0; i < 2; i++)
        p[i].status = '\0';
}

void sortare(PlayerLead* p, const short n) // sorteaza leaderboard-ul dupa finalul meciului
{
    std::vector<PlayerLead> lista_playeri;
    lista_playeri.reserve(n);
    for(int i=0; i<n; i++)
        lista_playeri.emplace_back(p[i]);
    std::sort(lista_playeri.begin(),lista_playeri.end(),[](PlayerLead p1,PlayerLead p2)
              {
                  return p1>p2;
              });
    int i=0;
    for(PlayerLead p2 : lista_playeri)
    {
        p[i]=p2;
        i++;
    }
}

bool final(const Player* p)
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
        }
        sortare(p2, n);
    }
    else
    {
        n = 2;
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
        std::cout << p2[i].nume << " " << p2[i].puncte << " puncte\n";
    }
    d.close();
    delete [] p2;
    std::cout << "Apasa enter pentru a reveni la ecranul principal sau esc pentru a iesii";
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
    short k=0, y=3, MAX_Y = 6, MIN=2, culoare=0;
    bool gasit = false;
    std::string optiuni[3] = { "Play","LeaderBoard","Exit" };
    while(GetAsyncKeyState(VK_RETURN)) {}
    while (!gasit)
    {
        system("cls");
        std::cout << "TicTacToe!\n\tby Tamas Andrei\n\n";
        for (short i = 0; i < 3; i++)
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
            if (GetAsyncKeyState(0x57))//w
            {
                y -= 1;
                culoare--;
                if (y <= MIN)
                {
                    y = 3;
                    culoare = 0;
                }
                break;
            }
            if (GetAsyncKeyState(0x53))//s
            {
                y++;
                culoare++;
                if (y >= MAX_Y)
                {
                    y = 5;
                    culoare=2;
                }
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
        std::cout << "Nu exista playeri inregistrati\n";
    }
    f.close();
    std::cout << "Apasa enter pentru a fi dus inapoi sau esc pentru a iesii";
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

int main()
{
    Player p[2];
    char a[9];
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
            joc(&a[0], &p[0]);
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
    return 0;
}

