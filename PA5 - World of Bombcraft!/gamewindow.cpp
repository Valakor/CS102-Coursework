#include "gamewindow.h"


/*------------------------------------GAMEWINDOW------------------------------------------------*/
GameWindow::GameWindow(int nWidth, int nHeight, QWidget* prnt) : QGraphicsView() {
	// Initialize all gameplay values
	height = nHeight;
	width = nWidth;
	parent = prnt;
	gameTimer = 0;
	gameCounter = 0;
	gameSpeed = 1;
	enemyCounter = 0;
	collisionCounter = 0;
	mineCounter = 2250;
	powerupCounter = 0;
	healthCounter = 0;
	powerupSpawnTime = 5000;
	numHealths = 0;
	numPowerups = 0;
	srand(time(NULL));
	marine = NULL;
	gameInProgress = false;
	
	// Set up the view and scene
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene = new QGraphicsScene(0, -16, width, height);
	backgroundPix = new QPixmap("./GamePictures/DirtBackground.png");
	backgroundBrush = new QBrush();
	backgroundBrush->setTexture(*backgroundPix);
	QGraphicsView::setScene(scene);
	scene->setBackgroundBrush(*backgroundBrush);
	QGraphicsView::setFixedSize(width + 20, height + 52);
	
	// Set up Missile display
	missileDisplay = new QGraphicsSimpleTextItem("Missiles: 0");
	missileDisplay->setPos(100, -24);
	scene->addItem(missileDisplay);
	
	// Preload all the game's sprites
	wallSpr = new QPixmap("./GamePictures/wall.png");
	wallBrokenSpr = new QPixmap("./GamePictures/wall_cracked.png");
	
	marineSpr_up = new QPixmap("./GamePictures/marine_up.png");
	marineSpr_down = new QPixmap("./GamePictures/marine_down.png");
	marineSpr_left = new QPixmap("./GamePictures/marine_left.png");
	marineSpr_right = new QPixmap("./GamePictures/marine_right.png");
	marinePackage = new QPixmap*[4];
	marinePackage[UP] = marineSpr_up;
	marinePackage[DOWN] = marineSpr_down;
	marinePackage[LEFT] = marineSpr_left;
	marinePackage[RIGHT] = marineSpr_right;
	
	zerglingSpr_up = new QPixmap("./GamePictures/zergling_up.png");
	zerglingSpr_down = new QPixmap("./GamePictures/zergling_down.png");
	zerglingSpr_left = new QPixmap("./GamePictures/zergling_left.png");
	zerglingSpr_right = new QPixmap("./GamePictures/zergling_right.png");
	zerglingPackage = new QPixmap*[4];
	zerglingPackage[UP] = zerglingSpr_up;
	zerglingPackage[DOWN] = zerglingSpr_down;
	zerglingPackage[LEFT] = zerglingSpr_left;
	zerglingPackage[RIGHT] = zerglingSpr_right;
	
	spiderMineSpr = new QPixmap("./GamePictures/spiderMine.png");
	spiderMine_OffSpr = new QPixmap("./GamePictures/spiderMine_off.png");
	spiderPackage = new QPixmap*[2];
	spiderPackage[0] = spiderMineSpr;
	spiderPackage[1] = spiderMine_OffSpr;
	
	explosionSpr_1 = new QPixmap("./GamePictures/explosion1.png");
	explosionSpr_2 = new QPixmap("./GamePictures/explosion2.png");
	explosionSpr_3 = new QPixmap("./GamePictures/explosion3.png");
	explosionSpr_4 = new QPixmap("./GamePictures/explosion4.png");
	explosionSpr_5 = new QPixmap("./GamePictures/explosion5.png");
	explosionSpr_6 = new QPixmap("./GamePictures/explosion6.png");
	explosionPackage = new QPixmap*[6];
	explosionPackage[0] = explosionSpr_1;
	explosionPackage[1] = explosionSpr_2;
	explosionPackage[2] = explosionSpr_3;
	explosionPackage[3] = explosionSpr_4;
	explosionPackage[4] = explosionSpr_5;
	explosionPackage[5] = explosionSpr_6;
	
	livesPackage = new QPixmap*[3];
	hpSpr_0 = new QPixmap("./GamePictures/healthBar_empty.png");
	hpBar = new QGraphicsPixmapItem(*hpSpr_0);
	hpBar->setZValue(2);
	hpBar->setPos(0, -32);
	scene->addItem(hpBar);
	hpSpr_1 = new QPixmap("./GamePictures/healthBar_1.png");
	hpSpr_2 = new QPixmap("./GamePictures/healthBar_2.png");
	hpSpr_3 = new QPixmap("./GamePictures/healthBar_3.png");
	hpItem = new QGraphicsPixmapItem();
	hpItem->setZValue(1);
	hpItem->setPos(0, -32);
	scene->addItem(hpItem);
	livesPackage[0] = hpSpr_1;
	livesPackage[1] = hpSpr_2;
	livesPackage[2] = hpSpr_3;
	
	missileSpr = new QPixmap("./GamePictures/missile.png");
	
	powerupSpr = new QPixmap("./GamePictures/powerup.png");
	
	healthPickupSpr = new QPixmap("./GamePictures/health.png");
	
	// Initialize the abstract grid to 18x18 (324) and the gameObjects list
	grid = new std::vector<GameObject*>;
	for (int i = 0; i < 324; i++) {
		grid->push_back(NULL);
	}
	gameObjects = new std::list<GameObject*>;
	
	// Initialize the timer
	timer = new QTimer();
	timer->setInterval(1);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
	
	// Create the exterior set of walls that holds all gameplay
	Wall* wall;
	for (int i = 0; i < 18; i++) {
		wall = new Wall(i*32, 0, wallSpr, i, this);
		scene->addItem(wall);
		grid->at(i) = wall;
		gameObjects->push_back(wall);
		wall = new Wall(i*32, height - 32, wallSpr, i+306, this);
		scene->addItem(wall);
		grid->at(i+306) = wall;
		gameObjects->push_back(wall);
	}
	
	for (int i = 1; i < 17; i++) {
		wall = new Wall(0, i*32, wallSpr, i*18, this);
		scene->addItem(wall);
		grid->at(i*18) = wall;
		gameObjects->push_back(wall);
		wall = new Wall(width - 32, i*32, wallSpr, i*18 + 17, this);
		scene->addItem(wall);
		grid->at(i*18+17) = wall;
		gameObjects->push_back(wall);
	}
}


