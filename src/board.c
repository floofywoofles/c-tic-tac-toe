#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include "position.h"
#include "board.h"

void generateBoard(struct Board *board)
{
    for (int y = 0; y < board->height; y++)
    {
        for (int x = 0; x < board->length; x++)
        {
            board->board[y][x] = '-';
        };
    };
};

void showBoard(struct Board *board){
    for(int y = 0; y < board->height; y++){
        for(int x = 0; x < board->length; x++){
            printf("%c",board->board[y][x]);
        };
        printf("\n");
    };
};

void getSpotOnBoard(struct Position *pos, int spot){
    if(spot){
        int y = 0;
        int x = 0;

        // As good of a solution as I could get for this
        // We try to get the y value of spot (1-9) by associating it to 0-2 with if statements and switch statements. Could use math, but I am lazy
        // A PR with a better solution would be appreciated
        if(spot >= 1 && spot <= 3){
            y = 0;
            switch(spot){
                case 1:
                    x = 0;
                    break;
                case 2:
                    x = 1;
                    break;
                case 3:
                    x = 2;
                    break;
            }
        } else if(spot >= 4 && spot <= 6){
            y = 1;
            switch(spot){
                case 4:
                    x = 0;
                    break;
                case 5:
                    x = 1;
                    break;
                case 6:
                    x = 2;
                    break;
            }
        } else if(spot >= 7 && spot <= 9){
            y = 2;
            switch(spot){
                case 7:
                    x = 0;
                    break;
                case 8:
                    x = 1;
                    break;
                case 9:
                    x = 2;
                    break;
            }
        } else {
            printf("Spot is out of bounds");
            exit(1);
        }
        if(x >= 0 && y >= 0){
            pos->x = x;
            pos->y = y;
        } else {
            printf("Position variables are null or negative\n");
            printf("{y: %i x: %i}\n",y,x);
            exit(1);
        }
    } else {
        printf("Spot is a null value\n");
        exit(1);
    }
}

int spotIsEmpty(struct Board *board, struct Position *pos, int spot){
    int y = pos->y;
    int x = pos->x;

    if(board && pos){
        if(board->board[y][x] == '-'){
            return 1;
        } else {
            return 0;
        }
    } else {
        printf("Board and/or pos is NULL");
        exit(1);
    }
};

void placeSpotOnBoard(struct Board *board, struct Position *pos, int spot, char sprite){
    if(spot > -1){
        getSpotOnBoard(pos, spot);
    }
    int y = pos->y;
    int x = pos->x;

    if(pos){
        board->board[y][x] = sprite;
    } else {
        printf("Pos (in placement) is null");
        exit(1);
    }
}

// Checks if two sprites are adjacent
int isSpriteAdjacent(struct Board *board, struct Position *p1, struct Position *p2, char sprite){
    if(!p1){
        printf("Position 1 is null");
        exit(1);
    } else if(!p2){
        printf("Position 2 is null");
        exit(1);
    } else {
        int y1 = p1->y;
        int x1 = p1->x;

        int y2 = p2->y;
        int x2 = p2->x;

        // Checks if values are in-bounds of the array
        if(y1+1<=2 || x1+1<=2 || x1-1>=2){
            // Is sprite to bottom right
            if((y1+1) == y2 && (x1+1) == x2){
                return 1;
            } else if((y1+1) == y2 && (x1-1) == x2){ // Is sprite to bottom left
                return 1;
            }
        }
    }

    return 0;
}

int isSpriteBeside(struct Board *board, struct Position *p1, struct Position *p2, char sprite){
    if(!p1){
        printf("Position 1 is null");
        exit(1);
    } else if(!p2){
        printf("Position 2 is null");
        exit(1);
    } else {
        int x1 = p1->x;
        int x2 = p2->x;

        if(x1+1 <= 2){
            if(x1+1 == x2){
                return 1;
            }
        }
    }

    return 0;
};

int isSpriteBelow(struct Board *board, struct Position *p1, struct Position *p2, char sprite){
    if(!p1){
        printf("Position 1 is null");
        exit(1);
    } else if(!p2){
        printf("Position 2 is null");
        exit(1);
    } else {
        int y1 = p1->y;
        int x1 = p1->x;

        int y2 = p2->y;
        int x2 = p2->x;

        if(y1+1<=2){
            if(y1+1 == y2 && x1 == x2){
                if(board->board[y2][x2] == sprite){
                    return 1;
                }
            }
        }
    };

    return 0;
}

int isPositionTaken(struct Board *board, struct Position *pos){
    if(board && pos){
        int y = pos->y;
        int x = pos->x;

        if(board->board[y][x] != '-'){
            return 1;
        }
    } else {
        printf("Board and/or pos is null\n");
        exit(1);
    }

    return 0;
}

// Checks if a row is filled with sprites
// 0 is down, 1 right, 2 is adjacent, 3 is opposite adjacent
// Will use this at some point to replace current implementation for didSpriteWin
int isRowFull(struct Board *board, int row, int direction,char sprite){
    
}

// Checks if a player sprite won. We run this everytime so we don't have to reset variables which could cause issues
int didSpriteWin(struct Board *board, char sprite){
    //TODO:Implement a better solution with less loops maybe
    //TODO:Use isSprite functions
    // Check adjacent matches
    int adj_count = 0; // Counts adjacent matches
    int ver_count = 0;

    while(true){
        // Checks adjacent tiles
        for(int y = 0; y < board->height; y++){
            for(int x = 0; x < board->length;x++){
                if(x == 0){
                    int tmp_x = x;
                    switch(y){
                        case 1:
                            tmp_x += 1;
                            break;
                        case 2:
                            tmp_x += 2;
                            break;
                    }

                    if(board->board[y][tmp_x] == sprite){
                        adj_count += 1;
                    }
                }
            }
        }
        if(adj_count == 3){
            return 1;
        }

        adj_count = 0;
        
        // Checks opposite adjacent tiles
        for(int y = 0; y < board->height; y++){
            for(int x = 0; x < board->length; x++){
                if(x == 2){
                    int tmp_x = x;
                    switch(y){
                        case 1:
                            tmp_x -= 1;
                            break;
                        case 2:
                            tmp_x -= 2;
                            break;
                    }

                    if(board->board[y][tmp_x] == sprite){
                        adj_count += 1;
                    }
                }
            }
        }

        if(adj_count == 3){
            return 1;
        }

        // Checks each horizontal row(s)
        for(int y = 0; y < board->height; y++){
            for(int x = 0; x < board->length; x++){
                if(board->board[y][x] == sprite){
                    ver_count += 1;
                }
            }

            if(ver_count == 3){
                return 1;
            } else {
                ver_count = 0;
            }
        }

        ver_count = 0;
        
        // Checks each vertical row(s)
        for(int y = 0; y < board->length; y++){
            if(board->board[0][y] == sprite){
                if(board->board[1][y] == sprite && board->board[2][y] == sprite){
                    ver_count = 3;
                    break;
                }
            }
        }

        if(ver_count == 3){
            return 1;
        } else {
            ver_count = 0;
        }

        return 0;
    }
}

// Checks if entire board is filled
int isBoardFull(struct Board *board){
    int count = 0;

    for(int y = 0; y < board->height; y++){
        for(int x = 0; x < board->length; x++){
            if(board->board[y][x] != '-'){
                count += 1;
            }
        }
    }

    if(count >= (board->height * board->length)){
        return 1;
    } else {
        return 0;
    }
}