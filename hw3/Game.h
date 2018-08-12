#ifndef GAME_H_
#define GAME_H_

#define SEPARATOR "----------------------------------\n"
#define PIPE "| "


typedef struct Sudoku_t{
	int num_column;
	int num_row;
	int num;
	int boardSize;
	int solved;
	int *board;
	int *const_board;
	int *solved_board;

} Sudoku;

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

Sudoku * buildBoard( int column , int row);
void buildConstBoard(Sudoku* s,int numFixedCells);
int isValid(Sudoku* s,int* gameBoard, int n, int r, int c);
int isSolved(Sudoku* s, int* gameBoard);
void printBoard(Sudoku* s);
int turn(Sudoku* s);
void setCell(Sudoku* s, int row, int column , int new_num);
Sudoku* puzzleGeneration(int column, int row);
void deleteSudoku(Sudoku* s);


#endif /* GAME_H_ */
