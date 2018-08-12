#include <stdio.h>
#include "SPBufferset.h"
#include "MainAux.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main(int i,char** str){
	char *p;
	int seed;
	SP_BUFF_SET();
	if(i>=2){
		seed=strtol(str[1], &p, 10);
		srand(seed);				/*sets the seed*/
	} else{
		srand(5);
	}
	play();
	return 0;

}