/*------------------------------------~GAMEWINDOW------------------------------------------------*/
GameWindow::~GameWindow() {	
	// Empty the gameObjects list
	for (std::list<GameObject*>::iterator it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		if ((*it) != NULL) {
			scene->removeItem(*it);
			delete *it;
			*it = NULL;
		}
	}
	delete gameObjects;
	delete grid;
}


/*------------------------------------STARTTIMER------------------------------------------------*/
void GameWindow::startTimer() {
	if (!timer->isActive())
		timer->start();
}


/*------------------------------------STOPTIMER------------------------------------------------*/
void GameWindow::stopTimer() {
	if (timer->isActive())
		timer->stop();
}


/*------------------------------------MOVEPLAYER------------------------------------------------*/
void GameWindow::movePlayer(int dx, int dy) {
	if (marine == NULL) {
		return;
	}
	// Move the player's Marine if not currently moving and the direction of movement is valid
	else if (!marine->moving()) {
		if (dx > 0) {
			if (grid->at(marine->getIndex() + 1) == NULL) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() + 1) = marine;
				marine->setIndex(marine->getIndex() + 1);
			} else if (grid->at(marine->getIndex() + 1)->getType() == ALIEN) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() + 1) = marine;
				marine->setIndex(marine->getIndex() + 1);
			} else if (grid->at(marine->getIndex() + 1)->getType() == POWERUP) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() + 1) = marine;
				marine->setIndex(marine->getIndex() + 1);
			} else if (grid->at(marine->getIndex() + 1)->getType() == HEALTH) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() + 1) = marine;
				marine->setIndex(marine->getIndex() + 1);
			} else {
				marine->changeDirection(RIGHT);
			}
		} else if (dx < 0) {
			if (grid->at(marine->getIndex() - 1) == NULL) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() - 1) = marine;
				marine->setIndex(marine->getIndex() - 1);
			} else if (grid->at(marine->getIndex() - 1)->getType() == ALIEN) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() - 1) = marine;
				marine->setIndex(marine->getIndex() - 1);
			} else if (grid->at(marine->getIndex() - 1)->getType() == POWERUP) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() - 1) = marine;
				marine->setIndex(marine->getIndex() - 1);
			} else if (grid->at(marine->getIndex() - 1)->getType() == HEALTH) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() - 1) = marine;
				marine->setIndex(marine->getIndex() - 1);
			} else {
				marine->changeDirection(LEFT);
			}
		} else if (dy > 0) {
			if (grid->at(marine->getIndex() + 18) == NULL) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() + 18) = marine;
				marine->setIndex(marine->getIndex() + 18);
			} else if (grid->at(marine->getIndex() + 18)->getType() == ALIEN) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() + 18) = marine;
				marine->setIndex(marine->getIndex() + 18);
			} else if (grid->at(marine->getIndex() + 18)->getType() == POWERUP) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() + 18) = marine;
				marine->setIndex(marine->getIndex() + 18);
			} else if (grid->at(marine->getIndex() + 18)->getType() == HEALTH) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() + 18) = marine;
				marine->setIndex(marine->getIndex() + 18);
			} else {
				marine->changeDirection(DOWN);
			}
		} else if (dy < 0) {
			if (grid->at(marine->getIndex() - 18) == NULL) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() - 18) = marine;
				marine->setIndex(marine->getIndex() - 18);
			} else if (grid->at(marine->getIndex() - 18)->getType() == ALIEN) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() - 18) = marine;
				marine->setIndex(marine->getIndex() - 18);
			} else if (grid->at(marine->getIndex() - 18)->getType() == POWERUP) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() - 18) = marine;
				marine->setIndex(marine->getIndex() - 18);
			} else if (grid->at(marine->getIndex() - 18)->getType() == HEALTH) {
				marine->move(dx, dy);
				grid->at(marine->getIndex()) = NULL;
				grid->at(marine->getIndex() - 18) = marine;
				marine->setIndex(marine->getIndex() - 18);
			} else {
				marine->changeDirection(UP);
			}
		}
	}
}


