#ifndef BOARD_H
#define BOARD_H

#include "position.h"

struct Board {
    int height;
    int length;
    char board[3][3];
};

void generateBoard(struct Board *board);
void showBoard(struct Board *board);
void getSpotOnBoard(struct Position *pos, int spot);
int spotIsEmpty(struct Board *board, struct Position *pos, int spot);
void placeSpotOnBoard(struct Board *board, struct Position *pos, int spot);
int isSpriteAdjacent(struct Board *board, struct Position *p1, struct Position *p2);
int isSpriteBeside(struct Board *board, struct Position *p1, struct Position *p2);
int isSpriteBelow(struct Board *board, struct Position *p1, struct Position *p2);
int didSpriteWin(struct Board *board, char sprite);


#endif