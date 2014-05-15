#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#define MAX 20

class Mouse
{
public:
    Mouse();

    int getRowPos();
    int getColumnPos();

    int getHunger();
    void decrementHunger();
    void eat();
    bool getDrown();
    bool foundFood();
    bool isSafe();
    bool foundBridge();
    bool onCat();

    void randomMove(int board[MAX][MAX],int directionChoice,int mapWidth,int mapHeight);
    void relocate(int board[MAX][MAX]);

    void findStart(int board[MAX][MAX], int mapWidth, int mapHeight);

private:
    int rowPos,columnPos;

    int hunger;

    int oldTileValue;

    bool drown,food,safe,onBridge,isCat;
};







#endif // MOUSE_H_INCLUDED
