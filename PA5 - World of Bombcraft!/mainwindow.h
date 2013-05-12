#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "gamewindow.h"

/** The main GUI of the application containing all user interface and the GameWindow. */

class MainWindow : public QMainWindow {
	Q_OBJECT
	
public:
	/** Default constructor. Constructs the entire visible window of the application and waits
	 * for user input. */
	explicit MainWindow();
	
	/** Default destructor. Does nothing, as Qt handles its own memory deallocation. */
	~MainWindow();
	
	
public slots:
	/** Slot connected to the Start button that starts the game if no game is currently in progress,
	 * and sets initial gameplay values. Calls GameWindow's GameWindow::start() slot. After starting
	 * the game, determines whether or not the Start button should be changed to a Pause or Resume
	  * button. */
	void start();
	
	/** Slot connected to the Restart button that resets gameplay values, changes the Pause button's
	 * function back to Start!, and saves the current player's score. */
	void restart();
	
	/** Slot connected to the Quit button that calls MainWindow::restart() and exits the application. */
	void quitGame();
	
	/** Slot that changes the player's score by a given amount.
	 * @param s The amount to change the score by (can be positive or negative) */
	void updateScore(int s);
	
	
protected:
	/** Handles keyboard input from the user. */
	void keyPressEvent(QKeyEvent* e);
	
	
private:
	// Game state variables
	bool gameInProgress;	/**< Whether or not a game is currently being played */
	bool paused;			/**< Whether or not the current game is paused */
	QString playerName;		/**< The current player's name */
	int playerScore;		/**< The current player's score */
	
	// UI objects pertaining to right-hand side UI elements
	QDockWidget* rightDock;			/**< The QDockWidget holding all UI elements placed on the right side of the QMainWindow */
	QFrame* rightFrame;				/**< The QFrame that holds all UI elements external to the game itself */
	QVBoxLayout* frameLayout;		/**< The layout used to organized the right-hand side UI */
	QGroupBox* startBox;			/**< The QGroupBox that holds things related to starting the game (i.e. Start button) */
	QVBoxLayout* startBoxLayout;	/**< The layout for the startBox */
	QLineEdit* nameEntry;			/**< The QLineEdit players use to enter their name to save recent scores */
	QPushButton* startButton;		/**< The Start button used to start the game. Also performs the role of Pause and Resume after a game has started */
	QLabel* name;					/**< Displays the current user's name when entered in the nameEntry box */
	QLabel* score;					/**< Displays the score of the current game */
	QPushButton* restartButton;		/**< The button used to restart the game */
	QGroupBox* highScoresBox;		/**< The QGroupBox used for displaying recent scores */
	QVBoxLayout* highScoresLayout;	/**< The layout used to organize the highScoresBox */
	QListWidget* scoresList;		/**< The QListWidget that actually displays recent scores */
	QPushButton* exitButton;		/**< The button used to exit the game */
	
	// The GameWindow
	GameWindow* gameWindow;	/**< The GameWindow in which all gameplay is done */
	
	// Menu items
	QMenuBar* menu;			/**< The application's menu bar */
	QMenu* fileMenu;		/**< The file menu in the menu bar that holds the options Start, Restart, and Quit */
	QAction* quitAction;	/**< Performs the same role as exitButton */
	QAction* restartAction;	/**< Performs the same role as restartButton */
	QAction* startAction;	/**< Performs the same role as startButton */
	
	// Qt Styles
	QStyle* plastique;	/**< The QStyle of the application */
};

#endif
