#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <time.h>

using namespace std;

//global variables
int mat[3][3];  //tic-tac-toe matrix
int ord[3][3]; //matrix storing playing order
time_t startTime;
char one[20], two[20];    //player names
int won; //records win, since changes made to matrix to make after-win output better, change result of win()
ofstream fout;

//function prototype list
int win(void);
int tie (void);
void pChoose(int);
void printMat(int);
int eChoose(int);  //return-type made "int" to make exiting function easy
void logMat();
void clrscr();

int main()
{
    int i, j, opt, key;
    char repeat;

    tagForGoto:
    //intialising tic-tac-toe matrix as 0
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
        {
            mat[i][j] = 0;
            ord[i][j] = -1;
        }

    //Menu
    opt = 0;
    key = 0;
    won = 0;

    while(!(opt == 0 && key == 13))
    {
        clrscr();
        if(opt == 0)
        {
            system("color 0A");
            cout<<"Press Q to scroll, ENTER to select.\n\nPLAY\ninstructions\nexit\n\nCreated by AMIT @Pola8976 during the 2020 COVID-19 Pandemic.\n";
        }
        else if(opt == 1)
        {
            system("color 0E");
            cout<<"Press Q to scroll, ENTER to select.\n\nplay\nINSTRUCTIONS\nexit\n\nCreated by AMIT @Pola8976 during the 2020 COVID-19 Pandemic.\n";
        }
        else if(opt == 2)
        {
            system("color 0C");
            cout<<"Press Q to scroll, ENTER to select.\n\nplay\ninstructions\nEXIT\n\nCreated by AMIT @Pola8976 during the 2020 COVID-19 Pandemic.\n";
        }

        //Detecting either scroll(Q) or ENTER
        key = getch();

        //Scroll if Q is pressed
        if(key == 81 || key == 113)
        {
            if(opt >= 0 && opt < 2)
                opt++;
            else if(opt == 2)
                opt = 0;
        }

        //if ENTER is pressed on either INSTRUCTIONS or EXIT
        else if(key == 13)
        {
            if(opt == 1)
            {
                clrscr();
                cout<<"HOW TO PLAY\n1.The game is played on a grid that's 3 squares by 3 squares.\n";
                cout<<"2. You are X, your friend (or the computer in this case) is O. Players take turns putting their marks in empty squares.\n";
                cout<<"3. The first player to get 3 of her marks in a row (up, down, across, or diagonally) is the winner.\n";
                cout<<"4. When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie.\n";
                getch();
            }
            if(opt == 2)
                return 0;
        }
    }

    //setting font color to Bright White and clearing screen
    system("color 0F");
    clrscr();

    //getting current time
    startTime = time(NULL);

    //get player names, one & two
    cout<<"Player 1, enter your name: ";
    gets(one);
    //entering this name as computer starts PvE mode
    cout<<"Player 2, enter your name: ";
    gets(two);

    //count turns
    int turn = 0;


    //PvP
    if((strcmpi(one,"Computer") && strcmpi(one,"cc")) && (strcmpi(two,"Computer") && strcmpi(two,"cc")))
    {
        fout.open("ttt-PvP-log.txt", ios::app);
        while(!win() && !tie())
        {
            printMat(turn);
            pChoose(turn);
            turn++;
        }
    }

    //EvP
    else if((strcmpi(one,"Computer") && strcmpi(one,"cc")) && !(strcmpi(two,"Computer") && strcmpi(two,"cc")))
    {
        fout.open("ttt-PvE-log.txt", ios::app);
        while(!win() && !tie())
        {
            printMat(turn);
            if(turn%2)
                eChoose(turn);
            else
                pChoose(turn);
            turn++;
        }
    }

    //EvP
    else if(!(strcmpi(one,"Computer") && strcmpi(one,"cc")) && (strcmpi(two,"Computer") && strcmpi(two,"cc")))
    {
        fout.open("ttt-EvP-log.txt", ios::app);
        while(!win() && !tie())
        {
            printMat(turn);
            if(turn%2)
                pChoose(turn);
            else
                eChoose(turn);
            turn++;
        }
    }

    //EvE
    else if(!(strcmpi(one,"Computer") && strcmpi(one,"cc")) && !(strcmpi(two,"Computer") && strcmpi(two,"cc")))
    {
        fout.open("ttt-EvE-log.txt", ios::app);
        while(!win() && !tie())
        {
            printMat(turn);
            Sleep(300);
            eChoose(turn);
            turn++;
        }
    }

    //Game ends
    printMat(-1);

    logMat();
    fout.close();

    cout<<"\nWant to play another game (Y/N)?";
    repeat = getch();
    if(repeat == 'Y' || repeat == 'y')
        goto tagForGoto;

    return 0;
}

//user-defined function definitions
void clrscr()
{
    system("cls");
    cout<<"TIC-TAC-TOE"<<endl;
}

