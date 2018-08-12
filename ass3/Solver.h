
#ifndef SOLVER_H_
#define SOLVER_H_

#include "Game.h"

int solveDeterministicRecursive(Sudoku * s, int *tempBoard, int row, int column);
int solveDeterministic(Sudoku * s);
void optionalValues(Sudoku* s, int row, int column, int* optionalValues);
int randomValue(int* optionalValue);
int solveRandomized(Sudoku* s, int row, int column);

#endif /* SOLVER_H_ */
