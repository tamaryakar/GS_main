#include "Game.h"
#include <stdio.h>
#include <stdlib.h>

/*The function tries to solve the board with deterministic backtracking algorithm
 * tempBoard- a copy of the game board
 * row, column - the cell we want to solve
 * return 1 if the board is solvable, else returns 0
 */
int solveDeterministicRecursive(Sudoku * s, int *tempBoard, int row, int column){
	int nextNum;
	if(isSolved(s, tempBoard)){
		return 1;
	}
	if(*(tempBoard+row*s->num+column)==0){
		for(nextNum=1; nextNum<=s->num; nextNum++){
			if(isValid(s,tempBoard, nextNum, row, column)){
				*(tempBoard+row*s->num+column)=nextNum;
				/* we are at the last column*/
				if(column==s->num-1){
					if(solveDeterministicRecursive(s,tempBoard, row+1, 0)){
						return 1;
					}
				} else {
					if(solveDeterministicRecursive(s,tempBoard, row, column+1)){
						return 1;
					}
				}
				*(tempBoard+row*s->num+column)=0;
			}
		}
	} else{
		if(column==s->num-1){
			if(solveDeterministicRecursive(s,tempBoard, row+1, 0)){
				return 1;
			}
		} else {
			if(solveDeterministicRecursive(s,tempBoard, row, column+1)){
				return 1;
			}
		}
	}
	return 0;
}
/*The function calls a recursive function to solve the board
 * if there is a solution, it updated the solved_board matrix and returns 1,
 * otherwise, return 0.
 */
int solveDeterministic(Sudoku * s){
	int *tempBoard,r,c, result;
	tempBoard=(int *)malloc(s->boardSize*8);
	if(tempBoard==NULL){
			 printf("Error: malloc has failed\n");
		}
	for(r=0; r<s->num; r++){
		for (c=0; c<s->num; c++){
			*(tempBoard+r*s->num+c)=*(s->board+r*s->num+c);
		}
	}
	result=solveDeterministicRecursive(s,tempBoard,0,0);
	if(result){
		for(r=0; r<s->num; r++){
			for (c=0; c<s->num; c++){
				*(s->solved_board+r*s->num+c)=*(tempBoard+r*s->num+c);
			}
		}
	}
	free(tempBoard);
	return result;
}

/*
 * The function checks all the valid values for board[row][column]
 * optionalValues - an array that the function updates
 * at the end of the function:
 * optionalValues[0]= how many valid values
 * optionalValues[i] (i>0) = the valid values sorted
 */
void optionalValues(Sudoku* s, int row, int column, int* optionalValues){
	int i ,count=0;
	for (i = 1; i <=s->num; i++) {
		if(isValid(s,s->solved_board,i,row,column)){
			optionalValues[count+1]=i;
			count++;
		}
	}
	optionalValues[0]=count;
}
/*
 * The function randomly generates a number from the optionalValue array.
 */
int randomValue(int* optionalValue){
	int randIndex, randValue,i;
	/*no valid values*/
	if(optionalValue[0]==0){
		return 0;
	/*only one valid value*/
	} else if (optionalValue[0]==1){
		optionalValue[0]--;
		return optionalValue[1];
	}
	randIndex=1+(rand()%(optionalValue[0]));
	randValue=optionalValue[randIndex];
	for (i = randIndex; i < optionalValue[0]; i++) {
		optionalValue[i]=optionalValue[i+1];
	}
	optionalValue[0]--;
	return randValue;
}
/*
 * The function solved a sudoku board with randomized backtracking algorithm
 * row, column - the cell we want to solve
 * return 1 if the function was able to solve the board, else return 0
 */
int solveRandomized(Sudoku* s, int row, int column){
	int i, *optionalValuesArr, value=0;
	if(isSolved(s, s->solved_board)){
			return 1;
		}
	optionalValuesArr=(int *)malloc((s->num+1)*8);
	if(optionalValuesArr==NULL){
				 printf("Error: malloc has failed\n");
			}
	for (i = 0; i <=s->num; i++) {
		optionalValuesArr[i]=0;
	}
	optionalValues(s, row, column, optionalValuesArr);
	do{
		value = randomValue(optionalValuesArr);
		/* if value=0, there aren't any valid values for the current cell*/
		if(value!=0){
			*(s->solved_board+row*s->num+column)=value;
			/* we are at the last column*/
			if(column==s->num-1){
				if(solveRandomized(s, row+1, 0)){
					free(optionalValuesArr);
					return 1;
				}
			} else {
				if(solveRandomized(s, row, column+1)){
					free(optionalValuesArr);
					return 1;
				}
			}
			*(s->solved_board+row*s->num+column)=0;
		}
	} while(optionalValuesArr[0]>0); /*while there are valid values for the current cell*/
	free(optionalValuesArr);
	return 0;

}

