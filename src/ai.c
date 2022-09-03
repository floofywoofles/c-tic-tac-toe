#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "position.h"
#include "ai.h"

// AI just chooses random spots. Too lazy to implement anything better

void chooseSpot(struct Board *board, char sprite){
  int y;
  int x;
  int range = 2;
  int min = 0;
  int done = 0;

  while(!done){
    srand(time(0));

    y = rand() % range + min;

    srand(time(0));

    x = rand() % range + min;
    
    if(x <= range && x >= min){
      if(y <= range && x >= min){
        struct Position pos = {x,y};
        if(!isPositionTaken(board,&pos)){
          placeSpotOnBoard(board, &pos, -1, sprite);
          done = 1;
        }
      } else {
        printf("Y is out of range. y: %d\n",y);
        exit(0);
      }
    } else {
      printf("X is out of range. x: %d\n",x);
      exit(0);
    }
  }

}