/*------------------------------------SPAWNEXPLOSIVE------------------------------------------------*/
void GameWindow::spawnExplosive(QString type) {
	if (marine == NULL) {
		return;
	}
	
	// Spawn an appropriate explosive (Mine or Missile) at the player's Marine location
	if (type == "mine") {
		if (mineCounter > 1500 && !marine->moving()) {
			mineCounter -= 1500;
			Mine* mine = new Mine(marine->x(), marine->y(), spiderPackage, -1, this);
			mine->setZValue(-1);
			connect(timer, SIGNAL(timeout()), mine, SLOT(handleTimer()));
			connect(mine, SIGNAL(destroy(GameObject*)), this, SLOT(destroyObject(GameObject*)));
			connect(mine, SIGNAL(explode(int, int, int)), this, SLOT(createExplosion(int, int, int)));
			scene->addItem(mine);
			gameObjects->push_back(mine);
		}
	} else if (type == "missile") {
		if (marine->getMissiles() > 0 && !marine->moving()) {
			marine->changeMissile(-1);
			Missile* missile = new Missile(marine->x(), marine->y(), marine->getDirection(), missileSpr, -1, this);
			missile->setZValue(1);
			connect(timer, SIGNAL(timeout()), missile, SLOT(handleTimer()));
			connect(missile, SIGNAL(destroy(GameObject*)), this, SLOT(destroyObject(GameObject*)));
			connect(missile, SIGNAL(explode(int, int, int)), this, SLOT(createExplosion(int, int, int)));
			scene->addItem(missile);
			gameObjects->push_back(missile);
			missileDisplay->setText(QString("Missiles: " + QString::number(marine->getMissiles())));
		}
	}
}


