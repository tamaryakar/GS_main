#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * numFixedCells- asks the user how many filled (fixed) cells does he want and returns it, if the users input is invalid, prints an error
 * play- the game itself
 */

int numFixedCells(int n){
	char str[1024], exit[4];
	int numFixed=0, ok=0;
	do{
		printf("Please enter the number of cells to fill [0-%d]:\n", n-1);
		if(scanf("%d", &numFixed)>0){
			if(numFixed>n-1 || numFixed<0){
				printf("Error: invalid number of cells to fill (should be between 0 and %d)\n", n-1);
			} else{
				ok=1;
			}
		}else{
			scanf("%s", str);
			strcpy(exit,"exit");
			if(strcmp(str,exit)==0 ){
				printf("Exiting...\n");
				return 81;
			}else{
				if(getchar()==EOF){
					printf("Exiting...\n");
					return 81;
				}else{
				printf("Error: invalid number of cells to fill (should be between 0 and %d)\n", n-1);
								}
			}
		}
	}while(ok==0);
	return numFixed;
}


void play(){
	Sudoku* s;
	char c;
	s=puzzleGeneration(3,3);
	if(s==NULL){
		return;
	}
	while((c=getchar())!='\n' && c!= EOF);
	while(!turn(s));
	return;

}
