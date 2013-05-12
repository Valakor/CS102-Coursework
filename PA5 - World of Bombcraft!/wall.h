#ifndef WALL_H
#define WALL_H

#include "gameobject.h"

class GameWindow;

/** An indestructible wall. Prevents movement by all other GameObjects. */
class Wall : public GameObject {
public:
	/** Constructor. Creates a Wall at a location in the scene.
	 * @param nx The x coordinate of the Wall in the scene
	 * @param ny The y coordinate of the Wall in the scene
	 * @param pix The Wall's sprite
	 * @param indx The index location of the Wall in the game's grid
	 * @param prnt The Wall's parent. Should be of type GameWindow */
	Wall(int nx, int ny, QPixmap* pix, int indx, GameWindow* prnt);
	
	/** Re-implemented from GameObject to do nothing, as Walls cannot move. */
	void move(int dx, int dy);
	
	
public slots:
	/** Re-implemented from GameObject to do nothing, as Walls take no action. */
	void handleTimer() {};
	
	
protected:
	/** Re-implemented from GameObject to do nothing, as Walls cannot move. */
	void move() {};
};

#endif