/*------------------------------------START------------------------------------------------*/
void GameWindow::start() {
	generateTerrain();
	
	// Assure the player is not hemmed in by walls at the start of the game
	if (grid->at(19) != NULL) {
		destroyObject(grid->at(19));
	}
	if (grid->at(20) != NULL) {
		destroyObject(grid->at(20));
	}
	if (grid->at(37) != NULL) {
		destroyObject(grid->at(37));
	}
	
	// Spawn the player's Marine
	marine = new Marine(32, 32, marinePackage, 19, this, 1);
	marine->setZValue(2);
	connect(timer, SIGNAL(timeout()), marine, SLOT(handleTimer()));
	grid->at(19) = marine;
	gameObjects->push_back(marine);
	scene->addItem(marine);
	
	// Re-intialize gameplay variables
	enemyCounter = 0;
	collisionCounter = 0;
	mineCounter = 2250;
	powerupCounter = 0;
	powerupSpawnTime = 5000;
	healthCounter = 0;
	numPowerups = 0;
	gameCounter = 0;
	gameTimer = 0;
	gameSpeed = 1;
	numHealths = 0;
	srand(time(NULL));
	missileDisplay->setText("Missiles: 1");
	
	// Set the visible lives to 3 of 3
	hpItem->setPixmap(*(livesPackage[2]));
	
	// Begin the game
	gameInProgress = true;
	timer->start();
}


/*------------------------------------RESET------------------------------------------------*/
void GameWindow::reset() {
	// Re-intialize gameplay variables
	timer->stop();
	enemyCounter = 0;
	collisionCounter = 0;
	mineCounter = 2250;
	powerupCounter = 0;
	powerupSpawnTime = 5000;
	gameTimer = 0;
	numPowerups = 0;
	gameSpeed = 1;
	gameCounter = 0;
	healthCounter = 0;
	numHealths = 0;
	srand(time(NULL));
	gameInProgress = false;
	missileDisplay->setText("Missiles: 0");
	
	// Empty everything from the scene and delete it from the gameObjects list
	for (std::list<GameObject*>::iterator it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		if ((*it) != NULL) {
			scene->removeItem(*it);
			delete *it;
			*it = NULL;
		}
	}
	
	// Clear the abstract grid
	for (int i = 0; i < 324; i++) {
		grid->at(i) = NULL;
	}
	
	gameObjects->clear();
	
	// Recreate the boundary walls for gameplay
	Wall* wall;
	for (int i = 0; i < 18; i++) {
		wall = new Wall(i*32, 0, wallSpr, i, this);
		scene->addItem(wall);
		grid->at(i) = wall;
		gameObjects->push_back(wall);
		wall = new Wall(i*32, height - 32, wallSpr, i+306, this);
		scene->addItem(wall);
		grid->at(i+306) = wall;
		gameObjects->push_back(wall);
	}
	
	for (int i = 1; i < 17; i++) {
		wall = new Wall(0, i*32, wallSpr, i*18, this);
		scene->addItem(wall);
		grid->at(i*18) = wall;
		gameObjects->push_back(wall);
		wall = new Wall(width - 32, i*32, wallSpr, i*18 + 17, this);
		scene->addItem(wall);
		grid->at(i*18+17) = wall;
		gameObjects->push_back(wall);
	}
	
	// Set the lives to 0 of 3
	hpItem->setPixmap(NULL);
}


