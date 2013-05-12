#ifndef HEALTH_H
#define HEALTH_H

#include "gameobject.h"

#include <vector>
#include <cmath>

class GameWindow;

/** A GameObject that can be picked up the the player during gameplay to increase lives by 1. */
class Health : public GameObject {
public:
	/** Constructor. Creates a Health powerup at a location in the scene.
	 * @param nx The x coordinate of the Health powerup in the scene
	 * @param ny The y coordinate of the Health powerup in the scene
	 * @param pix The Health powerup's sprite
	 * @param indx The index location of the Health powerup in the game's grid
	 * @param g The game's grid used to determine movement for the Health powerup
	 * @param prnt The Health powerup's parent. Should be of type GameWindow
	 * @param GSpd The Health powerup's initial gameSpeed */
	Health(int nx, int ny, QPixmap* pix, int indx, std::vector<GameObject*>* g, GameWindow* prnt, float GSpd);
	
	/** Re-implemented from GameObject to do nothing, as the Health powerup cannot be moved externally. */
	void move(int dx, int dy);
	
	
public slots:
	/** Moves the Health powerup at an interval determined by gameSpeed. */
	void handleTimer();
	
	
protected:
	/** Picks a random valid location on the grid and snaps the Health powerup to that location. */
	void move();
	
	
private:
	std::vector<GameObject*>* grid;	/**< The abstract representation of the game's grid */
};

#endif
