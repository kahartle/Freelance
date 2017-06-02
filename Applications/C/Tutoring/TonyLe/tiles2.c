//This program will allow the user to play C words
//Anthony Le - 17s1 - Dillon Giacoppa
//30th of May 2017
//This program will read in 25 tiles. It will allow the user to place the tiles on a grid. It will then calculate the score for 3, 4 and 5 letter words

#include <stdio.h>
#include <stdlib.h>

#define INPUT 49
#define COLUMNS 5
#define wordsTHREE 24
#define wordsFOUR 20
#define wordsFIVE 10

int main (void) {
    char letter[INPUT] = {0};
    int i = 0, j = 0, k = 0;
    int score[INPUT] = {0};
    char errorMessage = 0;

//This will allow the user to enter their tiles. It will be stored
    printf("Enter 25 tiles: ");
    while (i < INPUT) {
        scanf("%c", &letter[i]); //Store letter to corresponding array
        scanf("%d", &score[i]); //Store number to corresponding array
        i = i + 1;
    }

    
//This will reprint the tiles that were entered
    printf("Tiles: "); //Print out tiles in the listed form ?/? ?/? ?/?...
    i = 0;
    while (i < INPUT) {
        printf("%c", letter [i]);
        printf("/");
        printf("%d ", score[i]);
        i = i + 2;
    }
    printf("\n\n");
//This will go through each tile and allow the user to enter the row and column
    int rowZero[COLUMNS] = {0}; //Defining some arrays and variables
    int rowOne[COLUMNS] = {0};
    int rowTwo[COLUMNS] = {0};
    int rowThree[COLUMNS] = {0};
    int rowFour[COLUMNS] = {0};
    int inputX = 0;
    int inputY = 0;
    i = 0;
    j = 0;
    printf("Enter row and column for each title ...\n"); //This section will allow the user to select the row and column
    while (i < INPUT) {
        printf("Tile #%d: %c/%d? ", i/2 + 1, letter[i], score[i]);
        scanf("%d %d", &inputY, &inputX); //This saves the input in 2 variables
        if (inputY == 0) {//Error checking for each row. If there is no entered value, it will enter the corresponding tile. If there is a tile already allocated to that slot, it will inform of an error and allow the user to reselect
            if (rowZero[inputX] != 0) {
                printf("Error in input\n");
                printf("Tile #%d: %c/%d? ", i/2 + 1, letter[i], score[i]);
                scanf("%d %d", &inputY, &inputX);
            } else {
                rowZero[inputX] = i/2 + 1;
              }
        }
        if (inputY == 1) {
            if (rowOne[inputX] != 0) {
                printf("Error in input\n");
                printf("Tile #%d: %c/%d? ", i/2 + 1, letter[i], score[i]);
                scanf("%d %d", &inputY, &inputX);
            } else {
                rowOne[inputX] = i/2 + 1;
              }
        }
        if (inputY == 2) {
            if (rowTwo[inputX] != 0) {
                printf("Error in input\n");
                printf("Tile #%d: %c/%d? ", i/2 + 1, letter[i], score[i]);
                scanf("%d %d", &inputY, &inputX);                
            } else {
                rowTwo[inputX] = i/2 + 1;
              }
        }
        if (inputY == 3) {
            if (rowThree[inputX] != 0) {
                printf("Error in input\n");
                printf("Tile #%d: %c/%d? ", i/2 + 1, letter[i], score[i]);
                scanf("%d %d", &inputY, &inputX);
            } else {
                rowThree[inputX] = i/2 + 1;
              }
        }
        if (inputY == 4) {
            if (rowFour[inputX] != 0) {
                printf("Error in input\n");
                printf("Tile #%d: %c/%d? ", i/2 + 1, letter[i], score[i]);
                scanf("%d %d", &inputY, &inputX);
            } else {
                rowFour[inputX] = i/2 + 1;
              }
        }
//This section will print out the corresponding board
        printf("    0   1   2   3   4\n");
        printf("0: ");
        while (j < COLUMNS) {
            if (rowZero[j] == 0) {
                printf("./. ");
        } else {
            printf("%c/%d ", letter[(2*rowZero[j] - 2)], score[(2*rowZero[j] - 2)]);
          }
          j = j + 1;
        }
        printf("\n");
        j = 0;
        printf("1: ");
        while (j < COLUMNS) {
            if (rowOne[j] == 0) {
                printf("./. ");
        } else {
            printf("%c/%d ", letter[(2*rowOne[j] - 2)], score[(2*rowOne[j] - 2)]);
          }
          j = j + 1;
        }
        printf("\n");
        j = 0;
        printf("2: ");
        while (j < COLUMNS) {
            if (rowTwo[j] == 0) {
                printf("./. ");
        } else {
            printf("%c/%d ", letter[(2*rowTwo[j] - 2)], score[(2*rowTwo[j] - 2)]);
          }
          j = j + 1;
        }
        printf("\n");    
        j = 0;
        printf("3: ");
        while (j < COLUMNS) {
            if (rowThree[j] == 0) {
                printf("./. ");
        } else {
            printf("%c/%d ", letter[(2*rowThree[j] - 2)], score[(2*rowThree[j] - 2)]);
          }
          j = j + 1;
        }
        j = 0;
        printf("\n");
        printf("4: ");
        while (j < COLUMNS) {
            if (rowFour[j] == 0) {
                printf("./. ");
        } else {
            printf("%c/%d ", letter[(2*rowFour[j] - 2)], score[(2*rowFour[j] - 2)]);
          }
          j = j + 1;
        }
        printf("\n");
        j = 0;
        i = i + 2;
    }

//Calculating the score
    char threeW[wordsTHREE] = {0};
    char fourW[wordsFOUR] = {0};
    char fiveW[wordsFIVE] = {0};

//Words of length 3 score: this part is incorrect -> not sure why, but it doesnt print anything when I run the code
    while (k < 3) {
        strcat(threeW[k], "%s%s%s", letter[rowZero[k]], letter[rowZero[k + 1], letter[rowZero[k + 2]]);
        k = k + 1;
    }
    k = 0;
    printf("threeW[0] = %s", threeW[0]);


//Print out relevant words - 4


//Words of length 4 score


//Print out relevant words - 5


//Words of length 5 score

//Total score

//relist tiles and print out from each row

    return 0;
}
