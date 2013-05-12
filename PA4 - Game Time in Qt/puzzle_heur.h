#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H

#include <cmath>
#include <cstdlib>

class PuzzleHeuristic
{
 public:
  virtual int compute(int *tiles, int size) = 0;
};


/**
 * An extension of PuzzleHeuristic. Used to compute the h_ score for the given Board
 * using a Manhattan Heuristic (x-y distance of every tile from its correct
 * location).
 */

class ManhattanHeuristic : public PuzzleHeuristic
{
 public:
  /** Compute the h-score for the given tiles of a Board using a Manhattan Heuristic.
   * @param tiles The tile array whose h-score is being calculated
   * @param size The size of the given tile array
   * @return The heurstic score for the given set of tiles */
  int compute(int *tiles, int size);
};


/**
 * An extension of PuzzleHeuristic. Used to compute the h_ score for the given Board
 * using an Out Of Place Heuristic (number of tiles not in their correct location).
 */

class OutOfPlaceHeuristic : public PuzzleHeuristic
{
 public:
  /** Compute the h-score for the given tiles of a Board using an Out of Place Heuristic.
   * @param tiles The tile array whose h-score is being calculated
   * @param size The size of the given tile array
   * @return The heurstic score for the given set of tiles */
  int compute(int *tiles, int size);
};

#endif
