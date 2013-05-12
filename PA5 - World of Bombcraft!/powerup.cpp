#include "powerup.h"

/*------------------------------------POWERUP------------------------------------------------*/
Powerup::Powerup(int nx, int ny, QPixmap* pix, int indx, std::vector<GameObject*>* g, GameWindow* prnt, float GSpd) : GameObject(nx, ny, pix, indx, prnt, GSpd) {
	// Initialize variables
	grid = g;
	type = POWERUP;
	vx = 1;
	vy = 1;
	speed = 30;
	canMove = false;
	srand(time(NULL));
}


/*------------------------------------MOVE------------------------------------------------*/
void Powerup::move(int dx, int dy) {
	// Effectively does nothing
	dx = dx;
	dy = dy;
}


/*------------------------------------HANDLETIMER------------------------------------------------*/
void Powerup::handleTimer() {
	// If at its current target, determine the next move
	if (!canMove) {
		canMove = determineMove();
		return;
	}
	
	// Move towards the current target
	counter++;
	if (counter >= (double)speed/gameSpeed && canMove) {
		counter = 0;
		move();
	}
}


/*------------------------------------MOVE------------------------------------------------*/
void Powerup::move() {
	if (x() == tx && y() == ty) {
		canMove = false;
		return;
	}
	
	// Move towards the current target
	if (tx > x()) {
		QGraphicsPixmapItem::setPos(x() + vx, y());
	} else if (tx < x()) {
		QGraphicsPixmapItem::setPos(x() - vx, y());
	} else if (ty > y()) {
		QGraphicsPixmapItem::setPos(x(), y() + vy);
	} else if (ty < y()) {
		QGraphicsPixmapItem::setPos(x(), y() - vy);
	}
}


/*------------------------------------DETERMINEMOVE------------------------------------------------*/
bool Powerup::determineMove() {	
	// Determine a random direction of movement and move there if valid
	switch (rand() % 4) {
		case 0: {
			if (grid->at(index+1) == NULL) {	
				tx = x() + 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index+1) = this;
				index = index + 1;
				return true;
			} else if (grid->at(index+1)->getType() == MARINE) {
				tx = x() + 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index+1) = this;
				index = index + 1;
				return true;
			} else if (grid->at(index+1)->getType() == ALIEN) {
				tx = x() + 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index+1) = this;
				index = index + 1;
				return true;
			} else if (grid->at(index+1)->getType() == HEALTH) {
				tx = x() + 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index+1) = this;
				index = index + 1;
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
				return true;
			} else if (grid->at(index-1)->getType() == MARINE) {
				tx = x() - 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index-1) = this;
				index = index - 1;
				return true;
			} else if (grid->at(index-1)->getType() == ALIEN) {
				tx = x() - 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index-1) = this;
				index = index - 1;
				return true;
			} else if (grid->at(index-1)->getType() == HEALTH) {
				tx = x() - 32;
				ty = y();
				grid->at(index) = NULL;
				grid->at(index-1) = this;
				index = index - 1;
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
				return true;
			} else if (grid->at(index+18)->getType() == MARINE) {
				tx = x();
				ty = y() + 32;
				grid->at(index) = NULL;
				grid->at(index+18) = this;
				index = index + 18;
				return true;
			} else if (grid->at(index+18)->getType() == ALIEN) {
				tx = x();
				ty = y() + 32;
				grid->at(index) = NULL;
				grid->at(index+18) = this;
				index = index + 18;
				return true;
			} else if (grid->at(index+18)->getType() == HEALTH) {
				tx = x();
				ty = y() + 32;
				grid->at(index) = NULL;
				grid->at(index+18) = this;
				index = index + 18;
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
				return true;
			} else if (grid->at(index-18)->getType() == MARINE) {
				tx = x();
				ty = y() - 32;
				grid->at(index) = NULL;
				grid->at(index-18) = this;
				index = index - 18;
				return true;
			} else if (grid->at(index-18)->getType() == ALIEN) {
				tx = x();
				ty = y() - 32;
				grid->at(index) = NULL;
				grid->at(index-18) = this;
				index = index - 18;
				return true;
			} else if (grid->at(index-18)->getType() == HEALTH) {
				tx = x();
				ty = y() - 32;
				grid->at(index) = NULL;
				grid->at(index-18) = this;
				index = index - 18;
				return true;
			}
			break;
		}
		default: break;
	}
	return false;
}




