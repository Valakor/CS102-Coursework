#ifndef PMMINLIST_H
#define PMMINLIST_H
#include <list>

/**
 * PMMinList implements a sorted list of PuzzleMoves
 * based on their f-score (from smallest to largest).
 */
 
class PMMinList 
{
 public:
  /** Default Constructor. Instantiates a list of PuzzleMove*. */
  PMMinList();
  
  /** Destructor. Empty. */
  ~PMMinList();
  
  /** Returns the number of items in the list
   * @return The size of the list */
  int size() const { return slist_.size(); }
  
  /** Returns whether or not the list is empty
   * @return True if the list is empty, false otherwise */
  bool empty() const { return slist_.empty(); }
  
  /** Adds a puzzle move to the sorted PMMinList according to its f-score (In
   * ascending order).
   * @param pm The PuzzleMove to add to the sorted PuzzleMove list */
  void push(PuzzleMove* pm);
  
  /** Removes the minimum scored (front) puzzle move. */
  void pop();
  
  /** Returns the PuzzleMove at the top of the list.
   * @return The PuzzleMove with the lowest score */
  PuzzleMove* top();
  
 private:
  std::list<PuzzleMove*> slist_;	///< The sorted list of PuzzleMove objects
};

#endif
