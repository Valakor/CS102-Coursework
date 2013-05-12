#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include "board.h"


/* Default constructor. Creates a 2x2 board that is
 * already solved. */
Board::Board()
{
  size_ = 4;
  tiles_ = new int[size_];
  for (int i = 0; i < size_; i++)
  	tiles_[i] = i;
}


/* Init a board of given size and scramble it with numInitMoves 
 * by moving the space tile with a randomly chosen direction N, W, S, E
 * some of which may be invalid, in which case we skip that move 
 * 
 *  @param size Number of tiles for the game.  \
 *      Should be a perfect square (4, 16, 25)
 *  @param numInitMoves Number of tile moves to attempt to scramble the board
 *  @param seed Use to seed the random number generator (srand) 
 */
Board::Board(int size, int numInitMoves, int seed )
{
  size_ = size;
  tiles_ = new int[size_];
  int dim = static_cast<int>(sqrt(size_));
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  for(int i=0; i < numInitMoves; i++){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
    }
  }
}


/* Copy constructor that accepts a Board object.*/
Board::Board(const Board &b)
{
  size_ = b.size_;
  tiles_ = new int[b.size_];
  for (int i = 0; i < size_; i++)
  	tiles_[i] = b.tiles_[i];
}


/* Another kind of "copy" constructor */
Board::Board(int *tiles, int size)
{
  size_ = size;
  tiles_ = new int[size];
  for (int i = 0; i < size; i++)
  	tiles_[i] = tiles[i];
}


/* Default destructor. Deletes the tile array. */
Board::~Board()
{
  delete [] tiles_;
}


/* Swaps the blank with the specified tile. */
void Board::move(int tile)
{
  int blankTileIndex = -1, otherTileIndex = -1;
  
  // Find the blank tile index and other tile index
  for (int i = 0; i < size_; i++)
  {
    if (tiles_[i] == 0) blankTileIndex = i;
    if (tiles_[i] == tile) otherTileIndex = i;
  }
  
  // If a tile is not found, return immediately
  if (blankTileIndex == -1 || otherTileIndex == -1) return;
  
  
  if (abs(blankTileIndex - otherTileIndex) == (int)sqrt(size_)) // Check for moves above and below
  {
    tiles_[blankTileIndex] = tiles_[otherTileIndex];
    tiles_[otherTileIndex] = 0;
  } else if (blankTileIndex - 1 == otherTileIndex && blankTileIndex % (int)sqrt(size_) != 0) // Check for move on the left
  {
    tiles_[blankTileIndex] = tiles_[otherTileIndex];
    tiles_[otherTileIndex] = 0;
  } else if (blankTileIndex + 1 == otherTileIndex && blankTileIndex % (int)sqrt(size_) != (int)sqrt(size_) - 1) // Check for move on the right
  {
    tiles_[blankTileIndex] = tiles_[otherTileIndex];
    tiles_[otherTileIndex] = 0;
  }
}


/* Generate potential moves and return new boards in a map.
 * Key=tile, Value=Ptr to corresponding Board. */
std::map<int, Board*> Board::potentialMoves()
{
  int blankTileIndex = 0;
  std::map<int, Board*> boardMap;
  Board* tempBoard;
  
  // Find blank tile
  for (int i = 0; i < size_; i++)
  {
    if (tiles_[i] == 0)
    {
      blankTileIndex = i;
      break;
    }
  }
  
  // Check for possible move above
  int aboveMove = blankTileIndex - (int)sqrt(size_);
  if (aboveMove >= 0) 
  {
    tempBoard = new Board(*this);
    tempBoard->move(tiles_[aboveMove]);
    boardMap[tiles_[aboveMove]] = tempBoard;
  }
  
  // Check for possible move below
  int belowMove = blankTileIndex + (int)sqrt(size_);
  if (belowMove < size_) 
  {
    tempBoard = new Board(*this);
    tempBoard->move(tiles_[belowMove]);
    boardMap[tiles_[belowMove]] = tempBoard;
  }
  
  // Check for possible move left
  int leftMove = blankTileIndex - 1;
  if (blankTileIndex % (int)sqrt(size_) != 0)
  {
    tempBoard = new Board(*this);
    tempBoard->move(tiles_[leftMove]);
    boardMap[tiles_[leftMove]] = tempBoard;
  }
  
  // Check for possible move right
  int rightMove = blankTileIndex + 1;
  if (blankTileIndex % (int)sqrt(size_) != (int)sqrt(size_) - 1)
  {
    tempBoard = new Board(*this);
    tempBoard->move(tiles_[rightMove]);
    boardMap[tiles_[rightMove]] = tempBoard;
  }
  
  return boardMap;
}


/* Returns true if the board is solved, false otherwise. */
bool Board::solved()
{
  for (int i = 0; i < size_; i++)
  	if (tiles_[i] != i) return false;
  	
  return true;
}


/* Operator << overload to print a formated Board object. */
std::ostream& operator<<(std::ostream &os, const Board &b)
{
  int width = (int)(log10(b.size_ - 1) + 2);
  
  for (int i = 0; i < (int)sqrt(b.size_); i++)
  {
    for (int j = 0; j < (int)sqrt(b.size_); j++)
    {
      if (b.tiles_[j + i * (int)sqrt(b.size_)] == 0)
      {
        os << std::setw(width);
        os << " ";
      }
      else
      {
        os << std::setw(width);
        os << b.tiles_[j + i * (int)sqrt(b.size_)];
      }
    }
    os << std::endl;
  }
  
  return os;
}


/* Operator == overload. */
bool Board::operator==(const Board& rhs) const
{
  if (size_ != rhs.size_) return false;
  for (int i = 0; i < size_; i++)
  {
    if (tiles_[i] != rhs.tiles_[i]) return false;
  }
  
  return true;
}


/* Operator < overload. */
bool Board::operator<(const Board& rhs) const
{
  if(size_ < rhs.size_){
    return true;
  }
  bool val = false;
  for(int i=0; i < size_; i++){
    if(tiles_[i] < rhs.tiles_[i]){
       //val = true;
       //break;
       return true;
     }
     else if(tiles_[i] > rhs.tiles_[i]){
       //break;
       return false;
     }
  }
  return val;
}


/* Operator != overload. */
bool Board::operator!=(const Board& rhs) const
{
  if (size_ != rhs.size_) return true;
  for (int i = 0; i < size_; i++)
  {
    if (tiles_[i] != rhs.tiles_[i]) return true;
  }
  
  return false;
}


/* Returns a pointer to the Board's tile array. */
int* Board::getTiles()
{
  return tiles_;
}


/* Returns the size of the Board object. */
int Board::getSize()
{
  return size_;
}

