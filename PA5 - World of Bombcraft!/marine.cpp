#include "marine.h"

/*------------------------------------MARINE------------------------------------------------*/
Marine::Marine(int nx, int ny, QPixmap** pix, int indx, GameWindow* prnt, float GSpd) : GameObject(nx, ny, pix[DOWN], indx, prnt, GSpd) {
	// Initialize gameplay variables
	invulnerable = true;
	sprOn = true;
	invulnerableCounter = 0;
	direction = DOWN;
	sprites = pix;
	type = MARINE;
	vx = 2;
	vy = 2;
	speed = 25;
	lives = 3;
	missiles = 1;
}


/*------------------------------------MOVE------------------------------------------------*/
void Marine::move(int dx, int dy) {
	// Determine next move location iff not currently moving
	if (!canMove) {
		tx = x() + dx;
		ty = y() + dy;
		canMove = true;
	}
}


/*------------------------------------GETLIVES------------------------------------------------*/
int Marine::getLives() {
	return lives;
}


/*------------------------------------REMOVELIFE------------------------------------------------*/
bool Marine::removeLife() {
	// Remove a life iff Marine is not currently invulerable
	if (!invulnerable) {
		lives--;
		invulnerable = true;
		return true;
	}
	return false;
}


/*------------------------------------ADDLIFE------------------------------------------------*/
bool Marine::addLife() {
	// Add a life iff player has less than 3 lives
	if (lives < 3) {
		lives++;
		return true;
	}
	return false;
}


/*------------------------------------GETMISSILES------------------------------------------------*/
int Marine::getMissiles() {
	return missiles;
}


/*------------------------------------GETDIRECTION------------------------------------------------*/
DIRECTION Marine::getDirection() {
	return direction;
}


/*------------------------------------CHANGEDIRECTION------------------------------------------------*/
void Marine::changeDirection(DIRECTION newDirection) {
	// Change the direction the Marine faces
	if (direction != newDirection) {
		QGraphicsPixmapItem::setPixmap(*(sprites[newDirection]));
		direction = newDirection;
	}
}


/*------------------------------------CHANGEMISSILE------------------------------------------------*/
void Marine::changeMissile(int num) {
	if (num > 0) {
		if (missiles >= 0 && missiles < 3) {	
			missiles += num;
		}
	} else if (num < 0) {
		if (missiles > 0 && missiles <= 3) {	
			missiles += num;
		}
	}
}


/*------------------------------------HANDLETIMER------------------------------------------------*/
void Marine::handleTimer() {
	counter++;
	if (counter >= (double)speed/gameSpeed && canMove) {
		counter = 0;
		move();
	}
	
	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter % BLINKSPEED == BLINKSPEED - 1) {
			if (sprOn) {
				QGraphicsPixmapItem::setPixmap(NULL);
				sprOn = false;
			} else {
				QGraphicsPixmapItem::setPixmap(*(sprites[direction]));
				sprOn = true;
			}
		}
		if (invulnerableCounter >= 1500) {
			invulnerableCounter = 0;
			invulnerable = false;
			sprOn = true;
			QGraphicsPixmapItem::setPixmap(*(sprites[direction]));
		}
	}
}


/*------------------------------------MOVE------------------------------------------------*/
void Marine::move() {
	if (x() == tx && y() == ty) {
		canMove = false;
		return;
	}
	
	if (tx > x()) {
		QGraphicsPixmapItem::setPos(x() + vx, y());
		direction = RIGHT;
		if (sprOn) {
			QGraphicsPixmapItem::setPixmap(*(sprites[direction]));
		}
	} else if (tx < x()) {
		QGraphicsPixmapItem::setPos(x() - vx, y());
		direction = LEFT;
		if (sprOn) {
			QGraphicsPixmapItem::setPixmap(*(sprites[direction]));
		}
	} else if (ty > y()) {
		QGraphicsPixmapItem::setPos(x(), y() + vy);
		direction = DOWN;
		if (sprOn) {
			QGraphicsPixmapItem::setPixmap(*(sprites[direction]));
		}
	} else if (ty < y()) {
		QGraphicsPixmapItem::setPos(x(), y() - vy);
		direction = UP;
		if (sprOn) {
			QGraphicsPixmapItem::setPixmap(*(sprites[direction]));
		}
	}
}
