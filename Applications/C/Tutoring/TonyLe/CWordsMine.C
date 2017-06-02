#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT_ROWS 3	// Should be 25 - 3 for debugging
#define DISPLAY_ROWS 5
#define DISPLAY_COLS 5

#define SUCCESS 0

#define BAD_INPUT_LETTER 01
#define BAD_INPUT_SCORE 02
#define BAD_INPUT_ROW 11
#define BAD_INPUT_COLUMN 12

// Structure
struct tile
{
	char letter;
	int score;
};

typedef struct tile Tile;

// Function declarations
void print_tiles(Tile input[INPUT_ROWS]);
void print_matrix(Tile display[DISPLAY_ROWS][DISPLAY_COLS]);
int stage0_read_tiles(Tile input[INPUT_ROWS]);
int stage1_place_tiles(Tile input[INPUT_ROWS], Tile display[DISPLAY_ROWS][DISPLAY_COLS]);
int stage2_calculate_score(Tile display[DISPLAY_ROWS][DISPLAY_COLS]);
int readfile(int size, char *filename, Tile display[DISPLAY_ROWS][DISPLAY_COLS]);
int check_for_word(int size, char *word, Tile display[DISPLAY_ROWS][DISPLAY_COLS]);

int main (void) 
{
	// variables
	Tile input[INPUT_ROWS];
	Tile display[DISPLAY_ROWS][DISPLAY_COLS];

	// Stage 0:  Reading tiles
	int result = stage0_read_tiles(input);
	if (result != SUCCESS)
	{
		return result;
	}

	// Initialise display
	for(int row = 0; row < DISPLAY_ROWS; row++)
	{
		for(int col = 0; col < DISPLAY_COLS; col++)
		{
			display[row][col].letter = '.';
			display[row][col].score = -1;
		}
	}

	result = stage1_place_tiles(input, display);
	if (result != SUCCESS)
	{
		return result;
	}
	
	result = stage2_calculate_score(display);
	if (result != SUCCESS)
	{
		return result;
	}

    return 0;
}


// stage0_read_tiles
// Description: Reads the tiles from standard input
// 		Return: SUCCESS, BAD_INPUT_LETTER, BAD_INPUT_SCORE
int stage0_read_tiles(Tile input[INPUT_ROWS])
{
	char letter;
	int score;

	printf("Enter %d tiles: ", INPUT_ROWS);

	for (int idx = 0; idx < INPUT_ROWS; idx++)
	{
		// Input and check if a letter
		scanf(" %c", &letter);
		if (!isalpha(letter)) 
		{
			// Bad input
			printf("Error in input - Bad Letter %d - %c\n", idx, letter);
			return BAD_INPUT_LETTER;
		} else {
			// Input and check if a valid score
			scanf(" %d", &score);
			if (score < 0 || score > 100) 
			{
				// Bad Input
				printf("Error in input - Bad Score %d - %d\n", idx, score);
				return BAD_INPUT_SCORE;
			}
			
			// Store the result
			input[idx].letter = tolower(letter);
			input[idx].score = score;
		}
	}
	
	// Print the tiles
	print_tiles(input);
	
	return SUCCESS;
}

// stage1_place_tiles
// Description:	Reads the tile positions from standard input 
int stage1_place_tiles(Tile input[INPUT_ROWS], Tile display[DISPLAY_ROWS][DISPLAY_COLS])
{
	int row, col;

	printf("Enter row and column for each tile ...\n");
	
	for (int idx = 0; idx < INPUT_ROWS; idx++)
	{	
		do {
			printf("Tile #%d: %c/%d? ", idx, input[idx].letter, input[idx].score);

			// Check row
			scanf(" %d", &row);
			if (row < 0 || row > DISPLAY_ROWS)
			{
				printf("Error in input\n");
				return BAD_INPUT_ROW;
			}
			
			// Check col
			scanf(" %d", &col);				
			if (col < 0 || col > DISPLAY_COLS)
			{
				printf("Error in input\n");
				return BAD_INPUT_COLUMN;
			}
		} while (display[row][col].letter != '.');

		// Store the Tile and display matrix
		display[row][col].letter = input[idx].letter;
		display[row][col].score = input[idx].score;
		print_matrix(display);
	}

	return 0;
}


int stage2_calculate_score(Tile display[DISPLAY_ROWS][DISPLAY_COLS])
{
	char filename[10];
	int result;
	int total = 0;
	
	printf("Words:\n");

	// Read the Files
	for (int size = 3; size <= 5; size++)
	{
		sprintf(filename, "words%d.txt", size);
		
		printf(" - File: %s\n", filename);
		
		result = readfile(size, filename, display);
		printf("Words of length %d = %d\n", size, result);
		total += result;
	}

	printf("\nTOTAL = %d\n", total);
	
	// Print the final display
	for (int row = 0; row < DISPLAY_ROWS; row++)
	{
		for (int col = 0; col < DISPLAY_COLS; col++)
		{
			printf("%c %d ", display[row][col].letter, display[row][col].score);
		}
	}
	printf("\n");
	
	return 0;
}

int readfile(int size, char *filename, Tile display[DISPLAY_ROWS][DISPLAY_COLS])
{
	char word[size];
	FILE *file;
	int result = 0;
	
	file = fopen(filename, "r");
	
	while (fgets(word, sizeof(word), file))
	{
		result += check_for_word(size, word, display);
	}
	
	fclose(file);
	return result;
}

int check_for_word(int size, char *word, Tile display[DISPLAY_ROWS][DISPLAY_COLS])
{
	char compare[size];
	int score;
	int total = 0;
	
	// Across
	for (int row = 0; row < DISPLAY_ROWS; row++)
	{
		for (int col = 0; col < DISPLAY_COLS - size; col++)
		{
			score = 0;
			for (int idx = 0; idx < size; idx++)
			{
				compare[idx] = display[row][col + idx].letter;
				score += display[row][col + idx].score;
			}
						
			if (strncmp(word, compare, size) == 0)
			{
				printf("%s = %d", compare, score);
				total += score;
			}
		}
	}

	// Down
	for (int col = 0; col < DISPLAY_COLS; col++)
	{
		for (int row = 0; row < DISPLAY_ROWS - size; row++)
		{
			score = 0;
			for (int idx = 0; idx < size; idx++)
			{
				compare[idx] = display[row + idx][col].letter;
				score += display[row + idx][col].score;
			}
			
			if (strcmp(word, compare) == 0)
			{
				printf("%s = %d", word, score);
				total += score;
			}
		}
	}
	
	return total;
}

// print_tiles
// Description: Print tiles to standard out 
void print_tiles(Tile tiles[INPUT_ROWS])
{
	printf("Tiles:");

	for (int idx = 0; idx < INPUT_ROWS; idx++)
	{
		printf(" %c/%d", tiles[idx].letter, tiles[idx].score);
	}
	
	printf("\n\n");
}

// print_matrix
// Description: Display the 
void print_matrix(Tile tiles[DISPLAY_ROWS][DISPLAY_COLS])
{
	printf("    0   1   2   3   4\n");
	for (int row = 0; row < DISPLAY_ROWS; row++)
	{
		printf("%d:", row);
		for (int col = 0; col < DISPLAY_COLS; col++)
		{
			if (tiles[row][col].letter != '.')
			{
				printf(" %c/%d", tiles[row][col].letter, tiles[row][col].score);
			} else
			{
				printf(" ./.");
			}
		}
		printf("\n");
	}
	printf("\n");
}

