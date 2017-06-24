//This program will allow the user to play C words
//Anthony Le - 17s1 - Dillon Giacoppa
//30th of May 2017
//This program will read in 25 tiles. It will allow the user to place the tiles on a grid. It will then calculate the score for 3, 4 and 5 letter words(did not complete this part)

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT_ROWS 25
#define DISPLAY_ROWS 5
#define DISPLAY_COLS 5

#define SUCCESS 0

#define BAD_INPUT_LETTER 01
#define BAD_INPUT_SCORE 02
#define BAD_INPUT_POSITION 11

// Structure
struct tile {//defining the variables within the struct
    char letter;
    int score;
};

typedef struct tile Tile;

// KH - Yeah I know I did this ... I was rushing and breaking rules.
// 		You should have global variables by rights ... 
//		Declare the arrays in main and pass them around like this
//		int method_name(Tile display[DISPLAY_ROWS][DISPLAY_COLS])

// Global variables
Tile input[INPUT_ROWS];
Tile display[DISPLAY_ROWS][DISPLAY_COLS];

// Function declarations
void print_tiles(Tile tiles[INPUT_ROWS]);
void print_matrix(Tile tiles[DISPLAY_ROWS][DISPLAY_COLS]);
int stage0_read_tiles();
int stage1_place_tiles();
int stage2_calculate_score();

int main (void) {
    //Stage 0:  Reading tiles
    int result = stage0_read_tiles();
    if (result != SUCCESS) {
        return result;
    }
    
    //Initialising the display of the matrix
    for(int row = 0; row < DISPLAY_ROWS; row++)	{
        for(int col = 0; col < DISPLAY_COLS; col++) {
            display[row][col].letter = '.';//This will set all letters to . and all scores to -1
            display[row][col].score = -1;//We can then tell that a part of the matrix has not been allocated with a tile as its score would be -1
        }
    }
    result = stage1_place_tiles();//Allows user to pick where to place tiles
    if (result != SUCCESS) {
        return result;
    }
    
    result = stage2_calculate_score();//Calculates the score
    if (result != SUCCESS)
    {
        return result;
    }
    
    // KH - This should be - return SUCCESS;
    return 0;
}
//Defining how functions work
//stage0_read_tiles
//Reads the tiles from stdin
//Will return: SUCCESS, BAD_INPUT_LETTER, BAD_INPUT_SCORE depending on input
int stage0_read_tiles()
{
    char letter;
    int score;
    
    printf("Enter %d tiles: ", INPUT_ROWS);//ask for entry of tiles
    
    for (int i = 0; i < INPUT_ROWS; i++) {
        // Input and check if a letter
        scanf(" %c", &letter);
        if (!isalpha(letter)) {
        
        	// KH - By the assignment brief all errors should be just "Error in input"
        	//		I added the extra "Bad Letter/Score" for testing.
  	
            // Bad input
            printf("Error in input - Bad Letter %d - %c\n", i, letter);
            return BAD_INPUT_LETTER;
        } else {
            // Input and check if a valid score
            scanf(" %d", &score);
            if (score < 0 || score > 100) {
                // Bad Input
                printf("Error in input - Bad Score %d - %d\n", i, score);
                return BAD_INPUT_SCORE;
            }
            // Store the result
            input[i].letter = tolower(letter);//if entered as upper case will be saved as lower case
            input[i].score = score;
        }
    }
    // Print the tiles
    print_tiles(input);
    
    return SUCCESS;
}
//stage1_place_tiles
//Allows for input for the location of each tile, i.e. select where the tile is placed
int stage1_place_tiles() {
    printf("Enter row and column for each tile ...\n");
    for (int i = 0; i < INPUT_ROWS; i++) {
        printf("Tile #%d: %c/%d?", i + 1, input[i].letter, input[i].score);
        int row = 0, col = 0;
        scanf("%d %d", &row, &col);
        if (display[row][col].score == -1) {//Only input if no tile has been allocated here
            display[row][col].letter = input[i].letter;
            display[row][col].score = input[i].score;
        } else {
            i = i - 1;
        }
        Tile tiles[DISPLAY_ROWS][DISPLAY_COLS];
        print_matrix(tiles);
    }
    return 0;
}


// KH - It is bad form to have Global Variables.
//		Move this declaration into stage2_calculate_score.
//		Also the dimensions are not correct. By the brief there are a maximum of 5000
//		words per file and there are 3 sets of words. So it should be:
//			 [3][5000][5] - 3 sets of words of 5000 words of a maximum 5 characters
//		The search loop can then work over each word set with a loop like:
//			for (int wrd = 0; wrd < WRD_SETS (#define WRD_SETS 3) ; wrd++)
//				compare words[wrd][wrd_idx] with display character
//				print ("Words of length %d", wrd + 3)

char words[20000][5];