/*------------------------------------HANDLETIMER------------------------------------------------*/
void GameWindow::handleTimer() {
	// If the Marine has 0 lives, remove him from the scene and end the game
	if (marine != NULL) {
		if (marine->getLives() == 0) {
			grid->at(marine->getIndex()) = NULL;
			for (std::list<GameObject*>::iterator it = gameObjects->begin(); it != gameObjects->end(); ++it) {
				if (*it != NULL) {
					if ((*it)->getType() == MARINE) {
						*it = NULL;
						break;
					}
				}
			}
			delete marine;
			marine = NULL;
			gameInProgress = false;
			return;
		}
	}
	
	// Increase gameSpeed over time
	gameCounter++;
	if (gameCounter >= 1000) {
		gameCounter = 0;
		gameTimer++;
		gameSpeed = exp((double)gameTimer/55.0);
		if (gameSpeed >= 10) {
			gameSpeed = 10;
		}
	}
	
	// Spawn enemies at a decreasing interval based on gameSpeed
	enemyCounter++;
	if (enemyCounter >= 4200.0/gameSpeed) {
		enemyCounter = 0;
		if (gameInProgress) {
			spawnThing("Alien");
		}
	}
	
	// Spawn Missile powerups at random, decreasing intervals based on gameSpeed (limited to 3 in the game at a time)
	powerupCounter++;
	if (powerupCounter >= (double)powerupSpawnTime/gameSpeed) {
		powerupSpawnTime = rand() % 5000 + 4001;
		powerupCounter = 0;
		if (gameInProgress && numPowerups < 3) {
			numPowerups++;
			spawnThing("Powerup");
		}
	}
	
	// Spawn Health pickups at decreasing intervals based on gameSpeed (limited to 2 in the game at a time)
	healthCounter++;
	if (healthCounter >= 8000.0/gameSpeed) {
		healthCounter = 0;
		if (gameInProgress && numHealths < 2) {
			numHealths++;
			spawnThing("Health");
		}
	}
	
	// Detect collisions every 0.1 seconds
	collisionCounter++;
	if (collisionCounter >= 100) {
		collisionCounter = 0;
		
		if (marine != NULL) {
			marine->setGameSpeed(gameSpeed);
		}
		
		// Detect all collisions with Explosions
		for (std::list<GameObject*>::iterator it = gameObjects->begin(); it != gameObjects->end(); ++it) {
			if (*it != NULL) {
				if ((*it)->getType() == EXPLOSION) {
					QList<QGraphicsItem*> collisions = scene->collidingItems(*it);
					for (int j = 0; j < collisions.size(); j++) {
						if (*it == collisions[j]) {
							continue;
						}
						if (dynamic_cast<GameObject*>(collisions[j])->getType() == DWALL) {
							destroyObject(dynamic_cast<GameObject*>(collisions[j]));
						} else if (dynamic_cast<GameObject*>(collisions[j])->getType() == POWERUP) {
							destroyObject(dynamic_cast<GameObject*>(collisions[j]));
							numPowerups--;
						} else if (dynamic_cast<GameObject*>(collisions[j])->getType() == HEALTH) {
							destroyObject(dynamic_cast<GameObject*>(collisions[j]));
							numHealths--;
						} else if (dynamic_cast<GameObject*>(collisions[j])->getType() == ALIEN) {
							emit incrementScore(dynamic_cast<Alien*>(collisions[j])->pointValue());
							destroyObject(dynamic_cast<GameObject*>(collisions[j]));
						} else if (dynamic_cast<GameObject*>(collisions[j])->getType() == MARINE) {
							if (!dynamic_cast<Explosion*>(*it)->hasHit()) {
								dynamic_cast<Explosion*>(*it)->hit();
								if (marine->removeLife()) {
									if (marine->getLives() > 0) {
										hpItem->setPixmap(*(livesPackage[marine->getLives() - 1]));
									} else {
										hpItem->setPixmap(NULL);
									}
								}
							}
						}
					}
				}
			}
		}
		
		// Detect all collisions with the Marine
		if (marine != NULL) {
			QList<QGraphicsItem*> collisions = scene->collidingItems(marine);
			for (int j = 0; j < collisions.size(); j++) {
				if (marine == collisions[j]) {
					continue;
				}
				if (dynamic_cast<GameObject*>(collisions[j])->getType() == ALIEN) {
					if (marine->removeLife()) {
						if (marine->getLives() > 0) {
							hpItem->setPixmap(*(livesPackage[marine->getLives() - 1]));
						} else {
							hpItem->setPixmap(NULL);
						}
						destroyObject(dynamic_cast<GameObject*>(collisions[j]));
						break;
					}
				} else if (dynamic_cast<GameObject*>(collisions[j])->getType() == POWERUP) {
						numPowerups--;
						marine->changeMissile(1);
						missileDisplay->setText(QString("Missiles: " + QString::number(marine->getMissiles())));
						destroyObject(dynamic_cast<GameObject*>(collisions[j]));
						break;
				} else if (dynamic_cast<GameObject*>(collisions[j])->getType() == HEALTH) {
						numHealths--;
						if (marine->addLife()) {
							hpItem->setPixmap(*(livesPackage[marine->getLives() - 1]));
						}
						destroyObject(dynamic_cast<GameObject*>(collisions[j]));
						break;
				}
			}
		}
	}
	
	if (mineCounter < 4500) {
		mineCounter++;
	}
}


