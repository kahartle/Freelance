//This is a program that will calculate a Chew Score//
//Anthony Le - z3420973 - Dillon Giacoppa//
//24th of April, 2017//
//This program will allow the user to enter 5 numbers between 1 and 9. It will then calculate the user's Chew Score//

#include <stdio.h>
#include <string.h>

#define NUMBER 5

int main (void) {
	//Defining variables//
	
	// Define and Initialise 
    int input[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 	// Note array Index starts at ZERO

	// Results
    int score = 0;
    char methodMsg[100];

	// Temp variables
    int tempNumber = 0;
	int tempScore = 0;

	// A better loop and error checking
	for (int idx = 0; idx < NUMBER; idx++)
	{
		// Need to check if the input is a number between 1 and 9
		scanf("%d", &tempNumber);
		if (tempNumber < 1 || tempNumber > 9) {
			// Bad input
			printf("Invalid input: 5 integers 1..9 must be supplied.\n");
			return 1;
		} else {
			input[tempNumber] += 1;
			
			// Get the basic Score - Sum
			score += tempNumber;
		}
	}
	
	// Assume the best score is Sum
	strcpy(methodMsg, "sum");
	
	// Look for 2 dice the same
	// Note:
	//	- At most there can only be 2 duplicates
	//	- [dIdx][0] is the Number duplicated
	//	- [dIdx][1] is the number of times it is duplicated
	int duplicates[2][2] = {{ 0, 0 }, { 0, 0}};
	int dIdx = 0;
	for (int idx = 0; idx <= 9; idx++) {
		if (input[idx] >= 2) {
			if (dIdx == 1 && duplicates[0][1] < input[idx]) {
				// Swap the numbers around so the larger duplicate is in the first index
				tempNumber = duplicates[0][0];
				duplicates[1][0] = tempNumber;
				tempNumber = duplicates[0][1];
				duplicates[1][1] = tempNumber;
				dIdx--;
			}

			duplicates[dIdx][0] = idx;
			duplicates[dIdx][1] = input[idx];
			dIdx++;
		}
	}

	// What is the result of any duplicates
	// Duplicate
	if (duplicates[0][1] == 2) {
		tempScore = 14 + (duplicates[0][0] * 2);
		if (tempScore > score) {
			score = tempScore;
			sprintf(methodMsg, "pair of %d's", duplicates[0][0]);
		}
		// Check if there is a second 
		if (duplicates[1][1] == 2) {
			score = 13 + (duplicates[0][0] * 2) + (duplicates[1][0] * 2);
			sprintf(methodMsg, "%s and a pair of %d's", methodMsg, duplicates[1][0]);
		}
	}
	
	// Triplicate
	if (duplicates[0][1] == 3) {
		score = 15 + (duplicates[0][0] * 3);
		sprintf(methodMsg, "three %d's", duplicates[0][0]);
		// Check if there is a second
		if (duplicates[1][1] == 2) {
			score = 15 + (duplicates[0][0] * 3) + (duplicates[1][0] * 2);
			sprintf(methodMsg, "%s and a pair of %d's", methodMsg, duplicates[1][0]);
		}
	}
	
	// Quadruple
	if (duplicates[0][1] == 4) {
		score = 16 + (duplicates[0][0] * 4);
		sprintf(methodMsg, "four %d's", duplicates[0][0]);
	}
	
	// Pentatude
	if (duplicates[0][1] == 5) {
		score = 17 + (duplicates[0][0] * 5);
		sprintf(methodMsg, "five %d's", duplicates[0][0]);
	}
		
	// Check for a sequence
	int seqStart = 0;
	int seqCount = 0;
	for (int idx = 0; idx <= 9; idx++) {
		// Find the first 
		if (input[idx] >= 1) {
			// Get the first index of the sequence
			if (seqStart == 0) {
				seqStart = idx;
			}
			seqCount = seqCount + 1;
		} else if (seqCount < 4) {
			// If not a significant sequence then (1 2 3 5 6)
			// then reset the values
			seqStart = 0;
			seqCount = 0;
		}
	}

	// What is the result of the Sequence Check
	if (seqCount == 4) {
		tempScore = 25 + (seqStart + 3);
			
		// test that tempScore is bigger than score
		if (score < tempScore) {
			score = tempScore;
			sprintf(methodMsg, "short sequence %d..%d", seqStart, seqStart + 3);
		}
	}
	
	if (seqCount == 5) {
		tempScore = 37 + (seqStart + 4);
			
		// test that tempScore is bigger than score
		if (score < tempScore) {
			score = tempScore;
			sprintf(methodMsg, "long sequence %d..%d", seqStart, seqStart + 4);
		}
	}
			
	// Output the result
	printf("You Chew score is %d: %s.\n", score, methodMsg);
	return 0;


    //No values the same//
    
    
    //1 value the same//


    //2 and 2 same//
    
    //3 and 2 same//
    
    //Sequential dice faces//

    //Invalid Input//
    
    //Highest Value result//


//Output of chew score//


    return 0;
}
