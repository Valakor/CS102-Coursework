#ifndef DWALL_H
#define DWALL_H

#include "gameobject.h"

class GameWindow;

/** A destructible wall. Prevents movement by all other GameObjects and can be destroyed by Explosions. */
class DWall : public GameObject {
public:
	/** Constructor. Creates a DWall at a location in the scene.
	 * @param nx The x coordinate of the DWall in the scene
	 * @param ny The y coordinate of the DWall in the scene
	 * @param pix The DWall's sprite
	 * @param indx The index location of the DWall in the game's grid
	 * @param prnt The DWall's parent. Should be of type GameWindow */
	DWall(int nx, int ny, QPixmap* pix, int indx, GameWindow* prnt);
	
	/** Re-implemented from GameObject to do nothing, as DWalls cannot move. */
	void move(int dx, int dy);
	
	
public slots:
	/** Re-implemented from GameObject to do nothing, as DWalls take no action. */
	void handleTimer() {};
	
	
protected:
	/** Re-implemented from GameObject to do nothing, as DWalls cannot move. */
	void move() {};
};

#endif
