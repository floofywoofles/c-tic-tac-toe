#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include "position.h"
#include "board.h"

/*
A very basic tic-tac-toe ai for my "very basic" tic-tac-toe

Our AI prioritizes a middle position over anything else
This is primarily because, in this game, that position guarantees a win or a draw.

If the player chooses the middle, then the AI just pickes a random corner
If the AI sees that the player is a spot away from winning, it will block it.
*/


// Sorts by scores
int SCORES_FOR_SET[9];

// Just going to use selection sort, its easy to make
// Its also fast
void sortScores(int *scores[9]){
    for(int p = 0; p < 9; p++){
        for(int l = p; l < 9; l++){
            if(scores[l] < scores[p]){
                int tmp = scores[p];
                scores[p] = scores[l];
                scores[l] = tmp;
            }
        }
    }
}

void getScoreOfSpot(int *scores[9], struct Board *board){
    
}