#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include <functional>
#include "board.h"
#include "puzzle_heur.h"

/** Represents a single potential move, storing the tile that would be
 * moved and the resulting Board. */

class PuzzleMove
{
 public:
  /** Constructor for the starting Board of an A* search.
   * @param b The original Board with no parent */
  PuzzleMove(Board &b);

  /** Constructor for subsequent search Boards with a parent Board.
   * (i.e. Those returned by Board::potentialMoves())
   * @param tile The tile that was moved to create the Board this PuzzleMove represents
   * @param b The Board this PuzzleMove represents
   * @param parent The previous Board that created the current Board */
  PuzzleMove(int tile, Board *b, PuzzleMove *parent);

  /** Default destructor. Deletes the local Board. */
  ~PuzzleMove();

  /** Operator < overload.
   * @return True if the f-score of the Board on the left is less than the 
   * f-score of the Board on the right */
  bool operator<(const PuzzleMove& p) const;
  
  /** Operator > overload.
   * @return True if the f-score of the Board on the left is greater than the 
   * f-score of the Board on the right */
  bool operator>(const PuzzleMove& p) const;
  
  /** Operator == overload.
   * @return True if the f-score of the Board on the left is equal to the 
   * f-score of the Board on the right */
  bool operator==(const PuzzleMove& p) const;


 public:
  int tileMove_;  	 /**< Tile moved to reach the Board b */
  Board *b_;     	 /**< Pointer to a board representing the updated state */
  int g_;        	 /**< Distance from the start board */
  int h_;        	 /**< Heuristic distance to the goal */
  PuzzleMove *prev_; /**< Pointer to parent PuzzleMove */
};


// Leave this alone and don't touch it!
struct PuzzleMoveGreater : 
  public std::binary_function<const PuzzleMove*, const PuzzleMove*,bool>
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    return *m1 > *m2;
  }
};

#endif
