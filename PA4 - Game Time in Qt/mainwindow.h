#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListWidget>
#include <QRadioButton>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QStyle>
#include <QPlastiqueStyle>
#include <QProxyStyle>
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QMessageBox>
#include <QBrush>
#include <QGraphicsRectItem>

#include <cmath>
#include <iostream>

#include "guitile.h"
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

#define WINDOW_MAX_X 480
#define WINDOW_MAX_Y 480
#define TILE_SIZE 80

/** The main application window containing all gameplay elements. */

class MainWindow : public QWidget {
	Q_OBJECT
	
public:
	/** Default constructor. Constructs the entire visible window for the
	 * game and sets initial gameplay states. */
	explicit MainWindow();
	
	/** Default destructor. Free's some memory that is dynamically allocated,
	 * however many of the delete's cause seg faults and are commented out. */
	~MainWindow();
	
	/** Clears the error and cheat results boxes, and writes a 'You Win!' message
	 * inside each of them.
	 * @pre Board::solved() must return true, indicating that the game has been won  */
	void displayWinState();
	
	/**  An enum type defining different heuristic options */
	enum HEURISTIC{
		NONE,		/**< Indicates no Heuristic is selected (value 0) */
		MANHATTAN,	/**< Indicates Manhattan Heuristic is selected (value 1) */
		OUTOFPLACE	/**< Indicates OutOfPlace Heuristic is selected (value 2) */
	};


public slots:
	/** If a tile is not currently moving, and the clicked tile can be moved,
	 * swaps the blank GUITile and selected GUITile .
	 * @param val The integer value on the face of the GUITile that the user clicked on */
	void MainWindowMoveTile(int val);
	
	/** Reads in the values the user has given for Board Size, Initial Moves, and Seed,
	 * creates a Board with these values, and creates a visual representation of that Board
	 * on screen. */
	void start();
	
	/** Determines which QRadioButton has been selected (either the Manhattan Heuristic or
	 * OutOfPlace Heuristc) and sets the program's current HEURISTIC enum appropriately. */
	void handleRadios();
	
	/** Called when the Cheat QPushButton is clicked. Uses the current HEURISTIC enum to determine
	 * what heuristic to use to solve the current Board, then prints the solution to the QListWidget
	 * cheatBox.
	 * @pre A heuristic must be selected, or this function will print an error to the errorBox */
	void cheat();
	
	/** Called when the current moving GUITile has reached its position. Allows further tiles to be
	 * moved (since only one GUITile can be moving at one time).
	 * @post tileMoving is set to FALSE */
	void toggleTileMoving();


private:
	/** Checks if the given string is a valid entry for the user-entered Seed or Initial Moves
	 * (i.e. is a valid integer, not actually a string).
	 * @param input The QString to check for validity
	 * @return True if the QString is actually a valid integer, False otherwise */
	bool checkIfValidInt(QString input);
	
	GUITile** tiles_;	/**< GUITile array */
	
	// Current Board variables
	Board* board_;		/**< The current iteration of the Board */
	int size;			/**< The size of the Board (width * height). Must be either 9 or 16 */
	int initMoves;		/**< The number of intitial moves used when initializing the Board */
	int seed;			/**< The seed used to scramble the Board when initializing it */
	bool canMoveTiles;	/**< Whether or not the player is currently allowed to move tiles */
	
	// Misc. variables
	bool shouldDelete;	/**< Whether or not memory should be free'd when starting a new game */
	int heuristic;		/**< The currently selected heuristic (see enum HEURISTIC) */
	bool tileMoving;	/**< Whether or not a GUITile is currently moving */
	
	// Styles
	QStyle* defaultStyle;	/**< The visual style most of the GUI uses (excluding the QGraphicsVew) */
	QStyle* viewStyle;		/**< The visual style the QGraphicsVew uses */
	
	// Layouts
	QGridLayout* mainLayout;		/**< The main layout that holds everything in the application */
	QFormLayout* formLayout;		/**< The form layout that holds the initial Board widgets */
	QVBoxLayout* cheatersBoxLayout;	/**< The box layout that holds cheat-related widgets */
	QVBoxLayout* errorBoxLayout;	/**< The box layout that holds the error text box widget */
	
	// Labels
	QLabel* titleLabel;		/**< Displays the game title, Game Time! */
	QLabel* heuristicLabel;	/**< Displays the heuristic query, Choose a Heuristic */
	QLabel* sizeLabel;		/**< Displays the board size query, Board Size: */
	QLabel* movesLabel;		/**< Displays the initial moves query, Initial Moves: */
	QLabel* seedLabel;		/**< Displays the seed query, Seed: */
	
	// Scene and view for Board
	QGraphicsScene* puzzleScene;	/**< The scene used to display GUITiles during gameplay */
	QGraphicsView* puzzleView;		/**< The view holding the gameplay scene */
	QGraphicsRectItem* background;	/**< The background underlying the visualized Board during gameplay */
	
	// Push Buttons
	QPushButton* startButton;	/**< Button that starts a game */
	QPushButton* exitButton;	/**< Button that exits the application */
	QPushButton* cheatButton;	/**< Button that uses a heuristic to display the cheat (moves to win the game) */
	
	// Radio Buttons
	QRadioButton* manhattanRadio;	/**< Radio button for selecting the Manhattan Heuristic */
	QRadioButton* outOfPlaceRadio;	/**< Radio button for selecting the OutOfPlace Heuristic */
	
	// Text Boxes
	QLineEdit* sizeText;	/**< Text box for accepting the initial Board size from the user */
	QLineEdit* movesText;	/**< Text box for accepting the initial moves used to scramble the Board from the user */
	QLineEdit* seedText;	/**< Text box for accepting the seed used to scramble the Board from the user */
	QTextEdit* errorText;	/**< Read-only text box for displaying errors to the user */
	
	// List Box for A* Search Results
	QListWidget* cheatResults;	/**< List text box for displaying cheat results (moves to make to win) */
	
	// Group Boxes
	QGroupBox* initialStuffBox;	/**< Group Box that holds all initial Board value input and the Start button */
	QGroupBox* cheatersBox;		/**< Group Box that holds all cheat-related widgets */
	QGroupBox* errorBox;		/**< Group Box that holds the error text box */
};

#endif
