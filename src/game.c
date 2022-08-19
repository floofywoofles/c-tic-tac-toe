#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <stdbool.h> 
#include "board.h"

// TODO: Maybe replace int functions with bool with bool.h

int main()
{
    struct Board board = {3,3};
    generateBoard(&board);
    int turns_done = 0;

    int done = 0;

    while(done != 1){
        showBoard(&board);
        
        if(turns_done >= 3){
            if(didSpriteWin(&board,'@') == 1){
                printf("You win!\n");
                done = 1;
            }
        } else {
            int choice;

            printf("\nChoose a spot to put your piece: (1-9)\n");
            printf("\nIf you want to quit, type -1\n\n");

            scanf("%d",&choice);

            if(choice >= 1 && choice <= 9){
                struct Position pos = {-1,-1};
                getSpotOnBoard(&pos,choice);
                
                if(spotIsEmpty(&board,&pos,choice) == 1){ // Checks if true
                    placeSpotOnBoard(&board,&pos,choice);
                    turns_done += 1;
                } else {
                    printf("Spot is full. Please pick another spot\n");
                }
            } else if(choice == -1){
                printf("Quitting the game\n");
                done = 1;
            } else {
                printf("\nPlease choose a valid number\n");
            }
        }

    };
    return 0;
}