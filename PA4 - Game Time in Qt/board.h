#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <functional>


/** An object that stores a possible game Board for an "8"-puzzle.
 * Holds an integer array representing the current locations of all
 * tiles and a size that is a perfect square. */


class Board
{
 public:
  /** Default constructor. Creates a 2x2 Board that is
   * already solved. */
  Board(); 

  /** Inititialize a board of given size and scramble it with numInitMoves 
   * by moving the space tile with a randomly chosen direction N, W, S, E
   * some of which may be invalid, in which case we skip that move.
   * 
   *  @param size Number of tiles for the game.
   *      Should be a perfect square (4, 16, 25)
   *  @param numInitMoves Number of tile moves to attempt to scramble the board
   *  @param seed Use to seed the random number generator (srand) 
   */
  Board(int size, int numInitMoves, int seed);

  /** Copy constructor that accepts a Board object and performs
   * a deep copy.
   * @param b The board to be copied */
  Board(const Board &b);

  /** Another kind of copy constructor that performs
   * a deep copy.
   * @param tiles The tiles array of the board to be copied
   * @param size The size of the board to be copied */
  Board(int *tiles, int size); 

  /** Default destructor. Deletes the tile array. */
  ~Board();

  /** Swaps the blank tile with the specified tile.
   * @param tile The tile to be swapped with the blank (not the index) */
  bool move(int tile);

  /** Generate potential moves and return new Boards in a map where 
   * Key=tile, Value=pointer to corresponding Board.
   * @return A map containing the corresponding Board for each potential move */
  std::map<int, Board*> potentialMoves(); 

  /** Returns whether or not the Board is solved.
   * @return True if the Board is solved, false otherwise */
  bool solved();


  // Operators
  /** Operator << overload to print a formated Board object.
   * @param os The output stream to be formated with the Board object information
   * @param b The Board to be printed
   * @return A reference to an ostream object containing the printed Board */
  friend std::ostream& operator<<(std::ostream &os, const Board &b);
  
  /** Operator == overload.
   * @return True if the size and tile locations of the Board on the left are
   * equal to the Board on the right */
  bool operator==(const Board& rhs) const;
  
  /** Operator < overload.
   * @return True if the size or tiles fo the Board on the left are less than
   * the Board on the right */
  bool operator<(const Board& rhs) const;
  
  /** Operator != overload.
   * @return True if the size or tile locations of the Board on the left are not
   * equal to the Board on the right */
  bool operator!=(const Board& rhs) const;
  
  
  // Accessors
  /** Gets a pointer to the Board's current tile layout. 
   * @return An int* to the Board's tiles array */
  int* getTiles();
  
  /** Gets the size of the Board object.
   * @return A perfect square int corresponding to the Board's size */
  int getSize();
  
  
 private:
  int *tiles_;	///< The array of tiles holding the current state of the Board
  int size_;	///< The size of the Board (Should always be a perfect square)
};

// Leave this alone and don't touch it!
struct BoardLessThan : 
  public std::binary_function<const Board*, const Board*,bool>
{
  bool operator()(const Board *b1, const Board *b2) const
  {
    return *b1 < *b2;
  }
};


#endif