int stage2_calculate_score()
{
    int n = 0;
    
    // For each of the lengths (3, 4, 5) open the corresponding
    // dictionary file and read the words from there
    char buff[20];
    FILE* f3 = fopen("words3.txt", "r");
    while (fscanf(f3, "%s", buff) != EOF) {
        
        // KH - strcpy(words[0][n], buff) 
    	//		OR if you are not sure the words are terminated correctly
    	//			  strncpy(words[0][n], buff, strlen(buff))
    	// NOTE: words[0][n] is a pointer to the next 5 cells of memory,
    	//		 likewise buff is also a pointer to the next 20 cells of memory.
    	//		 This saves you having to move things one character at a time.
        
        for (int i = 0; i < strlen(buff); i++)
            words[n][i] = buff[i];
        n++;
    }
    fclose(f3);
    FILE* f4 = fopen("words4.txt", "r");
    while (fscanf(f4, "%s", buff) != EOF) {
        
        // KH - strcpy(words[1][n], buff) 
    	//		OR if you are not sure the words are terminated correctly
    	//			  strncpy(words[1][n], buff, strlen(buff))
        
        for (int i = 0; i < strlen(buff); i++)
            words[n][i] = buff[i];
        n++;
    }
    fclose(f4);
    FILE *f5 = fopen("words5.txt", "r");
    while (fscanf(f5, "%s", buff) != EOF) {
        
        // KH - strcpy(words[2][n], buff) 
    	//		OR if you are not sure the words are terminated correctly
    	//			  strncpy(words[2][n], buff, strlen(buff))
        
        for (int i = 0; i < strlen(buff); i++)
            words[n][i] = buff[i];
        n++;
    }
    fclose(f5);
    
    // KH - This OK but my preference is to declare all variables at the top of the
    //		method. If you do more programming it will make sense why - it is a style
    //		thing so it is ok either way
    int totalScore = 0;
    
    
    // KH - While technically OK to use variable names like i, j, w & n it makes it hard
    //		to follow what the variable is for. It took me a bit to workout "n" comes 
    //		from the code above.
    //		Can I suggest you rename i -> row, j -> col, w -> wrd, n -> something??
    //		To get a result like the assignment brief you need to move your for loops
    //		around. You have it pretty much right. The order is:
    //			for each word size
    //				-- Horizontal word search
    //				for each row
    //					for each column
    //						look for the words
    //
    //				-- Vertical word search
    //				for each column
    //					for each row
    //						look for each word			
    //
    //				Print "Words of length %wrd + 3 = %wrd_total"
    //				grand_total += word_total
    //
	//			print "TOTAL = %grand_total
    //
    //	The code for the word search is giving you grief for the 5 letter words.
    //	A simpler method would be to use strncmp. Copy the letters from the display into
    //  a char array and then 
    //		if (strncmp(char_array_compare, words[wrd][wrd_idx], word_size) == 0)
    //			-- found a word so add up the letters and print the value
    //	There is a tricky bit in that the word "beats" is made up of a few words:
    //		eat, beat, eats, beats
    //	So for the char_array_compare for the shorter words you have to take the first 
    //  few letters and do the check - (3) bea, eat, ats, (4) beat, eats, (5) beats.
    //	I originally tried to do the word search on the display array but the part
    //	words gave me grief. Of course the vertical words it needed it anyway.
    
    printf("\n");
    // Check horizontal ones
    for (int i = 0; i < DISPLAY_ROWS; i++) {
        for (int j = 0; j < DISPLAY_COLS; j++) {
            for (int w = 0; w < n; w++) {
                // Now, we want to check if cells
                // (i,j), (i,j+1) ... (i,j+length(words[w])-1) form words[w]
                // If they do, score needs to be updated
                
                if (j + strlen(words[w]) - 1 >= DISPLAY_COLS) continue;
                int form = 1;
                int accumulatedScore = 0;
                for (int q = 0; q < strlen(words[w]); q++) {
                    if (display[i][j + q].letter != words[w][q]) {
                        form = 0;
                        break;
                    }
                    accumulatedScore += display[i][j + q].score;
                }
                if (form) {
                    printf("%s = %d\n", words[w], accumulatedScore);
                    totalScore += accumulatedScore;
                }
            }
        }
    }
    
    // Check vertical ones
    for (int i = 0; i < DISPLAY_ROWS; i++) {
        for (int j = 0; j < DISPLAY_COLS; j++) {
            for (int w = 0; w < n; w++) {
                // Now, we want to check if cells
                // (i+1,j), (i+2,j) ... (i+length(words[w])-1,j) form words[w]
                // If they do, score needs to be updated
                if (i + strlen(words[w]) - 1 >= DISPLAY_ROWS) continue;
                int form = 1;
                int accumulatedScore = 0;
                for (int q = 0; q < strlen(words[w]); q++) {
                    if (display[i + q][j].letter != words[w][q]) {
                        form = 0;
                        break;
                    }
                    accumulatedScore += display[i + q][j].score;
                }
                if (form) {
                    printf("%s = %d\n", words[w], accumulatedScore);
                    totalScore += accumulatedScore;
                }
            }
        }
    }
    
    printf("\nTOTAL = %d\n", totalScore);
    
    return 0;
}
//print_tiles
//This will reprint the tiles
void print_tiles(Tile tiles[INPUT_ROWS]) {
    printf("Tiles:");
    //Print out the tiles
    for (int i = 0; i < INPUT_ROWS; i++) {
        printf(" %c/%d", tiles[i].letter, tiles[i].score);
    }
    printf("\n\n");
}
//print_matrix
//This defines the function print_matrix, it is used in the entering of the tiles to print the 5x5 matrix
void print_matrix(Tile tiles[DISPLAY_ROWS][DISPLAY_COLS]) {
    printf("    0   1   2   3   4 \n");
    for (int row = 0; row < DISPLAY_ROWS; row++) {
        printf("%d:", row);
        for (int col = 0; col < DISPLAY_COLS; col++) {        
            if (display[row][col].score != -1) {
                printf(" %c/%d", display[row][col].letter, display[row][col].score);
            } else {
                printf(" ./.");
            }
        }
        printf("\n");
    }
}
