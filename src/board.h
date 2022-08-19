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
int isSpriteAdjacent(struct Board *board, struct Position *p1, struct Position *p2, char sprite);
int isSpriteBeside(struct Board *board, struct Position *p1, struct Position *p2, char sprite);
int isSpriteBelow(struct Board *board, struct Position *p1, struct Position *p2, char sprite);
int didSpriteWin(struct Board *board, char sprite);
int isBoardFull(struct Board *board);
int isRowFull(struct Board *board, int row, int direction,char sprite);

#endif