void printMat(int turn)
{
    char c = (char) 219;
    clrscr();
    if(turn == -1)
    {
        if(won > 0)
        {
            if(won == 1)
                cout<<one<<" (X) wins!!\n";
            else if(won == 2)
                cout<<two<<" (O) wins!!\n";
            system("color A0");
            Sleep(50);
            system("color B0");
            Sleep(50);
            system("color C0");
            Sleep(50);
            system("color D0");
            Sleep(50);
            system("color E0");
            Sleep(50);
            system("color 0F");
        }
        else if(tie())
        {
            system("color F0");
            Sleep(50);
            system("color 0F");
            Sleep(50);
            system("color F0");
            Sleep(50);
            system("color 0F");
            cout<<"Tie!\n";
        }
        else
            cout<<"CRITICAL ERROR: Neither WIN nor TIE, still came out of loop, exiting...";
    }
    else if(!(turn%2))
        cout<<"It's your turn, "<<one<<" (X),\nUse WASD to navigate. Hit F if you're landlocked. Press ENTER to choose cell.\n";
    else if(turn%2)
        cout<<"It's your turn, "<<two<<" (O),\nUse WASD to navigate. Hit F if you're landlocked. Press ENTER to choose cell.\n";
    cout<<"-------------\n";
    for(int i = 0; i < 3; i++)
    {
        cout<<"|";
        for(int j = 0; j < 3; j++)
        {
            switch(mat[i][j])
            {
                case 0:
                    cout<<"   ";
                    break;
                case 1:
                    cout<<" X ";
                    break;
                case 4:
                    cout<<" O ";
                    break;
                case 13:
                    cout<<" ? ";
                    break;
                case 14:
                    cout<<c<<c<<c;
                    break;
                default:
                    cout<<"CRITICAL ERROR: Value other than 0, 1, 4, 13, 14 found in TicTacToe matrix\n";
            }
            cout<<"|";
        }
        cout<<endl;
    }
    cout<<"-------------";
}

int win()
{
    int i, j, sum;

    //checking row sums
    for(i = 0; i < 3; i++)
    {
        sum = 0;
        for(j = 0; j < 3; j++)
            sum += mat[i][j];
        if(sum == 3 || sum == 12)
        {
            for(j = 0; j < 3; j++)
                mat[i][j] = 14;
            if(sum == 3)
                won = 1;
            else if(sum == 12)
                won = 2;
        }
    }

    //checking column sums
    for(j = 0; j < 3; j++)
    {
        sum = 0;
        for(i = 0; i < 3; i++)
            sum += mat[i][j];
        if(sum == 3 || sum == 12)
        {
            for(i = 0; i < 3; i++)
                mat[i][j] = 14;
            if(sum == 3)
                won = 1;
            else if(sum == 12)
                won = 2;
        }
    }

    if(mat[0][0] + mat[1][1] + mat[2][2] == 3 || mat[0][0] + mat[1][1] + mat[2][2] == 12)
    {
        if(mat[0][0] + mat[1][1] + mat[2][2] == 3)
            won = 1;
        if(mat[0][0] + mat[1][1] + mat[2][2] == 12)
            won = 2;
        mat[0][0] = 14;
        mat[1][1] = 14;
        mat[2][2] = 14;
    }

    if(mat[0][2] + mat[1][1] + mat[2][0] == 3 || mat[0][2] + mat[1][1] + mat[2][0] == 12)
    {
        if(mat[0][2] + mat[1][1] + mat[2][0] == 3)
            won = 1;
        if(mat[0][2] + mat[1][1] + mat[2][0] == 12)
            won = 2;
        mat[0][2] = 14;
        mat[1][1] = 14;
        mat[2][0] = 14;
    }

    return won;
}

int tie()
{
    int flag = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(!mat[i][j])
                flag = 1;
    if(!flag && !win())
        return 1;
    else
        return 0;
}

