#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc != 4){
    cerr << "Usage: ./puzzle size initMoves seed" << endl;
    return 0;
  }

  int size, initMoves, seed;

  size = atoi(argv[1]);
  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]);

  // Create the initial Board
  Board b(size,initMoves,seed);
  
  PuzzleHeuristic* puzzleHeur;
  PuzzleSolver* puzzleSolver;
  
  
  // Gameplay loop
  int move = -2;
  while(!b.solved())
  {
    cout << endl << "--------------------" << endl << endl;
    cout << b << endl;
    
    // Query user for input, ask again if unexpected input
    do
    {
      cout << "Enter tile number to move or -1 to cheat:  ";
      cin >> move;
      if (cin.fail())
      {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "    --Invalid input! Enter a valid integer corresponding to a tile move." << endl << endl;
        continue;
      }
      break;
    } while(true);
    cin.ignore(1024, '\n');
    
    if (move == -1) // Cheat
    { 
      // Choose either the OutOfPlaceHeuristic or ManhattanHeuristic
      puzzleHeur = new ManhattanHeuristic();
      //puzzleHeur = new OutOfPlaceHeuristic();
      
      // Create a PuzzleSolver object and run the A* algorithm
      // If -1 is returned, no moves were performed and the Board was already solved
      // The Heuristic should never not solve a Board considering the initial
      //     Board constructor only makes valid moves to create a scrambled Board
      puzzleSolver = new PuzzleSolver(b);
      if (puzzleSolver->run(puzzleHeur) == -1)
      {
      	cout << endl << "Already solved!" << endl;
      } else {
        
        // Retrieve and print out the solution list
        cout << endl << "Try this sequence: ";
        for (int i = (puzzleSolver->getSolution()).size() - 1; i >= 0; i--)
        {
          cout << (puzzleSolver->getSolution())[i] << " ";
        }
        cout << endl << "(Expansions = " << puzzleSolver->getNumExpansions() << ")" << endl;
      }
        
      // Remove all dynamically allocated objects that are no longer needed      
      delete puzzleHeur;
      delete puzzleSolver;
    } else b.move(move);	// If cheat is not input, move the selected tile into the empty space
  }
  
  cout << endl << endl;
  cout << b << endl;
  cout << "--------------------" << endl << endl;
  cout << "You Win!" << endl << "CONGRATULATIONS!!!" << endl;
  
  return 1;
}
