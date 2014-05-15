#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#define MAX 20

class Cat
{
public:

    Cat();

    int getRowPos();
    int getColumnPos();

    bool nearBridge();
    bool foundMouse();

    void randomMove(int board[MAX][MAX],int directionChoice);
    void relocate(int board[MAX][MAX]);


    void findStart(int board[MAX][MAX], int mapWidth, int mapHeight);


private:

    int rowPos,columnPos;
    int oldTileValue;
    bool bridge;
    bool onMouse;

};




#endif // CAT_H_INCLUDED
