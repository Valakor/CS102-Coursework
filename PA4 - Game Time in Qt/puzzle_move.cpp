#include "puzzle_move.h"

// Constructor for starting Board of an A* search
PuzzleMove::PuzzleMove(Board &b)
{
  tileMove_ = -1;
  b_ = new Board(b);
  g_ = 0;
  h_ = 0;
  prev_ = NULL;
}


// Constructor for subsequent search boards 
// (i.e. those returned by Board::potentialMoves() )
PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent)
{
  tileMove_ = tile;
  b_ = new Board(*b);
  h_ = 0;
  prev_ = parent;
  g_ = prev_->g_ + 1;
}


// Destructor
PuzzleMove::~PuzzleMove()
{
  delete b_;
}
  

// Compare two PuzzleMoves based on f distance (needed for priority queue)
bool PuzzleMove::operator<(const PuzzleMove& p) const
{
  if((g_ + h_) < (p.g_ + p.h_)){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ > p.g_)){
    return true;
  }
  else {
    return false;
  }
}


bool PuzzleMove::operator>(const PuzzleMove& p) const
{
  if( (g_ + h_) > (p.g_ + p.h_) ){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ < p.g_) ){
    return true;
  }
  else {
     return false;
  }
  
}


bool PuzzleMove::operator==(const PuzzleMove& p) const
{
  if ((g_ + h_) == (p.g_ + p.h_)) return true;
  return false;
}