/*------------------------------------DESTROYOBJECT------------------------------------------------*/
void GameWindow::destroyObject(GameObject* g) {
	scene->removeItem(g);
	
	for (std::list<GameObject*>::iterator it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		if (*it == g) {
			if (*it != NULL) {
				if ((*it)->getIndex() >= 0 && (*it)->getIndex() < 324) {
					grid->at((*it)->getIndex()) = NULL;
				}
				delete *it;
				*it = NULL;
			}
			gameObjects->erase(it);
			break;
		}
	}
}


/*------------------------------------CREATEEXPLOSION------------------------------------------------*/
void GameWindow::createExplosion(int x, int y, int dist) {
	Explosion* explosion;
	int index = x/32 + y/32*18;
	int explosionDistance = dist;

	if (index < 324 || index >= 0) {
		explosion = new Explosion(x, y, explosionPackage, -1, this);
		explosion->setZValue(1);
		connect(timer, SIGNAL(timeout()), explosion, SLOT(handleTimer()));
		connect(explosion, SIGNAL(destroy(GameObject*)), this, SLOT(destroyObject(GameObject*)));
		gameObjects->push_back(explosion);
		scene->addItem(explosion);
	}
	
	for (int i = 1; i <= explosionDistance; i++) {
		if (index + i >= 324 || index + i < 0) {
			break;
		}
		if (grid->at(index + i) != NULL) {
			if (grid->at(index + i)->getType() == IWALL) {
				break;
			}
		}
		explosion = new Explosion(x + i*32, y, explosionPackage, -1, this);
		explosion->setZValue(1);
		connect(timer, SIGNAL(timeout()), explosion, SLOT(handleTimer()));
		connect(explosion, SIGNAL(destroy(GameObject*)), this, SLOT(destroyObject(GameObject*)));
		gameObjects->push_back(explosion);
		scene->addItem(explosion);
		if (grid->at(index + i) != NULL) {
			if (grid->at(index + i)->getType() == DWALL) {
				explosionDistance--;
			}
		}
	}
	
	explosionDistance = dist;
	for (int i = -1; i >= -explosionDistance; i--) {
		if (index + i >= 324 || index + i < 0) {
			break;
		}
		
		if (grid->at(index + i) != NULL) {
			if (grid->at(index + i)->getType() == IWALL) {
				break;
			}
		}
		explosion = new Explosion(x + i*32, y, explosionPackage, -1, this);
		explosion->setZValue(1);
		connect(timer, SIGNAL(timeout()), explosion, SLOT(handleTimer()));
		connect(explosion, SIGNAL(destroy(GameObject*)), this, SLOT(destroyObject(GameObject*)));
		gameObjects->push_back(explosion);
		scene->addItem(explosion);
		if (grid->at(index + i) != NULL) {
			if (grid->at(index + i)->getType() == DWALL) {
				explosionDistance--;
			}
		}
	}
	
	explosionDistance = dist;
	for (int i = 1; i <= explosionDistance; i++) {
		if (index + i*18 >= 324 || index + i*18 < 0) {
			break;
		}
		if (grid->at(index + i*18) != NULL) {
			if (grid->at(index + i*18)->getType() == IWALL) {
				break;
			}
		}
		explosion = new Explosion(x, y + i*32, explosionPackage, -1, this);
		explosion->setZValue(1);
		connect(timer, SIGNAL(timeout()), explosion, SLOT(handleTimer()));
		connect(explosion, SIGNAL(destroy(GameObject*)), this, SLOT(destroyObject(GameObject*)));
		gameObjects->push_back(explosion);
		scene->addItem(explosion);
		if (grid->at(index + i*18) != NULL) {
			if (grid->at(index + i*18)->getType() == DWALL) {
				explosionDistance--;
			}
		}
	}
	
	explosionDistance = dist;
	for (int i = -1; i >= -explosionDistance; i--) {
		if (index + i*18 >= 324 || index + i*18 < 0) {
			break;
		}
		if (grid->at(index + i*18) != NULL) {
			if (grid->at(index + i*18)->getType() == IWALL) {
				break;
			}
		}
		explosion = new Explosion(x, y + i*32, explosionPackage, -1, this);
		explosion->setZValue(1);
		connect(timer, SIGNAL(timeout()), explosion, SLOT(handleTimer()));
		connect(explosion, SIGNAL(destroy(GameObject*)), this, SLOT(destroyObject(GameObject*)));
		gameObjects->push_back(explosion);
		scene->addItem(explosion);
		if (grid->at(index + i*18) != NULL) {
			if (grid->at(index + i*18)->getType() == DWALL) {
				explosionDistance--;
			}
		}
	}
}


