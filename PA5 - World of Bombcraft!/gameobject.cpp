#include "gameobject.h"

/*------------------------------------GAMEOBJECT------------------------------------------------*/
GameObject::GameObject(int nx, int ny, QPixmap* pix, int indx, GameWindow* prnt, float GSpd) : QObject(), QGraphicsPixmapItem(*pix) {
	// Set initial values
	parent = prnt;
	QGraphicsPixmapItem::setPos(nx, ny);
	counter = 0;
	
	gameSpeed = GSpd;
	
	index = indx;
	
	canMove = false;
	tx = 0;
	ty = 0;
	vx = 0;
	vy = 0;
	speed = 0;
	
	type = NONE;
}


/*------------------------------------SETGAMESPEED------------------------------------------------*/
void GameObject::setGameSpeed(float nSpeed) {
	gameSpeed = nSpeed;
}
