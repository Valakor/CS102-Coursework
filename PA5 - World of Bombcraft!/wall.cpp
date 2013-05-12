#include "wall.h"

/*------------------------------------WALL------------------------------------------------*/
Wall::Wall(int nx, int ny, QPixmap* pix, int indx, GameWindow* prnt) : GameObject(nx, ny, pix, indx, prnt) {
	type = IWALL;
}


/*------------------------------------MOVE------------------------------------------------*/
void Wall::move(int dx, int dy) {
	tx = dx;
	ty = dy;
}
