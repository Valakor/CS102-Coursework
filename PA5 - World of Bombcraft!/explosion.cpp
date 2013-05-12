#include "explosion.h"

/*------------------------------------EXPLOSION------------------------------------------------*/
Explosion::Explosion(int nx, int ny, QPixmap** pix, int indx, GameWindow* prnt) : GameObject(nx, ny, pix[0], indx, prnt) {
	// Set initial gameplay values
	sprites = pix;
	type = EXPLOSION;
	animIndex = 0;
	hitMarine = false;
}


/*------------------------------------HANDLETIMER------------------------------------------------*/
void Explosion::handleTimer() {
	// Iterate through the animation to make the explosion look more realistic and less static
	counter++;
	if (counter % (EXPLOSION_COUNTDOWN / 6) == (EXPLOSION_COUNTDOWN / 6 - 1) && animIndex < 5) {
		animIndex++;
		QGraphicsPixmapItem::setPixmap(*(sprites[animIndex]));
	}
	
	// Destroy this object if the animation is done
	if (counter >= EXPLOSION_COUNTDOWN) {
		counter = EXPLOSION_COUNTDOWN*2;
		emit destroy(this);
	}
}


/*------------------------------------MOVE------------------------------------------------*/
void Explosion::move(int dx, int dy) {
	// Essentially does nothing
	tx = dx;
	ty = dy;
}


/*------------------------------------HIT------------------------------------------------*/
void Explosion::hit() {
	hitMarine = true;
}


/*------------------------------------HASHIT------------------------------------------------*/
bool Explosion::hasHit() {
	return hitMarine;
}
