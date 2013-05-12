#include "missile.h"

/*------------------------------------MISSILE------------------------------------------------*/
Missile::Missile(int nx, int ny, DIRECTION dir, QPixmap* pix, int indx, GameWindow* prnt) : GameObject(nx, ny, pix, indx, prnt) {
	// Initialize variables
	type = MISSILE;
	speed = 1;
	setTransformOriginPoint(15, 15);
	
	// Determine which direction the Missile is flying and set its origin and velocity properly
	direction = dir;
	switch (direction) {
		case UP: {
			QGraphicsItem::setRotation(270);
			setPos(x(), y() - 32);
			ox = x();
			oy = y() - 32;
			vx = 0;
			vy = -1;
			break;
		}
		case DOWN: {
			QGraphicsItem::setRotation(90);
			setPos(x(), y() + 32);
			ox = x();
			oy = y() + 32;
			vx = 0;
			vy = 1;
			break;
		}
		case LEFT: {
			QGraphicsItem::setRotation(180);
			setPos(x() - 32, y());
			ox = x() - 32;
			oy = y();
			vx = -1;
			vy = 0;
			break;
		}
		case RIGHT: {
			setPos(x() + 32, y());
			ox = x() + 32;
			oy = y();
			vx = 1;
			vy = 0;
			break;
		}
		default: break;
	}
}


/*------------------------------------HANDLETIMER------------------------------------------------*/
void Missile::handleTimer() {	
	// Move the missile at an interval
	counter++;
	if (counter >= 1 / speed) {
		counter = 0;
		move();
	}
	
	// Determine if the Missile has reached the point where it should explode, and destroy it
	switch (direction) {
		case UP: {
			if (y() <= (oy - MISSILE_DISTANCE)) {
				emit explode(x(), y(), 1);
				emit destroy(this);
			}
			break;
		}
		case DOWN: {
			if (y() >= (oy + MISSILE_DISTANCE)) {
				emit explode(x(), y(), 1);
				emit destroy(this);
			}
			break;
		}
		case LEFT: {
			if (x() <= (ox - MISSILE_DISTANCE)) {
				emit explode(x(), y(), 1);
				emit destroy(this);
			}
			break;
		}
		case RIGHT: {
			if (x() >= (ox + MISSILE_DISTANCE)) {
				emit explode(x(), y(), 1);
				emit destroy(this);
			}
			break;
		}
		default: break;
	}
}


/*------------------------------------MOVE------------------------------------------------*/
void Missile::move(int dx, int dy) {
	// Effectively does nothing
	tx = dx;
	ty = dy;
}


/*------------------------------------MOVE------------------------------------------------*/
void Missile::move() {
	// Moves the missile forward
	setPos(x() + vx, y() + vy);
}



