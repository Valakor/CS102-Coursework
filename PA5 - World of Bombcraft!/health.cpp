#include "health.h"

/*------------------------------------HEALTH------------------------------------------------*/
Health::Health(int nx, int ny, QPixmap* pix, int indx, std::vector<GameObject*>* g, GameWindow* prnt, float GSpd) : GameObject(nx, ny, pix, indx, prnt, GSpd) {
	// Initialize gameplay values
	grid = g;
	type = HEALTH;
	vx = 1;
	vy = 1;
	speed = 10000;
	srand(time(NULL));
}


/*------------------------------------MOVE------------------------------------------------*/
void Health::move(int dx, int dy) {
	// Effectively does nothing
	dx = dx;
	dy = dy;
}


/*------------------------------------HANDLETIMER------------------------------------------------*/
void Health::handleTimer() {
	// Jump to a new location at an interval determined by speed and the gameSpeed
	counter++;
	if (counter >= (double)speed/gameSpeed) {
		counter = 0;
		move();
	}
}


/*------------------------------------MOVE------------------------------------------------*/
void Health::move() {
	int loc = rand() % 323 + 1;
	int tries = 1;
	
	// Determine a valid random location to jump to
	while (grid->at(loc) != NULL) {
		loc = rand() % 323 + 1;
		tries++;
		if (tries >= 324) return;
	}
	
	int x = loc % 18;
	int y = (loc - x) / 18;
	
	// Move to that randomized location
	setPos(x*32, y*32);
}




