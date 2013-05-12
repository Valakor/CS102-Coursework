#ifndef POWERUP_H
#define POWERUP_H

#include "gameobject.h"

#include <vector>
#include <cmath>

class GameWindow;


class Powerup : public GameObject {
public:
	/** Constructor. Creates a Powerup at a location in the scene that moves around randomly.
	 * @param nx The x coordinate of the Powerup in the scene
	 * @param ny The y coordinate of the Powerup in the scene
	 * @param pix The Powerup's sprite
	 * @param indx The index location of the Powerup in the game's grid
	 * @param g The game's grid used to determine movement for the Powerup
	 * @param prnt The Marine's parent. Should be of type GameWindow
	 * @param GSpd The game's speed used to make the Powerup move faster */
	Powerup(int nx, int ny, QPixmap* pix, int indx, std::vector<GameObject*>* g, GameWindow* prnt, float GSpd);
	
	/** Re-implemented from GameObject to do nothing, as the Powerup cannot be moved externally. */
	void move(int dx, int dy);
	
	
public slots:
	/** Determines how fast the Powerup moves and where its next movement will be. */
	void handleTimer();
	
	
protected:
	/** Moves the Powerup towards its target location. */
	void move();
	
	/** Determines a valid location to move the Powerup to in the grid.
	 * @return True if a valid move was found, false otherwise */
	bool determineMove();
	
	
private:
	std::vector<GameObject*>* grid;	/**< The abstract representation of the game's grid used to determine valid moves */
};

#endif
