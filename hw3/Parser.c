#define _SVID_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DELIMITER " \t\r\n"

/*
 * function gets the input line
 * function returns an int array of size 5.
 *how many elements received is in array[0]
 *actions: set=1 , hint=2, validate=3, restart=4, exit=5 , non of the above=0(saved in array[1])
 *more inputs if received are in array[2], array[3], array[4]
 */
int * Parse(char *input){
	char *token, set[4], hint[5], *p, validate[9], restart[8],exit[5], action;
	static int arr[5]={-1,-1,-1,-1,-1};
	int i;
	strcpy(set,"set");
	strcpy(hint,"hint");
	strcpy(validate,"validate");
	strcpy(restart,"restart");
	strcpy(exit,"exit");
	token=strtok(input, DELIMITER);
	i=1;
	while(token!=NULL && i<5){				/*checks which action is it*/
		if(i==1){
			p=strdup(token);
			if(strcmp(set, p)==0){
				action='1';
			}else if (strcmp(hint, p)==0){
				action='2';
			}else if(strcmp(validate, p)==0){
				action='3';
			}else if(strcmp(restart, p)==0){
				action='4';
			}else if(strcmp(exit, p)==0){
				action='5';
			}else{
				action='6';
			}
			free(p);
			arr[1]=action-'0';
		}
		else{
			arr[i]=*token-'0';		/*a non valid action*/
		}
		i++;

		token= strtok(NULL, DELIMITER);
		}

	arr[0]=i-1;  /*how many elements received*/
	return arr;

}
