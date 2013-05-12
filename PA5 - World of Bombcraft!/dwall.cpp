#include "dwall.h"

/*------------------------------------DWALL------------------------------------------------*/
DWall::DWall(int nx, int ny, QPixmap* pix, int indx, GameWindow* prnt) : GameObject(nx, ny, pix, indx, prnt) {
	type = DWALL;
}


/*------------------------------------MOVE------------------------------------------------*/
void DWall::move(int dx, int dy) {
	tx = dx;
	ty = dy;
}
