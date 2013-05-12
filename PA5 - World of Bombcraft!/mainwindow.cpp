#include "mainwindow.h"


/*------------------------------------MAINWINDOW------------------------------------------------*/
MainWindow::MainWindow() : QMainWindow() {
	// Initialize application variables
	playerScore = 0;
	playerName = "";
	gameInProgress = false;
	paused = false;
	
	// Change style of app
	plastique = new QPlastiqueStyle;
	QApplication::setStyle(plastique);
	
	// Right-hand side UI
	rightFrame = new QFrame();
	frameLayout = new QVBoxLayout();
	startBox = new QGroupBox("Game Options");
	startBoxLayout = new QVBoxLayout();
	QLabel* enterName = new QLabel("Enter Your Name:");
	startBoxLayout->addWidget(enterName);
	nameEntry = new QLineEdit();
	nameEntry->setMaxLength(20);
	startBoxLayout->addWidget(nameEntry);
	QLabel* story = new QLabel("You are a lone marine, holding your own as a distraction while the rest of your squad escapes. You must kill as many aliens as possible! Survive for as long as you can, and take a coupleof those darned zerglings out with you. You used all your ammo before your squad escaped, and now all you have left is spider mines and the ocassional missile left on the battlefield. <b>How long can you survive?</b>");
	story->setWordWrap(true);
	startBoxLayout->addWidget(story);
	startButton = new QPushButton("&START!");
	connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
	startBoxLayout->addWidget(startButton);
	QHBoxLayout* scoreDisplay = new QHBoxLayout();
	QLabel* scoreLabel = new QLabel("<b>SCORE:</b>");
	name = new QLabel();
	score = new QLabel();
	connect(nameEntry, SIGNAL(textEdited(const QString &)), name, SLOT(setText(const QString &)));
	scoreDisplay->addWidget(name);
	scoreDisplay->addWidget(score);
	QWidget* scoreDisplayWidget = new QWidget();
	scoreDisplayWidget->setLayout(scoreDisplay);
	restartButton = new QPushButton("&Restart");
	restartButton->setAutoDefault(false);
	connect(restartButton, SIGNAL(clicked()), this, SLOT(restart()));
	highScoresBox = new QGroupBox("Recent Scores");
	highScoresLayout = new QVBoxLayout();
	scoresList = new QListWidget();
	highScoresLayout->addWidget(scoresList);
	highScoresBox->setLayout(highScoresLayout);
	exitButton = new QPushButton("&Exit");
	connect(exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	startBox->setLayout(startBoxLayout);
	frameLayout->addWidget(startBox);
	frameLayout->addWidget(scoreLabel);
	frameLayout->addWidget(scoreDisplayWidget);
	frameLayout->addWidget(restartButton);
	frameLayout->addWidget(highScoresBox);
	frameLayout->addWidget(exitButton);
	rightFrame->setLayout(frameLayout);
	
	// Right Dock
	rightDock = new QDockWidget(tr("World of Bombcraft!"), this);
	rightDock->setAllowedAreas(Qt::RightDockWidgetArea);
	rightDock->setWidget(rightFrame);
	rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	addDockWidget(Qt::RightDockWidgetArea, rightDock);
	
	// Menu Bar
	menu = menuBar();
	fileMenu = new QMenu("File", menu);
	startAction = new QAction("Start Game", fileMenu);
	restartAction = new QAction("Restart Game", fileMenu);
	quitAction = new QAction("Quit", fileMenu);
	connect(quitAction, SIGNAL(triggered()), this, SLOT(quitGame()));
	connect(startAction, SIGNAL(triggered()), this, SLOT(start()));
	connect(restartAction, SIGNAL(triggered()), this, SLOT(restart()));
	fileMenu->addAction(startAction);
	fileMenu->addAction(restartAction);
	fileMenu->addAction(quitAction);
	menu->addMenu(fileMenu);
	setMenuBar(menu);
	
	// GameWindow (essentially a QGraphicsView)
	gameWindow = new GameWindow(576, 576, this);
	connect(gameWindow, SIGNAL(incrementScore(int)), this, SLOT(updateScore(int)));
	connect(gameWindow, SIGNAL(gameOver()), this, SLOT(restart()));
	setCentralWidget(gameWindow);
	
	// App usability changes
	setWindowTitle("World of Bombcraft!");
	QMainWindow::setFixedSize(900, 675);
	setFocus();
}


/*------------------------------------~MAINWINDOW------------------------------------------------*/
MainWindow::~MainWindow() {
	
}


/*------------------------------------START------------------------------------------------*/
void MainWindow::start() {
	// If a game is already running, this function handles Pause states
	if (gameInProgress) {
		if (paused) {
			gameWindow->startTimer();
			setFocus();
			startButton->setText("Pause");
			startAction->setText("Pause Game");
			paused = false;
		} else {
			gameWindow->stopTimer();
			startButton->setText("Resume");
			startAction->setText("Resume Game");
			paused = true;
		}
		return;
	}
	
	// Prompt user to enter a name if they click the start button without entering a name
	if (nameEntry->text().trimmed() == "") {
		QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("World of Bombcraft!"), tr("Please enter your name."), QMessageBox::Ok);
		warning->exec();
		return;
	}
	
	// Initialize gameplay
	gameInProgress = true;
	paused = false;
	startButton->setText("Pause");
	startAction->setText("Pause Game");
	disconnect(nameEntry, SIGNAL(textEdited(const QString &)), name, SLOT(setText(const QString &)));
	updateScore(0);
	playerName = nameEntry->text().trimmed();
	
	// Show instructions popup
	QMessageBox* startMessage = new QMessageBox();
	startMessage->setWindowTitle("World of Bombcraft!");
	startMessage->setTextFormat(Qt::RichText);
	startMessage->setText("Gameplay Controls: <ul><li>WASD Controls to move your Marine</li><li>Space Bar to drop a Mine</li><li>Shift to fire a Missile</li></ul>");
	startMessage->exec();
	
	gameWindow->setFocus();
	gameWindow->start();
}


