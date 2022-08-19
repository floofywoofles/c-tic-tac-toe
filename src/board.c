#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
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

void placeSpotOnBoard(struct Board *board, struct Position *pos, int spot){
    getSpotOnBoard(pos, spot);
    int y = pos->y;
    int x = pos->x;

    if(pos){
        board->board[y][x] = '@';
    } else {
        printf("Pos (in placement) is null");
        exit(1);
    }
}

// Checks if two sprites are adjacent
int isSpriteAdjacent(struct Board *board, struct Position *p1, struct Position *p2){
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

        if(y1+1<=2 || x1+1<=2 || x1-1>=2){
            // Is sprite to bottom right
            if((y1+1) == y2 && (x1+1) == x2){
                return 1;
            } else if((y1+1) == y2 && (x1-1) == x2){ // Is sprite to bottom left
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0; // False by default if cannot access spot on board
        }
    }

    return 0;
}

int isSpriteBeside(struct Board *board, struct Position *p1, struct Position *p2){
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
            } else {
                return 0;
            }
        } else {
            return 0; // False by default if cannot access spot on board
        }
    }

    return 0;
};

int isSpriteBelow(struct Board *board, struct Position *p1, struct Position *p2){
    if(!p1){
        printf("Position 1 is null");
        exit(1);
    } else if(!p2){
        printf("Position 2 is null");
        exit(1);
    } else {
        int y1 = p1->y;

        int y2 = p2->y;

        if(y1+1<=2){
            if(y1+1 == y2){
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0; // False by default if cannot access spot on board
        }
    };

    return 0;
}

// Checks if a player sprite won. Should only do this if 3 or more sprites are present on the board to prevent unnecessary work
int didSpriteWin(struct Board *board, char sprite){
    //TODO:Implement a better solution with less loops maybe
    // Check adjacent matches
    int adj_count = 0; // Counts adjacent matches

    while(true){
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
            break;
        }

        adj_count = 0;

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
            break;
        }

        return 0;
    }

    return 1;
}