#include "puzzle_heur.h"

int ManhattanHeuristic::compute(int *tiles, int size)
{
  int h_ = 0;
  
  for (int i = 0; i < size; i++)
  {
    if (tiles[i] != 0 && tiles[i] != i)
    {
      h_ += abs((int)(i / sqrt(size)) - (int)(tiles[i] / sqrt(size)));	// Add vertical distance to goal
      h_ += abs(i % (int)sqrt(size) - (tiles[i] % (int)sqrt(size)));	// Add horizontal distance to goal
    }
  }
  
  return h_;
}


int OutOfPlaceHeuristic::compute(int *tiles, int size)
{
  int h_ = 0;
  
  for (int i = 0; i < size; i++)
  {
    if (tiles[i] != i && tiles[i] != 0) h_++;	// If a tile is not in its correct location, increment h_
  }
  
  return h_;
}
