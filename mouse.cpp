#include "mouse.h"



Mouse::Mouse()
{
    hunger = 100;
    oldTileValue = 0;
    drown = false;
    food = false;
    safe = false;
    onBridge = false;
    isCat = false;
}

int Mouse::getRowPos()
{
    return rowPos;
}

int Mouse::getColumnPos()
{
    return columnPos;
}

int Mouse::getHunger()
{
    return hunger;
}

void Mouse::randomMove(int board[MAX][MAX],int directionChoice,int mapWidth,int mapHeight)
{
    safe = false;
    switch (directionChoice)
    {
        case 1     :board[rowPos][columnPos] = oldTileValue;         //up
                    rowPos--;
                    if (board[rowPos][columnPos] == 2)
                    {
                        isCat = true;
                    }
                    if(board[rowPos][columnPos] == 5)
                    {
                        onBridge = false;
                        drown = true;
                    }
                    if(board[rowPos][columnPos] == 3)
                    {
                        food = true;
                        board[rowPos][columnPos] = 0;
                    }
                    if (board[rowPos][columnPos] == 4)
                    {
                        safe = true;
                    }
                    if ((rowPos == 0 || rowPos == mapHeight) && board[rowPos][columnPos] == 0)
                    {
                        onBridge = true;
                    }
                    if ((columnPos == 0 || columnPos == mapWidth) && board[rowPos][columnPos] == 0)
                    {
                        onBridge = true;
                    }
                    relocate(board);
                    break;

        case 2     :board[rowPos][columnPos] = oldTileValue;           //down
                    rowPos++;
                    if (board[rowPos][columnPos] == 2)
                    {
                        isCat = true;
                    }
                    if(board[rowPos][columnPos] == 5)
                    {
                        onBridge = false;
                        drown = true;
                    }
                    if(board[rowPos][columnPos] == 3)
                    {
                        food = true;
                        board[rowPos][columnPos] = 0;
                    }
                    if (board[rowPos][columnPos] == 4)
                    {
                        safe = true;
                    }
                    if ((rowPos == 0 || rowPos == mapHeight) && board[rowPos][columnPos] == 0)
                    {
                        onBridge = true;
                    }
                    if ((columnPos == 0 || columnPos == mapWidth) && board[rowPos][columnPos] == 0)
                    {
                        onBridge = true;
                    }
                    relocate(board);
                    break;

        case 3     :board[rowPos][columnPos] = oldTileValue;           //left
                    columnPos--;
                    if (board[rowPos][columnPos] == 2)
                    {
                        isCat = true;
                    }
                    if(board[rowPos][columnPos] == 5)
                    {
                        onBridge = false;
                        drown = true;
                    }
                    if(board[rowPos][columnPos] == 3)
                    {
                        food = true;
                        board[rowPos][columnPos] = 0;
                    }
                    if (board[rowPos][columnPos] == 4)
                    {
                        safe = true;
                    }
                    if ((rowPos == 0 || rowPos == mapHeight) && board[rowPos][columnPos] == 0)
                    {
                        onBridge = true;
                    }
                    if ((columnPos == 0 || columnPos == mapWidth) && board[rowPos][columnPos] == 0)
                    {
                        onBridge = true;
                    }
                    relocate(board);
                    break;

        case 4     :board[rowPos][columnPos] = oldTileValue;           //right
                    columnPos++;
                    if (board[rowPos][columnPos] == 2)
                    {
                        isCat = true;
                    }
                    if(board[rowPos][columnPos] == 5)
                    {
                        onBridge = false;
                        drown = true;
                    }
                    if(board[rowPos][columnPos] == 3)
                    {
                        food = true;
                        board[rowPos][columnPos] = 0;
                    }
                    if (board[rowPos][columnPos] == 4)
                    {
                        safe = true;
                    }
                    if ((rowPos == 0 || rowPos == mapHeight) && board[rowPos][columnPos] == 0)
                    {
                        onBridge = true;
                    }
                    if ((columnPos == 0 || columnPos == mapWidth) && board[rowPos][columnPos] == 0)
                    {
                        onBridge = true;
                    }
                    relocate(board);
                    break;

        default    :break;
    }
}

void Mouse::relocate(int board[MAX][MAX])
{
    oldTileValue = board[rowPos][columnPos];
    board[rowPos][columnPos] = 1;
}

void Mouse::findStart(int board[MAX][MAX], int mapWidth, int mapHeight)
{
    for (int i=0; i < mapHeight; i++)
    {
        for (int j=0; j < mapWidth; j++)
        {
            if (board[i][j] == 1)
            {
                rowPos = i;
                columnPos = j;
            }
        }
    }
}

void Mouse::decrementHunger()
{
    hunger--;
}

void Mouse::eat()
{
    hunger = 100;
    food = false;
}

bool Mouse::getDrown()
{
    return drown;
}

bool Mouse::foundFood()
{
    return food;
}

bool Mouse::isSafe()
{
    return safe;
}

bool Mouse::foundBridge()
{
    return onBridge;
}

bool Mouse::onCat()
{
    return isCat;
}
