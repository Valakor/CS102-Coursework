#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <queue>
#include <vector>
#include <deque>
#include <set>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "mylist.h"


/** A class to solve an unsolved '8'-puzzle using an A* algorithm. */


class PuzzleSolver
{
 public:
  /** Typedef for the closed-list set. Declare a closed set variable as
   * 'BoardSet closedSet;'
   * when you write your code for the run() function. */
  typedef std::set<Board *, BoardLessThan> BoardSet;

  /** Constructor that makes a copy of the Board and stores it.
   * @param b Board that will be solved */
  PuzzleSolver(const Board &b);

  /** Destructor. */
  ~PuzzleSolver();

  /** Run the A* search to solve the Board.
   * @param ph A pointer to the Puzzle Heuristic that is being used
   * (Either ManhattanHeuristic or OutOfPlaceHeuristic)
   * @return -1 if the original Board was already solved or
   * the number of moves in the solution */
  int run(PuzzleHeuristic *ph);

  /** Get the list of solutions to solve the current Board.
   * @return A list of type MyList<int> that contains a solution
   * to the current Board */
  MyList<int>& getSolution();

  /** Get the number of expansions that were performed in the search.
   * @return An int corresponding to the number of expansions performed in the search */
  int getNumExpansions();

 private:
  Board* b_;				///< A pointer to the original Board
  int expansions_;			///< The number of expansions performed during the A* search
  MyList<int> solutionList;	///< The solution list that contains the moves necessary to solve the Board
};

#endif
