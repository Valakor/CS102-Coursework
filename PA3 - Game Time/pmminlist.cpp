#include "puzzle_move.h"
#include "pmminlist.h"

/*
 * Default Constructor. Instantiates a list of PuzzleMove*.
 */
PMMinList::PMMinList() : slist_()
{
  
}


/*
 * Destructor. Empty.
 */
PMMinList::~PMMinList()
{
  
}


/*
 * Adds a puzzle move to the sorted PMMinList according to its f-score (In
 * ascending order).
 * @param pm PuzzleMove to add to the sorted PuzzleMove list
 */
void PMMinList::push(PuzzleMove* pm)
{
  std::list<PuzzleMove*>::iterator it = slist_.begin();
 
  // If the list is empty, simply add the PuzzleMove and return immediately
  if (slist_.size() == 0)
  {
    slist_.push_front(pm);
    return;
  }
  
  // Search for the correct location for the PuzzleMove, insert it, and return immediately
  for (it = slist_.begin(); it != slist_.end(); ++it)
  {
    if (*pm < **it)
    {
      slist_.insert(it, pm);
      return;
    }
  }
  
  // If the PuzzleMove was greater than everything currently in the list, push it to the back
  slist_.push_back(pm);
}


/*
 * Removes the minimum scored (front) puzzle move.
 */
void PMMinList::pop()
{
  slist_.pop_front();
}


/*
 * @return Pointer to the minimum-scored PuzzleMove.
 */
PuzzleMove* PMMinList::top()
{
  return slist_.front();
}

