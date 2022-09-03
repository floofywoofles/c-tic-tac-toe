#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "board.h"
#include "ai.h"

// TODO: Maybe replace int functions with bool with bool.h

char playersprite = 'X';
char aisprite = 'O';

int main()
{
    struct Board board = {3,3};
    generateBoard(&board);
    int turns_done = 0;

    int done = 0;
    int current_turn = 1; // 1 is player, 2 is AI
    char currSprite;

    while(done != 1){
        switch(current_turn){
            case 1:
                currSprite = playersprite;
                break;
            case 2:
                currSprite = aisprite;
                break;
        };
        showBoard(&board);
        
        if(didSpriteWin(&board,playersprite) || didSpriteWin(&board, aisprite)){
            if(currSprite == aisprite){
                printf("You won!\n");
            } else {
                printf("The AI won!\n");
            }
            done = 1;
        } else if(isBoardFull(&board)){
            printf("No one won\n");
            done = 1;
        } else {
            switch(current_turn){
                case 1:
                    currSprite = playersprite;
                    break;
                case 2:
                    currSprite = aisprite;
                    break;
            };
            int choice;

            if(current_turn == 1){
                printf("\nChoose a spot to put your piece: (1-9)\n");
                printf("\nIf you want to quit, type -1\n\n");

                scanf("%d",&choice);
                if(choice >= 1 && choice <= 9){
                    struct Position pos = {-1,-1};
                    getSpotOnBoard(&pos,choice);
                    
                    if(spotIsEmpty(&board,&pos,choice)){ // Checks if true
                        placeSpotOnBoard(&board,&pos,choice, currSprite);
                        current_turn = 2;
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
            } else {
                chooseSpot(&board, aisprite);
                current_turn = 1;
                turns_done += 1;
            }

        }

    };
    return 0;
}