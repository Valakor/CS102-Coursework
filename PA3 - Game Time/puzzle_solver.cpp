#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "puzzle_solver.h"
#include "pmminlist.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b)
{
  b_ = new Board(b);
  expansions_ = 0;
}


PuzzleSolver::~PuzzleSolver()
{
  delete b_;
}


int PuzzleSolver::run(PuzzleHeuristic *ph)
{ 
  PMMinList openList;
  BoardSet closedSet;
  vector<PuzzleMove*> garbage;
  int moveCounter = 0;
  
  // Add the start state (start move) to the open list
  PuzzleMove* move = new PuzzleMove(*b_);
  openList.push(move);
  
  // Add initial move's board to the garbage list
  garbage.push_back(move);
  
  // Add the starting board to the closed set
  closedSet.insert(b_);
  
  while (!openList.empty() && !b_->solved())
  {
    // move = remove min. f-value state from open_list
    move = openList.top();
    openList.pop();
    
    // If move is goal node then trace path backwards & break
    if (move->b_->solved())
    {
      PuzzleMove *it = move;
      while (it->prev_ != NULL)
      {
        moveCounter++;
        solutionList.push_back(it->tileMove_);
        it = it->prev_;
      }
      
      // Delete everything in the garbage
      for (unsigned int i = 0; i < garbage.size(); i++)
      {
        delete garbage[i];
      }
      return moveCounter;
    }
    
    // Generate next potential moves (i.e. expansions)
    map<int, Board*> potentialMoves = move->b_->potentialMoves();
    bool inSet = false;
    
    for (map<int, Board*>::iterator itM = potentialMoves.begin(); itM != potentialMoves.end(); ++itM)
    {
      PuzzleMove* s = new PuzzleMove(itM->first , itM->second, move);
      
      inSet = false;
      // Check to see if the current potential move is in the closed set
      for (BoardSet::iterator itS = closedSet.begin(); itS != closedSet.end(); ++itS)
      {
        if (**itS == *(s->b_))
        {
          inSet = true;
          break;
        }
      }
      if (!inSet)
      {
        // Compute h value for the potential move
        s->h_ = ph->compute(s->b_->getTiles(), s->b_->getSize());
        
        // Add the board of s to the closed set
        closedSet.insert(s->b_);
        
        // Add s to the open_list
        openList.push(s);
        
        // Add s's board to the garbage list
        garbage.push_back(s);
        
        // Increment number of expansions
        expansions_++;
      } else delete s;
      
      // Delete the Board objects returned by the Board::potentialMoves() function
      delete itM->second;
    }
  }
  
  // Delete intial move
  delete move;
  return -1;
}


int PuzzleSolver::getNumExpansions()
{
  return expansions_;
}


MyList<int>& PuzzleSolver::getSolution()
{
  return solutionList;
}