/*------------------------------------RESTART------------------------------------------------*/
void MainWindow::restart() {
	// Reset start button from its Pause/Resume role to being a Start button again
	startButton->setText("START!");
	startAction->setText("Start Game");
	
	// Reset gameplay variables
	gameInProgress = false;
	paused = false;
	nameEntry->clear();
	connect(nameEntry, SIGNAL(textEdited(const QString &)), name, SLOT(setText(const QString &)));
	gameWindow->reset();
	
	// Save current player's score if there is a current player
	if (name->text() != "") {
		scoresList->addItem(QString(name->text() + ":  " + score->text()));
	}
	score->setText("");
	name->setText("");
	playerScore = 0;
	playerName = "";
	setFocus();
}


/*------------------------------------QUITGAME------------------------------------------------*/
void MainWindow::quitGame() {
	restart();
	qApp->quit();
}


/*------------------------------------UPDATESCORE------------------------------------------------*/
void MainWindow::updateScore(int s) {
	// Change score by s
	playerScore += s;
	score->setText(QString::number(playerScore));
}


/*------------------------------------KEYPRESSEVENT------------------------------------------------*/
void MainWindow::keyPressEvent(QKeyEvent* e) {
	if (e->key() == Qt::Key_Space) {
		gameWindow->spawnExplosive("mine");
	} else if (e->key() == Qt::Key_Shift) {
		gameWindow->spawnExplosive("missile");
	} else if (e->key() == Qt::Key_W) {
		gameWindow->movePlayer(0, -32);
	} else if (e->key() == Qt::Key_A) {
		gameWindow->movePlayer(-32, 0);
	} else if (e->key() == Qt::Key_S) {
		gameWindow->movePlayer(0, 32);
	} else if (e->key() == Qt::Key_D) {
		gameWindow->movePlayer(32, 0);
	}
}





