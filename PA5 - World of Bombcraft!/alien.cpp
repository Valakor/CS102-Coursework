#include "alien.h"

/*------------------------------------ALIEN------------------------------------------------*/
Alien::Alien(int nx, int ny, QPixmap** pix, int indx, std::vector<GameObject*>* g, GameWindow* prnt, float GSpd) : GameObject(nx, ny, pix[DOWN], indx, prnt, GSpd) {
	// Set initial gameplay values
	grid = g;
	direction = DOWN;
	sprites = pix;
	type = ALIEN;
	vx = 1;
	vy = 1;
	speed = 25;
	canMove = false;
	srand(time(NULL));
	points = 50;
}


/*------------------------------------MOVE------------------------------------------------*/
void Alien::move(int dx, int dy) {
	// Effectively does nothing
	dx = dx;
	dy = dy;
}


/*------------------------------------POINTVALUE------------------------------------------------*/
int Alien::pointValue() {
	return points;
}


/*------------------------------------HANDLETIMER------------------------------------------------*/
void Alien::handleTimer() {
	// Can only determine its next move once it is done moving to its current target location
	if (!canMove) {
		canMove = determineMove();
		return;
	}
	
	// Moves the alien at an increasing rate
	counter++;
	if (counter >= (double)speed/gameSpeed && canMove) {
		counter = 0;
		move();
	}
}


/*------------------------------------MOVE------------------------------------------------*/
void Alien::move() {
	// If at its target, set canMove so that another move can be determined
	if (x() == tx && y() == ty) {
		canMove = false;
		return;
	}
	
	// Move towards target location
	if (tx > x()) {
		QGraphicsPixmapItem::setPos(x() + vx, y());
		direction = RIGHT;
	} else if (tx < x()) {
		QGraphicsPixmapItem::setPos(x() - vx, y());
		direction = LEFT;
	} else if (ty > y()) {
		QGraphicsPixmapItem::setPos(x(), y() + vy);
		direction = DOWN;
	} else if (ty < y()) {
		QGraphicsPixmapItem::setPos(x(), y() - vy);
		direction = UP;
	}
}


/*------------------------------------DETERMINEMOVE------------------------------------------------*/
bool Alien::determineMove() {	
	// Randomize a direction corresponding to RIGHT, LEFT, DOWN, UP
	// Will only set the target of movement if it is a valid move (no Wall or DWall is in the grid in the direction of movement)
	switch (rand() % 4) {
		case 0: {
			if (grid->at(index+1) == NULL) {	
				tx = x() + 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index+1) = this;
				index = index + 1;
				QGraphicsPixmapItem::setPixmap(*(sprites[RIGHT]));
				return true;
			} else if (grid->at(index+1)->getType() == MARINE) {
				tx = x() + 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index+1) = this;
				index = index + 1;
				QGraphicsPixmapItem::setPixmap(*(sprites[RIGHT]));
				return true;
			} else if (grid->at(index+1)->getType() == POWERUP) {
				tx = x() + 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index+1) = this;
				index = index + 1;
				QGraphicsPixmapItem::setPixmap(*(sprites[RIGHT]));
				return true;
			} else if (grid->at(index+1)->getType() == HEALTH) {
				tx = x() + 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index+1) = this;
				index = index + 1;
				QGraphicsPixmapItem::setPixmap(*(sprites[RIGHT]));
				return true;
			}
			break;
		}
		case 1: {
			if (grid->at(index-1) == NULL) {	
				tx = x() - 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index-1) = this;
				index = index - 1;
				QGraphicsPixmapItem::setPixmap(*(sprites[LEFT]));
				return true;
			} else if (grid->at(index-1)->getType() == MARINE) {
				tx = x() - 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index-1) = this;
				index = index - 1;
				QGraphicsPixmapItem::setPixmap(*(sprites[LEFT]));
				return true;
			} else if (grid->at(index-1)->getType() == POWERUP) {
				tx = x() - 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index-1) = this;
				index = index - 1;
				QGraphicsPixmapItem::setPixmap(*(sprites[LEFT]));
				return true;
			} else if (grid->at(index-1)->getType() == HEALTH) {
				tx = x() - 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index-1) = this;
				index = index - 1;
				QGraphicsPixmapItem::setPixmap(*(sprites[LEFT]));
				return true;
			}
			break;
		}
		case 2: {
			if (grid->at(index+18) == NULL) {	
				tx = x();
				ty = y() + 32;
				grid->at(index) = NULL;
				grid->at(index+18) = this;
				index = index + 18;
				QGraphicsPixmapItem::setPixmap(*(sprites[DOWN]));
				return true;
			} else if (grid->at(index+18)->getType() == MARINE) {
				tx = x();
				ty = y() + 32;
				grid->at(index) = NULL;
				grid->at(index+18) = this;
				index = index + 18;
				QGraphicsPixmapItem::setPixmap(*(sprites[DOWN]));
				return true;
			} else if (grid->at(index+18)->getType() == POWERUP) {
				tx = x();
				ty = y() + 32;
				grid->at(index) = NULL;
				grid->at(index+18) = this;
				index = index + 18;
				QGraphicsPixmapItem::setPixmap(*(sprites[DOWN]));
				return true;
			} else if (grid->at(index+18)->getType() == HEALTH) {
				tx = x();
				ty = y() + 32;
				grid->at(index) = NULL;
				grid->at(index+18) = this;
				index = index + 18;
				QGraphicsPixmapItem::setPixmap(*(sprites[DOWN]));
				return true;
			}
			break;
		}
		case 3: {
			if (grid->at(index-18) == NULL) {	
				tx = x();
				ty = y() - 32;
				grid->at(index) = NULL;
				grid->at(index-18) = this;
				index = index - 18;
				QGraphicsPixmapItem::setPixmap(*(sprites[UP]));
				return true;
			} else if (grid->at(index-18)->getType() == MARINE) {
				tx = x();
				ty = y() - 32;
				grid->at(index) = NULL;
				grid->at(index-18) = this;
				index = index - 18;
				QGraphicsPixmapItem::setPixmap(*(sprites[UP]));
				return true;
			} else if (grid->at(index-18)->getType() == POWERUP) {
				tx = x();
				ty = y() - 32;
				grid->at(index) = NULL;
				grid->at(index-18) = this;
				index = index - 18;
				QGraphicsPixmapItem::setPixmap(*(sprites[UP]));
				return true;
			} else if (grid->at(index-18)->getType() == HEALTH) {
				tx = x();
				ty = y() - 32;
				grid->at(index) = NULL;
				grid->at(index-18) = this;
				index = index - 18;
				QGraphicsPixmapItem::setPixmap(*(sprites[UP]));
				return true;
			}
			break;
		}
		default: break;
	}
	return false;
}




