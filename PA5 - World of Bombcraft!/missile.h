#ifndef MISSILE_H
#define MISSILE_H

#include "gameobject.h"

class GameWindow;

#define MISSILE_DISTANCE 160

/** A GameObject representing a Missile that the player can fire. */
class Missile : public GameObject {
	Q_OBJECT

public:
	/** Constructor. Creates a Missile at a location in the scene that will fly in a given direction until it explodes after 5 grid spaces.
	 * @param nx The x coordinate of the Missile in the scene
	 * @param ny The y coordinate of the Missile in the scene
	 * @param dir The direction the Missile is flying
	 * @param pix The Missile's sprite
	 * @param indx The index location of the Missile in the game's grid
	 * @param prnt The Marine's parent. Should be of type GameWindow */
	Missile(int nx, int ny, DIRECTION dir, QPixmap* pix, int indx, GameWindow* prnt);
	
	/** Re-implemented from GameObject to do nothing, as the Missile cannot be moved externally. */
	void move(int dx, int dy);
	
	
public slots:
	/** Moves the Missile and determines when it should explode. */
	void handleTimer();
	
	
signals:
	/** Tells the GameWindow that the Missile should be destroyed.
	 * @param e The Missile to be destroyed (this) */
	void destroy(GameObject* e);
	
	/** Tells the GameWindow to create an explosion at this Missile's location.
	 * @param x The x coordinate of the explosion to be created
	 * @param y The y coordinate of the explosion to be created
	 * @param dist The size of the explosion from its center (1 for a Missile) */
	void explode(int x, int y, int dist);
	
	
protected:
	/** Moves the Missile according to its velocity. */
	void move();
	
	
private:
	int speed;				/**< The speed at which the Missile acts */
	DIRECTION direction;	/**< The DIRECTION the Missile is facing */
	
	int ox;					/**< The Missile's origin x coordinate */
	int oy;					/**< The Missile's origin y coordinate */
};

#endif
