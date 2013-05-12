#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"
#include <iostream>

class GameWindow;

#define EXPLOSION_COUNTDOWN 396

/** GameObject representing an Explosion caused by a Mine or Missile. Destroys everything but indestructible walls (Wall), and
 * causes 1 life damage to the player. */
class Explosion : public GameObject {
	Q_OBJECT
	
public:
	/** Constructor. Creates an Explosion at a location in the scene.
	 * @param nx The x coordinate of the Explosion in the scene
	 * @param ny The y coordinate of the Explosion in the scene
	 * @param pix The animation array containing the sprites for the Explosion
	 * @param indx The index location of the Explosion in the game's grid. Usually set to -1 as Explosions are temporary and hold no physical location in the grid
	 * @param prnt The Explosion's parent. Should be of type GameWindow */
	Explosion(int nx, int ny, QPixmap** pix, int indx, GameWindow* prnt);
	
	/** Re-implmeneted from GameObject to do nothing because Explosions cannot be moved from external sources. */
	void move(int dx, int dy);
	
	/** Flags this Explosion with hitMarine = true so that it cannot cause additional damage to the player. */
	void hit();
	
	/** Returns whether or not this Explosion has already his the player.
	 * @return True if a collision with the player has already occurred, false otherwise */
	bool hasHit();
	
	
public slots:
	/** Animates the Explosion until its animation is done, then destroys it. */
	void handleTimer();
	
	
signals:
	/** Tells the GameWindow that this Explosion should be destroyed. */
	void destroy(GameObject* e);
	
	
protected:
	/** Re-implemented from GameObject to do nothing, as Explosions cannot move. */
	void move() {};
	
	
private:
	QPixmap** sprites;	/**< The array holding the Explosion's animation */
	
	int animIndex;		/**< The current index of the Explosion's animation in the sprites array */	
	
	bool hitMarine;		/**< Whether or not the Explosion has collided with a Marine already */
};

#endif
