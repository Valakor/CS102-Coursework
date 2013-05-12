# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall
LDFLAGS =

all: puzzle
puzzle : puzzle_solver.o puzzle_move.o board.o pmminlist.o puzzle_heur.o puzzle.o
	@echo "Compiling and linking"
	$(CC) $(CFLAGS) puzzle_solver.o puzzle_move.o board.o pmminlist.o puzzle_heur.o puzzle.o -o puzzle

puzzle.o : puzzle_heur.h puzzle_solver.h board.h puzzle.cpp
	$(CC) $(CFLAGS) -c puzzle.cpp

puzzle_heur.o : puzzle_heur.h puzzle_heur.cpp
	$(CC) $(CFLAGS) -c puzzle_heur.cpp

pmminlist.o : puzzle_move.h pmminlist.h pmminlist.cpp
	$(CC) $(CFLAGS) -c pmminlist.cpp

puzzle_move.o : board.h puzzle_move.h puzzle_move.cpp
	$(CC) $(CFLAGS) -c puzzle_move.cpp

puzzle_solver.o : board.h puzzle_move.h puzzle_solver.h puzzle_solver.cpp
	$(CC) $(CFLAGS) -c puzzle_solver.cpp

board.o : board.h board.cpp
	$(CC) $(CFLAGS) -c board.cpp

clean:
	rm -f puzzle *.o *~ *.gch

