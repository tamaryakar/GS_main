#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "Solver.h"
#include "Game.h"
#include "MainAux.h"

/*
 * isValid - checks if it is possible to fill int n into sudoku[r][c]
 * buildBoard- creates a new object- board
 * buildConstBoard- randomly chooses the placing of all fixed cells and updates const_board with them
 * printBoard- prints the game board
 * isSolved- checks if the sudoku is solved
 * deleteSudoku- deletes the sudoku, frees all memory allocation
 * setCell- set cell sudoku[c][r] if it is not a const, if it is- do nothing
 * puzzleGeneration- generates a new game-calls build board, numoffixedcells, initializes const board, and prints the new board
 */

Sudoku * buildBoard( int column , int row){
	int c,r;
	Sudoku* s=(Sudoku*) malloc(sizeof(Sudoku));
	s->num_column=column;
	s->num_row=row;
	s->num=s->num_column*s->num_row;
	s->boardSize=s->num*s->num;
	s->solved=0;
	s->board=(int *)malloc(s->boardSize*8);
	s->const_board=(int *)malloc(s->boardSize*8);
	s->solved_board=(int *)malloc(s->boardSize*8);

	if(s->board==NULL || s->const_board==NULL || s->solved_board==NULL ){
		 printf("Error: malloc has failed\n");
	}
	/*create empty board game*/
	for(r=0; r<s->num; r++){
			for (c=0; c<s->num; c++){
				*(s->board+r*s->num+c)=0;
				*(s->const_board+r*s->num+c)=0;
				*(s->solved_board+r*s->num+c)=0;
			}
	}
	solveRandomized(s,0,0);
	return s;
}

void buildConstBoard(Sudoku* s,int numFixedCells){
	int i=0, row ,column;
	while(i<numFixedCells){
		column=rand()%(s->num);
		row=rand()%(s->num);
		if(*(s->board+row*s->num+column)==0){
			*(s->const_board+row*s->num+column)=1;		/* put 1 wherever there is a const number*/
			i++;
			*(s->board+row*s->num+column)=*(s->solved_board+row*s->num+column);
		}
	}

}

int isValid(Sudoku* s,int* gameBoard, int n, int r, int c){
	int i, bc, br;
	bc = c - c%s->num_column;
	br= r- r%s->num_row;
	/* checks if n exists in the row r or the column c*/
	if(*(gameBoard+r*s->num+c)==n){
		return 1;
	}
	for (i=0; i<s->num; i++){
		if(*(gameBoard+r*s->num+i)==n || *(gameBoard+i*s->num+c)==n){
			return 0;
		}
	}
	/*checks if n exists in the box*/
	for (r = br; r<br+s->num_row; r++) {
		for(c=bc; c<bc+s->num_column; c++){
			if(*(gameBoard+r*s->num+c)==n){
				return 0;
			}
		}
	}
	return 1;
}

int isSolved(Sudoku* s, int* gameBoard){
	int r,c;
	for(r=0; r<s->num; r++){
		for(c=0;c<s->num;c++){
			if(*(gameBoard+r*s->num+c)==0){
				return 0;
			}
		}
	}
	return 1;
}

void printBoard(Sudoku* s){
	int r, c, temp;
	for(r=0; r<s->num; r++){
		temp=(int)s->num_row;
		temp=r%temp;
		if(temp==0){
			printf(SEPARATOR);
		}
		for (c=0; c<s->num; c++){
			if(c%s->num_column==0){
				printf(PIPE);
			}
			if(*(s->board+r*s->num+c)==0){
				printf("   ");
			} else if(*(s->const_board+r*s->num+c)==1){
				printf(".%d ", *(s->board+r*s->num+c));
			} else{
				printf(" %d ", *(s->board+r*s->num+c));
			}
		}
		printf("|\n");
	}
	printf(SEPARATOR);
}

int turn(Sudoku* s){
	int *input_arr, action, hint_value,arr2, arr3, numOfWords;
	char input[1024];

	if(fgets(input,1025,stdin)==NULL){
		printf("Exiting...\n");
		deleteSudoku(s);
		return 1;
	}
	input_arr=Parse(&input[0]);
	numOfWords=*(input_arr);
	action=*(input_arr+1);
	arr2=*(input_arr+3)-1;		/*row*/
	arr3=*(input_arr+2)-1;		/*column*/
	if(numOfWords==0){			/*checks if any input was received*/
		return 0;
	}
	switch(action){
		case 1:{
			if(!s->solved){		/*allow only exit or restart if board is solved */
				if(numOfWords<4){			/*checks if enough input was received*/
					printf("Error: invalid command\n");
					return 0;
				}
				setCell(s, arr2, arr3, *(input_arr+4));
				if(isSolved(s, s->board)){
					printf("Puzzle solved successfully\n");
					s->solved=1;
					/*allow only exit or restart from here */
				}
			}else{
				printf("Error: invalid command\n");
			}

			return 0;
		}
		case 2:{
			if(!s->solved){		/*allow only exit or restart if board is solved */
				if(numOfWords<2){			/*checks if enough input was received*/
					printf("Error: invalid command\n");
					return 0;
				}

			hint_value=*(s->solved_board+arr2*s->num+arr3);
			printf("Hint: set cell to %d\n",hint_value);
			}else{
				printf("Error: invalid command\n");
			}

			return 0;
		}
		case 3:{
			if(!s->solved){		/*allow only exit or restart if board is solved */
				if(solveDeterministic(s)){
					printf("Validation passed: board is solvable\n");
				}else{
					printf( "Validation failed: board is unsolvable\n");
				}
			}else{
					printf("Error: invalid command\n");
				}
			return 0;
		}
		case 4:{
			deleteSudoku(s);
			play();
			return 1;
		}
		case 5:{
			printf("Exiting...\n");
			deleteSudoku(s);
			return 1;
		}
		case 6:{
			printf("Error: invalid command\n");		/*a non valid action*/
		}
	}
	return 0;

}

void setCell(Sudoku* s, int row, int column , int new_num){
	if(*(s->const_board+row*s->num+column)==0){
		if(new_num==0){
			*(s->board+row*s->num+column)=0;
			printBoard(s);
			return;
		}else{
			if(isValid(s, s->board, new_num, row,column)==1 ){
				*(s->board+row*s->num+column)=new_num;
				printBoard(s);
			}else{
				printf("Error: value is invalid\n");
				return;
			}
		}
		}else{
			printf("Error: cell is fixed\n");
		}
}
Sudoku* puzzleGeneration(int column, int row){
	int n;
	Sudoku* s;
	s=buildBoard(column,row);
	n=numFixedCells(s->num*s->num);
	if(n==81){
		return NULL;
	}
	buildConstBoard(s,n);
	printBoard(s);
	return s;

}

void deleteSudoku(Sudoku* s){
	if(!s){
		return;
	}
	free(s->solved_board);
	free(s->const_board);
	free(s->board);
	free(s);
	return;

}
