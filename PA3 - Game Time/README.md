# PA3 - Game Time

This programming assignment is a terminal-based 8-tile puzzle (though it can be of varying size). The user inputs
the size of the puzzle (a perfect square, i.e. 4, 9, 16, etc.), the number of initial moves the program will use to
scramble the board, and a seed that is used to randomize said moves (this allows the user to test the same puzzle
multiple times). The user simply enters a number to make a move; however, entering -1 is a "cheat" that prompts the
program to run an A* search algorithm on the currenet puzzle to determine the best solution.
 
### Compile & Run Instructions
To compile and run the code:
```shell
make
./puzzle size initMoves seed
```

To generate doxygen documentation:
```shell
doxygen config.txt
```
