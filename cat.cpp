#include "cat.h"


Cat::Cat()
{
    oldTileValue = 0;
    bridge = false;
    onMouse = false;
}

int Cat::getRowPos()
{
    return rowPos;
}

int Cat::getColumnPos()
{
    return columnPos;
}

void Cat::randomMove(int board[MAX][MAX], int directionChoice)
{
    onMouse = false;
    switch (directionChoice)
    {
        case 1     :board[rowPos][columnPos] = oldTileValue;         //up
                    rowPos--;
                    if(board[rowPos][columnPos] == 5)
                    {
                        rowPos++;
                    }
                    if(board[rowPos][columnPos] == 1)
                    {
                        onMouse = true;
                    }
                    relocate(board);
                    break;

        case 2     :board[rowPos][columnPos] = oldTileValue;           //down
                    rowPos++;
                    if(board[rowPos][columnPos] == 5)
                    {
                        rowPos--;
                    }
                    if(board[rowPos][columnPos] == 1)
                    {
                        onMouse = true;
                    }
                    relocate(board);
                    break;

        case 3     :board[rowPos][columnPos] = oldTileValue;           //left
                    columnPos--;
                    if(board[rowPos][columnPos] == 5)
                    {
                        columnPos++;
                    }
                    if(board[rowPos][columnPos] == 1)
                    {
                        onMouse = true;
                    }
                    relocate(board);
                    break;

        case 4     :board[rowPos][columnPos] = oldTileValue;           //right
                    columnPos++;
                    if(board[rowPos][columnPos] == 5)
                    {
                        columnPos--;
                    }
                    if(board[rowPos][columnPos] == 1)
                    {
                        onMouse = true;
                    }
                    relocate(board);
                    break;

        default    :break;
    }
}

void Cat::relocate(int board[MAX][MAX])
{
    oldTileValue = board[rowPos][columnPos];
    board[rowPos][columnPos] = 2;
}

void Cat::findStart(int board[MAX][MAX], int mapWidth, int mapHeight)
{
    for (int i=0; i < mapHeight; i++)
    {
        for (int j=0; j < mapWidth; j++)
        {
            if (board[i][j] == 2)
            {
                rowPos = i;
                columnPos = j;
            }
        }
    }
}

bool Cat::nearBridge()
{
    return bridge;
}

bool Cat::foundMouse()
{
    return onMouse;
}
