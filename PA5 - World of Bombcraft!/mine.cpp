#include "mine.h"

/*------------------------------------MINE------------------------------------------------*/
Mine::Mine(int nx, int ny, QPixmap** pix, int indx, GameWindow* prnt) : GameObject(nx, ny, pix[0], indx, prnt) {
	// Set intial values
	sprites = pix;
	type = MINE;
	on = true;
	countdown = MINE_COUNTDOWN;
}


/*------------------------------------HANDLETIMER------------------------------------------------*/
void Mine::handleTimer() {
	// Animate the mine
	counter++;
	if (counter >= 200) {
		counter = 0;
		if (on) {
			QGraphicsPixmapItem::setPixmap(*(sprites[1]));
			on = false;
		} else {
			QGraphicsPixmapItem::setPixmap(*(sprites[0]));
			on = true;
		}
	}
	
	// Explode and destroy the mine
	countdown--;
	if (countdown <= 0) {
		countdown = MINE_COUNTDOWN*2;
		emit explode(x(), y(), 3);
		emit destroy(this);
	}
}


/*------------------------------------MOVE------------------------------------------------*/
void Mine::move(int dx, int dy) {
	// Effectively does nothing
	tx = dx;
	ty = dy;
}