/*------------------------------------GENERATETERRAIN------------------------------------------------*/
void GameWindow::generateTerrain() {
	Wall* wall;
	DWall* dWall;
	
	// Generate randomized terrain. 17% chance for a Wall, 33% chance for a DWall
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j < 17; j++) {
			int num = rand() % 100 + 1;
			if (num < 18) {
				wall = new Wall(j*32, i*32, wallSpr, i*18 + j, this);
				gameObjects->push_back(wall);
				scene->addItem(wall);
				grid->at(i*18 + j) = wall;
			} else if (num < 50) {
				dWall = new DWall(j*32, i*32, wallBrokenSpr, i*18 + j, this);
				gameObjects->push_back(dWall);
				scene->addItem(dWall);
				grid->at(i*18 + j) = dWall;
			}
		}
	}
}


/*------------------------------------SPAWNTHING------------------------------------------------*/
void GameWindow::spawnThing(QString type) {
	int loc = rand() % 323 + 1;
	int tries = 1;
	
	// Determine a random, valid location for the object in the grid
	while (grid->at(loc) != NULL) {
		loc = rand() % 323 + 1;
		tries++;
		if (tries >= 324) return;
	}
	
	if (loc == 19 || loc == 20 || loc == 37) {
		return;
	}
	
	int x = loc % 18;
	int y = (loc - x) / 18;
	
	// Spawn the object in the grid
	if (type == "Alien") {
		Alien* alien = new Alien(x*32, y*32, zerglingPackage, loc, grid, this, gameSpeed*0.8);
		connect(timer, SIGNAL(timeout()), alien, SLOT(handleTimer()));
		alien->setZValue(1);
		grid->at(loc) = alien;
		gameObjects->push_back(alien);
		scene->addItem(alien);
	} else if (type == "Powerup") {
		Powerup* powerup = new Powerup(x*32, y*32, powerupSpr, loc, grid, this, gameSpeed*0.7);
		powerup->setZValue(1);
		connect(timer, SIGNAL(timeout()), powerup, SLOT(handleTimer()));
		grid->at(loc) = powerup;
		gameObjects->push_back(powerup);
		scene->addItem(powerup);
	} else if (type == "Health") {
		Health* health = new Health(x*32, y*32, healthPickupSpr, loc, grid, this, gameSpeed);
		health->setZValue(1);
		connect(timer, SIGNAL(timeout()), health, SLOT(handleTimer()));
		grid->at(loc) = health;
		gameObjects->push_back(health);
		scene->addItem(health);
	}
}



