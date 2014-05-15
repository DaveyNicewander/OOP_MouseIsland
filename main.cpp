#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>

#include "cat.h"
#include "mouse.h"

#define MAX 20
#define SCREEN_HEIGHT 25


using namespace std;

void initializeBoard(int startingBoardArray[MAX][MAX],string &mapName,
                     int &simRuns,int &mapHeight,int &mapWidth,int &currentRow);

void loadBoard(string line, int startingBoardArray[MAX][MAX],
               int currentRow, int mapWidth);

void printBoard(int boardArray[MAX][MAX],int mapWidth,int mapHeight);

void runGame(int startingBoardArray[MAX][MAX], int simRuns,
             int mapWidth,int mapHeight,int &mouseFree,
             int &mouseDrown,int &mouseStarve,int &mouseEaten);

void arrayCopy(int from[MAX][MAX], int to[MAX][MAX]);

void writeResults(string mapName,int simRuns,int seed,int mouseFree,
                  int mouseDrown,int mouseStarve,int mouseEaten);

void wait(int sec);
void clearScreen();



int main()
{
    string mapName;
    string line;
    int mapHeight;
    int mapWidth;
    int simRuns;
    int currentRow = 0;
    int startingBoardArray[MAX][MAX];
    int mouseFree,mouseDrown,mouseStarve,mouseEaten;

    int seed = 0;
    seed = time(NULL);
    srand(time(NULL));

    initializeBoard(startingBoardArray,mapName,simRuns,
                    mapHeight,mapWidth,currentRow);

    runGame(startingBoardArray,simRuns,mapWidth,mapHeight,
            mouseFree,mouseDrown,mouseStarve,mouseEaten);

    writeResults(mapName,simRuns,seed,mouseFree,mouseDrown,mouseStarve,mouseEaten);

    return 0;

}

void printBoard(int boardArray[MAX][MAX],int mapWidth,int mapHeight)
{
    int currentColumn = 0;
    int currentRow = 0;

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (currentColumn >= mapWidth)
            {
                cout << endl;
                cout << endl;
                currentColumn = 0;
                currentRow++;
            }
            if (boardArray[i][j] == 7)
            {
                cout << "";
            }
            else if(boardArray[i][j] != 7)
            {
                cout << boardArray[i][j] << ' ' << ' ';
                currentColumn++;
            }
        }
    }
}

void writeResults(string mapName,int simRuns,int seed,int mouseFree,
                  int mouseDrown,int mouseStarve,int mouseEaten)
{
    ofstream results;
    results.open("MouseIslandResults");
    results << "Map Title: " << mapName << endl;
    results << "Simulation Runs: " << simRuns << endl;
    results << "Random Seed: " << seed << endl;
    results << "Mice Escapes: " << mouseFree << endl;
    results << "Mice Eaten: " << mouseEaten << endl;
    results << "Mice Drowned: " << mouseDrown << endl;
    results << "Mice Starved: " << mouseStarve << endl;
    //Frequency Table here

    results.close();
    return;

}

void initializeBoard(int startingBoardArray[MAX][MAX],string &mapName,
                     int &simRuns,int &mapHeight,int &mapWidth,int &currentRow)
{
    string fileName;
    string line;

    cout << "Enter your filename: ";
    cin >> fileName;


    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            startingBoardArray[i][j] = 7;
        }
    }


    ifstream mapFile(fileName.c_str());
    if (mapFile.is_open())
    {
        getline(mapFile,mapName);
        getline(mapFile,line);
        simRuns = atoi(line.c_str());
        getline(mapFile,line);
        mapHeight = atoi(line.c_str());
        getline(mapFile,line);
        mapWidth = atoi(line.c_str());
        while (getline(mapFile,line))
        {
            loadBoard(line,startingBoardArray,currentRow,mapWidth);
            currentRow++;
        }
        mapFile.close();
    }
    else
    {
        cout << "File Error!" << endl;
    }
    return;
}

void loadBoard(string line,int startingBoardArray[MAX][MAX],
               int currentRow,int mapWidth)
{
    string temp;
    int convertedNum;
    int counter = 0;

    for (int i = 0; i < mapWidth; i++)
    {
        if (line[i] != '-')
        {
            temp = line[i];
            convertedNum = atoi(temp.c_str());
            startingBoardArray[currentRow][counter] = convertedNum;
            counter++;
        }
        else if (line[i] == '-')
        {
            temp = line[i];
            temp += line[i+1];
            convertedNum = atoi(temp.c_str());
            startingBoardArray[currentRow][counter] = convertedNum;
            counter++;
            i++;
        }

    }
    return;
}

void runGame(int startingBoardArray[MAX][MAX],int simRuns,
             int mapWidth,int mapHeight,int &mouseFree,int &mouseDrown,
             int &mouseStarve,int &mouseEaten)
{

    mouseFree = 0;
    mouseDrown = 0;
    mouseEaten = 0;
    mouseStarve = 0;

    while (simRuns > 0) //continue running game
    {

        bool session = true;
        int gameBoardArray[MAX][MAX];
        arrayCopy(startingBoardArray,gameBoardArray);

        Mouse gameMouse;
        gameMouse.findStart(gameBoardArray,mapWidth,mapHeight);
        Cat gameCat;
        gameCat.findStart(gameBoardArray,mapWidth,mapHeight);
        printBoard(gameBoardArray,mapWidth,mapHeight);

        while (session)           //continue with current simulation
        {

            gameMouse.randomMove(gameBoardArray,rand() % 4 + 1,mapWidth,mapHeight);
            gameCat.randomMove(gameBoardArray,rand() % 4 + 1);


            cout << "Press enter to advance..." << endl;
            cin.sync();
            cin.get();
            clearScreen();
            //check for conditions

            if(gameMouse.foundFood())
            {
                gameMouse.eat();
            }

            if((gameMouse.onCat() == true || gameCat.foundMouse() == true) &&
               gameMouse.isSafe() == false)
            {
                //mouse eaten
                mouseEaten++;
                cout << "Mouse eaten by cat!" << endl;
                session = false;
            }
            if(gameMouse.getDrown())
            {
                //mouse drowns
                mouseDrown++;
                cout << "Mouse drowned!" << endl;
                session = false;
            }
            if(gameMouse.getHunger() <= 0)
            {
                //mouse starves
                mouseStarve++;
                cout << "Mouse starved!" << endl;
                session = false;
            }
            if(gameMouse.foundBridge())
            {
                //mouse escape
                mouseFree++;
                cout << "Mouse escaped!" << endl;
                session = false;
            }

            printBoard(gameBoardArray,mapWidth,mapHeight);
            gameMouse.decrementHunger();
        }
        simRuns--;
        if(simRuns > 0)
        {
            cout << "NEW SIMULATION" << endl;
        }
    }
}

void arrayCopy(int from[MAX][MAX], int to[MAX][MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            to[i][j] = from[i][j];
        }
    }
}

void clearScreen()
{
    wait(1);
    cout << string(SCREEN_HEIGHT, '\n');
    return;
}

void wait(int sec)
{
    clock_t endwait;
    endwait = clock() + sec * CLK_TCK;
    while (clock() < endwait)
        {
        }
    return;
}