void pChoose(int turn)
{
    int i, j, r, c, flag = 0, key = 0;

    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(!mat[i][j] && !flag)
            {
                r = i; c = j;
                flag = 1;
            }
    mat[r][c] = 13;
    printMat(turn);


    while(key != 13)
    {
        //W = 87/119 A = 65/97 S = 83/115 D = 68/100 F = 70/102
        key = getch();
        mat[r][c] = 0;

        //W
        if((key == 87 || key == 119) && r != 0)
        {
            if(!mat[r-1][c])
                r--;
            else if(mat[r-1][c] && !mat[r-2][c] && r == 2)
                r -= 2;
        }

        //A
        else if((key == 65 || key == 97) && c != 0)
        {
            if(!mat[r][c-1])
                c--;
            else if(mat[r][c-1] && !mat[r][c-2] && c == 2)
                c -= 2;
        }

        //S
        else if((key == 83 || key == 115) && r != 2)
        {
            if(!mat[r+1][c])
                r++;
            else if(mat[r+1][c] && !mat[r+2][c] && r == 0)
                r += 2;
        }

        //D
        else if((key == 68 || key == 100) && c != 2)
        {
            if(!mat[r][c+1])
                c++;
            else if(mat[r][c+1] && !mat[r][c+2] && c == 0)
                c += 2;
        }

        //F
        else if((key == 70 || key == 102))
        {
            flag = 0;
            for(i = r+1; i <= (r+3); i++)
            {
                for(j = 0; j < 3; j++)
                {
                    if(!mat[i%3][j] && !flag)
                    {
                        r = i%3; c = j;
                        flag = 1;
                    }
                }
            }
        }

        mat[r][c] = 13;
        printMat(turn);
    }

    //if ENTER is pressed
    if(turn%2)
        mat[r][c] = 4;
    else
        mat[r][c] = 1;
    ord[r][c] = turn;
}

int eChoose(int turn)
{
    /* Priorities in descending order:-
        1) One step win
        2) Stop other player from one step win
        3) Two step win
        4) Three step win
        5) Random move
    */
    int i, j, k, r, c, rowSum[3], colSum[3], diaSumLR, diaSumRL, det = turn%2, set[2] = {1, 4}, prio[2][4] = {{2, 8, 1, 0}, {8, 2, 4, 0}}; //det determines who's turn it is

    int storage[24], pos, num;


    for(i = 0; i < 3; i++)
    {
        rowSum[i] = 0;
        for(j = 0; j < 3; j++)
            rowSum[i] += mat[i][j];
    }

    for(j = 0; j < 3; j++)
    {
        colSum[j] = 0;
        for(i = 0; i < 3; i++)
            colSum[j] += mat[i][j];
    }

    diaSumLR = mat[0][0] + mat[1][1] + mat[2][2];
    diaSumRL = mat[0][2] + mat[1][1] + mat[2][0];

    for(k = 0; k < 4; k++)
    {

        for(i = 0; i < 24; i++)
            storage[i] = -1;
        pos = 0;

        for(i = 0; i < 3; i++)
            if(rowSum[i] == prio[det][k])
                for(j = 0; j < 3; j++)
                    if(!mat[i][j])
                    {
                        storage[pos] = i*10 + j;
                        pos++;
                    }

        for(j = 0; j < 3; j++)
            if(colSum[j] == prio[det][k])
                for(i = 0; i < 3; i++)
                    if(!mat[i][j])
                    {
                        storage[pos] = i*10 + j;
                        pos++;
                    }

        if(diaSumLR == prio[det][k])
            for(i = 0; i < 3; i++)
                for(j = 0; j < 3; j++)
                    if(!mat[i][j] && i == j)
                    {
                        storage[pos] = i*10 + j;
                        pos++;
                    }

        if(diaSumRL == prio[det][k])
            for(i = 0; i < 3; i++)
                for(j = 0; j < 3; j++)
                    if(!mat[i][j] && i + j == 2)
                    {
                        storage[pos] = i*10 + j;
                        pos++;
                    }

        srand(time(0));
        if(storage[0] != -1)
        {
            num = rand()%pos;
            r = storage[num] / 10;
            c = storage[num] % 10;
            mat[r][c] = set[det];
            ord[r][c] = turn;
            return 0;
        }
    }

    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(!mat[i][j])
            {
                mat[i][j] = set[det];
                ord[i][j] = turn;
                return 0;
            }

}

void logMat()
{
    fout<<ctime(&startTime);
    fout<<one<<" v. "<<two<<endl;
    fout<<"-------------\t-------------\n";
    for(int i = 0; i < 3; i++)
    {
        fout<<"|";
        for(int j = 0; j < 3; j++)
        {
            if(ord[i][j] == -1)
                fout<<" - |";
            else
                fout<<" "<<ord[i][j]<<" |";
        }

        fout<<"\t";

		fout<<"|";
        for(int j = 0; j < 3; j++)
        {
            switch(mat[i][j])
            {
                case 0:
                    fout<<"   ";
                    break;
                case 1:
                    fout<<" X ";
                    break;
                case 4:
                    fout<<" O ";
                    break;
                case 14:
                    if(won == 1)
                        fout<<" X ";
                    else if(won == 2)
                        fout<<" O ";
                    break;
                default:
                    fout<<"CRITICAL ERROR: Value other than 0, 1, 4, 13, 14 found in TicTacToe matrix\n";
            }
            fout<<"|";
        }
        fout<<"\n";
    }
    fout<<"-------------\t-------------\n";
    if(won == 1)
        fout<<"WIN: X\n*****************\n\n";
    else if(won == 2)
        fout<<"WIN: O\n*****************\n\n";
    else if(tie())
        fout<<"TIE\n*****************\n\n";
}
