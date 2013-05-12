#include "mainwindow.h"

// ----------------------- MAINWINDOW() -----------------------
MainWindow::MainWindow() {
	// Set initial gameplay states
	shouldDelete = false;
	heuristic = NONE;
	tileMoving = false;
	
	// Change app style
	defaultStyle = new QPlastiqueStyle;
	QApplication::setStyle(defaultStyle);
	
	// Create Main Layout
	mainLayout = new QGridLayout();
	
	// Board Visualization
	puzzleScene = new QGraphicsScene(-WINDOW_MAX_X/2, -WINDOW_MAX_X/2, WINDOW_MAX_X, WINDOW_MAX_Y);
	puzzleScene->setBackgroundBrush(Qt::white);
	viewStyle = new QProxyStyle;
	puzzleView = new QGraphicsView(puzzleScene);
	puzzleView->setStyle(viewStyle);
	puzzleView->setFixedSize(WINDOW_MAX_X + 20, WINDOW_MAX_Y + 20);
	mainLayout->addWidget(puzzleView, 2, 1, 4, 1);
	
	// Error Box
	errorText = new QTextEdit();
	errorText->setReadOnly(true);
	errorBox = new QGroupBox("Console");
	errorBoxLayout = new QVBoxLayout;
	errorBoxLayout->addWidget(errorText);
	errorBox->setLayout(errorBoxLayout);
	mainLayout->addWidget(errorBox, 6, 1);
	
	// Title Label
	titleLabel = new QLabel();
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setTextFormat(Qt::RichText);
	titleLabel->setText("<b>Game Time!</font></b>");
	mainLayout->addWidget(titleLabel, 1, 0);
	
	// Exit Button
	exitButton = new QPushButton("&Quit");
	connect(exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	mainLayout->addWidget(exitButton, 6, 0);
	
	// A* Button
	cheatButton = new QPushButton("&Cheat");
	connect(cheatButton, SIGNAL(clicked()), this, SLOT(cheat()));
	
	// A* Results
	cheatResults = new QListWidget();
	
	// Radio Button Label
	heuristicLabel = new QLabel("Choose a Heuristic:");
	
	// Radio Buttons
	outOfPlaceRadio = new QRadioButton("&Out of Place");
	connect(outOfPlaceRadio, SIGNAL(clicked()), this, SLOT(handleRadios()));
	manhattanRadio = new QRadioButton("&Manhattan");
	connect(manhattanRadio, SIGNAL(clicked()), this, SLOT(handleRadios()));
	
	// Cheaters GroupBox
	cheatersBox = new QGroupBox("For Cheaters");
	cheatersBoxLayout = new QVBoxLayout;
	cheatersBoxLayout->addWidget(heuristicLabel);
	cheatersBoxLayout->addWidget(manhattanRadio);
	cheatersBoxLayout->addWidget(outOfPlaceRadio);
	cheatersBoxLayout->addWidget(cheatButton);
	cheatersBoxLayout->addWidget(cheatResults);
	cheatersBox->setLayout(cheatersBoxLayout);
	mainLayout->addWidget(cheatersBox, 5, 0);
	
	// Start Game Button
	startButton = new QPushButton("&Start Game");
	connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
	
	// Input Labels
	sizeLabel = new QLabel("Board Size:");
	sizeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	movesLabel = new QLabel("Initial Moves:");
	movesLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	seedLabel = new QLabel("Seed:");
	seedLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	
	// Input Text Boxes
	sizeText = new QLineEdit();
	movesText = new QLineEdit();
	seedText = new QLineEdit();
	
	// Input GroupBox
	initialStuffBox = new QGroupBox("Initial Values");
	formLayout = new QFormLayout;
	formLayout->setLabelAlignment(Qt::AlignRight);
	formLayout->addRow(sizeLabel, sizeText);
	formLayout->addRow(movesLabel, movesText);
	formLayout->addRow(seedLabel, seedText);
	formLayout->addRow(startButton);
	initialStuffBox->setLayout(formLayout);
	mainLayout->addWidget(initialStuffBox, 2, 0);
	
	// Set Layout Settings
	setWindowTitle("Game Time!");
	setLayout(mainLayout);
}


// ----------------------- ~MAINWINDOW() -----------------------
MainWindow::~MainWindow() {	
	/* Most of the following are commented out because attempting to delete them
	 * causes a seg fault upon quitting the program. */
	
	// If memory needs to be free'd, delete the previous GUITiles and Board
	if (shouldDelete) {
		for (int i = 0; i < size; i++) {	
			puzzleScene->removeItem(tiles_[i]);
			delete tiles_[i];
		}
		delete board_;
		delete background;
	}
	
	//delete titleLabel;
	//delete heuristicLabel;
	//delete sizeLabel;
	//delete movesLabel;
	//delete seedLabel;
	
	//delete startButton;
	//delete exitButton;
	//delete cheatButton;
	
	//delete manhattanRadio;
	//delete outOfPlaceRadio;
	
	//delete sizeText;
	//delete movesText;
	//delete seedText;
	//delete errorText;
	
	//delete cheatResults;
	
	//delete formLayout;
	//delete cheatersBoxLayout;
	//delete errorBoxLayout;
	
	//delete initialStuffBox;
	//delete cheatersBox;
	//delete errorBox;

	delete puzzleScene;
	delete puzzleView;
	
	delete mainLayout;
	
	//delete defaultStyle;
	//delete viewStyle;
}


// ----------------------- CHECKIFVALIDINT() -----------------------
bool MainWindow::checkIfValidInt(QString input) {
	// Check if first character is a negative sign (-) or a valid integer (0-9)
	if (input[0] != '-') {
		if (input[0] < '0' || input[0] > '9') {
			return false;
		}
	}
	
	// Check if the rest of the string is a valid integer (0-9)
	for (int i = 1; i < input.size(); i++) {
		if (input[i] < '0' || input[i] > '9') {
			return false;
		}
	}
	
	return true;
}


// ----------------------- START() -----------------------
void MainWindow::start() {
	canMoveTiles = true;
	
	// If memory needs to be free'd, delete the previous GUITiles and Board
	if (shouldDelete) {
		for (int i = 0; i < size; i++) {	
			puzzleScene->removeItem(tiles_[i]);
			delete tiles_[i];
		}
		delete board_;
		delete background;
	}
	
	// Clear all forms
	errorText->clear();
	cheatResults->clear();
	
	// Store the values of size, initMoves, and seed
	size = sizeText->text().toInt();
	initMoves = movesText->text().toInt();
	seed = seedText->text().toInt();
	
	/* Check whether or not the values of size, initMoves, and seed are acceptable
	 * If unacceptable, print the correct error/warning and return immediately */
	bool error = false;
	if (sizeText->text().toStdString() == "") {
		errorText->append("- Warning: Please enter the Size of the Board");
		error = true;
	} else if (size != 9 && size != 16) {
		errorText->append("- Invalid Board Size: Please enter either 9 or 16");
		error = true;
	}
	
	if (movesText->text().toStdString() == "") {
		errorText->append("- Warning: Please enter the number of Initial Moves");
		error = true;
	} else if (!checkIfValidInt(movesText->text())) {
		errorText->append("- Invalid Number of Initial Moves: Please enter a positive integer");
		error = true;
	} else if (initMoves < 0) {
		errorText->append("- Invalid Number of Initial Moves: Please enter a positive number");
		error = true;
	}
	
	if (seedText->text().toStdString() == "") {
		errorText->append("- Warning: Please enter a number for Seed");
		error = true;
	} else if (!checkIfValidInt(seedText->text())) {
		errorText->append("- Invalid entry for Seed: Please enter an integer");
		error = true;
	}
	
	if (error) {
		shouldDelete = false;
		return;
	}
	
	
	// Initialize a new Board with User values
	board_ = new Board(size, initMoves, seed);
	
	/* Initialize a new tiles_ array and set the shouldDelete flag to true so that
	 * upon the next game, memory is free'd appropriately */
	tiles_ = new GUITile*[size];
	shouldDelete = true;
	
	// Create and add a background dependent on the size of the board to the scene
	background = new QGraphicsRectItem(-sqrt(size)*TILE_SIZE/2 - 20, -sqrt(size)*TILE_SIZE/2 - 20, TILE_SIZE*sqrt(size) + 40, TILE_SIZE*sqrt(size) + 40);
	background->setBrush(QBrush(Qt::lightGray));
	QPen outline(Qt::SolidLine);
	outline.setJoinStyle(Qt::RoundJoin);
	outline.setWidth(3);
	background->setPen(outline);
	puzzleScene->addItem(background);
	
	/* Create the GUITiles based upon the Board's scrambled state and place them
	 * in the scene appropriately */
	for (int i = 0; i < size; i++) {
		tiles_[i] = new GUITile(board_->getTiles()[i], -sqrt(size)*TILE_SIZE/2 + (i%(int)sqrt(size))*TILE_SIZE, -sqrt(size)*TILE_SIZE/2 + (int)(i/sqrt(size))*TILE_SIZE, TILE_SIZE, TILE_SIZE);
		puzzleScene->addItem(tiles_[i]);
		connect(tiles_[i], SIGNAL(tilePressed(int)), this, SLOT(MainWindowMoveTile(int)));
	}
	
	/* If the Board is already solved, display the Win State and prevent the
	 * user from moving tiles */
	if (board_->solved()) {
		canMoveTiles = false;
		displayWinState();
	}
}


// ----------------------- HANDLERADIOS() -----------------------
void MainWindow::handleRadios() {
	if (manhattanRadio->isChecked()) {
		heuristic = MANHATTAN;
	} else heuristic = OUTOFPLACE;
	errorText->clear();
}


// ----------------------- CHEAT() -----------------------
void MainWindow::cheat() {
	cheatResults->clear();
	
	// If the current game has already been won, inform the user
	if (!canMoveTiles) {
		cheatResults->addItem("You've already won!");
		cheatResults->addItem("Try starting a new game.");
		return;
	}
	
	//  If no heuristic is selected or a game has not yet been started, print an error for the user
	bool error = false;
	if (heuristic == NONE) {
		errorText->append("- Invalid Heuristic Selection: Please select a Heuristic");
		error = true;
	}
	if (!shouldDelete) {
		errorText->append("- Invalid Operation: Please start a game before cheating");
		error = true;
	}
	if (error) return;
	
	// Create a puzzle heuristic object based on which heuristic the user has selected, and run A*
	PuzzleHeuristic* puzzleHeur;
	if (heuristic == MANHATTAN) {
		puzzleHeur = new ManhattanHeuristic;
	} else {
		puzzleHeur = new OutOfPlaceHeuristic;
	}
	PuzzleSolver solver(*board_);
	
	solver.run(puzzleHeur);
	
	// Print the results of A* to the cheat results box
	cheatResults->addItem("Try this sequence:");
	for (int i = (solver.getSolution()).size() - 1; i >= 0; i--) {
		cheatResults->addItem(QString::number((solver.getSolution())[i]));
	}
	
	delete puzzleHeur;
}


// ----------------------- TOGGLETILEMOVING() -----------------------
void MainWindow::toggleTileMoving() {
	tileMoving = false;
}


// ----------------------- MAINWINDOWMOVETILE() -----------------------
void MainWindow::MainWindowMoveTile(int val) {
	if (!canMoveTiles) return;
	if (tileMoving) return;
	
	int tileIndex = -1;
	int blankTileIndex = -1;
	
	// Find the index of the tile to move and the blank tile in the GUITile array
	for (int i = 0; i < size; i++) {
		if (tiles_[i]->getVal() == val) {
			tileIndex = i;
		}
		if (tiles_[i]->getVal() == 0) {
			blankTileIndex = i;
		}
	}
	
	// If the tile can be moved, move the correct tile to its new position, and swap the GUITiles in the GUITile array 
	if (board_->move(val)) {
		// Find the x,y coordinates of the current locations of the tiles to swap
		qreal tileX = tiles_[tileIndex]->getX();
		qreal tileY = tiles_[tileIndex]->getY();
		qreal blankX = tiles_[blankTileIndex]->getX();
		qreal blankY = tiles_[blankTileIndex]->getY();
		
		// Move the tiles graphically
		tileMoving = true;
		connect(tiles_[tileIndex], SIGNAL(doneMoving()), this, SLOT(toggleTileMoving()));
		tiles_[tileIndex]->setTargetAndMove(blankX, blankY);
		tiles_[blankTileIndex]->moveTile(tileX, tileY);
		
		// Swap GUITiles in the tiles_ array
		GUITile* temp = tiles_[tileIndex];
		tiles_[tileIndex] = tiles_[blankTileIndex];
		tiles_[blankTileIndex] = temp;
	} else return;
	
	// If this move is the winning move, display Win state
	if (board_->solved()) {
		canMoveTiles = false;
		displayWinState();
	} 
}


// ----------------------- DISPLAYWINSTATE() -----------------------
void MainWindow::displayWinState() {
	errorText->clear();
	for (int i = 0; i < 5; i++) errorText->append("YOU WIN!  YOU WIN!  YOU WIN!  YOU WIN!  YOU WIN!  YOU WIN!");
	cheatResults->clear();
	for (int i = 0; i < 9; i++) cheatResults->addItem("YOU WIN!  YOU WIN!  YOU WIN!");
}

