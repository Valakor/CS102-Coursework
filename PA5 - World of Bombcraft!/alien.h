#ifndef ALIEN_H
#define ALIEN_H

#include "gameobject.h"

#include <vector>
#include <cmath>

class GameWindow;

/** GameObject representing an enemy Alien. Moves randomly and increases speed as gameSpeed increases. Takes a life
 * from the player if it collides with the player. */
class Alien : public GameObject {
public:
	/** Constructor. Creates an Alien at a location in the scene.
	 * @param nx The x coordinate of the Alien in the scene
	 * @param ny The y coordinate of the Alien in the scene
	 * @param pix The animation array containing the sprites for the Alien
	 * @param indx The index location of the Alien in the game's grid
	 * @param g The game's grid used to determine movement for the Alien
	 * @param prnt The Alien's parent. Should be of type GameWindow
	 * @param GSpd The Alien's initial gameSpeed */
	Alien(int nx, int ny, QPixmap** pix, int indx, std::vector<GameObject*>* g, GameWindow* prnt, float GSpd);
	
	/** Re-implemented from GameObject to do nothing. Is not used for movement, as this is used to create movement
	 * externally. Alien::move() allows autonomous movement in conjunction with Alien::determineMove(). */
	void move(int dx, int dy);
	
	/** Returns the value of this Alien in points.
	 * @return An integer (50 for base Aliens) used to increase the player's score */
	int pointValue();
	
	
public slots:
	/** Moves the Alien towards its target. If at its target, determines the Alien's next move. */
	void handleTimer();
	
	
protected:
	/** Visibly moves the Alien in the scene towards its target location, and stops when it has reached said target. */
	void move();
	
	/** Randomly determines a direction for the Alien to move towards iff it is a valid move (no Wall or DWall in the direction
	 * of movement). */
	bool determineMove();
	
	
private:
	QPixmap** sprites;		/**< The array holding the Alien's sprites */
	DIRECTION direction;	/**< The direction in which the Alien is facing. Used to set the correct sprite. */
	
	std::vector<GameObject*>* grid;		/**< Abstract representation of the game's grid, used to determine movement. */
	
	int points;		/**< The number of points this Alien is worth. */
};

#endif
