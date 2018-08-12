CC = gcc
OBJS = main.o Parser.o MainAux.o Solver.o Game.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra \
-Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
main.o: main.c MainAux.h SPBufferset.h
	$(CC) $(COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h
	$(CC) $(COMP_FLAG) -c $*.c
MainAux.o: MainAux.c MainAux.h Game.h 
	$(CC) $(COMP_FLAG) -c $*.c
Solver.o: Solver.c Solver.h Game.h 
	$(CC) $(COMP_FLAG) -c $*.c
Game.o: Game.c Game.h MainAux.h Parser.h Solver.h
	$(CC) $(COMP_FLAG) -c $*.c

clean:
	rm -f $(OBJS) $(EXEC)
