#ifndef MARINE_H
#define MARINE_H

#include "gameobject.h"

#define BLINKSPEED 200

class GameWindow;

/** GameObject representing a Marine that the player controls during gameplay. Its x and y velocity
 * are both 2. */
class Marine : public GameObject {
public:
	/** Constructor. Creates a Marine at a location in the scene.
	 * @param nx The x coordinate of the Marine in the scene
	 * @param ny The y coordinate of the Marine in the scene
	 * @param pix The animation array containing the sprites for the Marine
	 * @param indx The index location of the Marine in the game's grid
	 * @param prnt The Marine's parent. Should be of type GameWindow
	 * @param GSpd The Marine's initial gameSpeed */
	Marine(int nx, int ny, QPixmap** pix, int indx, GameWindow* prnt, float GSpd);
	
	/** If the Marine is not currently moving, sets the desired target location and
	 * starts movement.
	 * @param dx Amount of movement in the x direction
	 * @param dy Amount of movement in the y direction */
	void move(int dx, int dy);
	
	/** Returns the number of lives the player currently has.
	 * @return An integer [0-3] corresponding to the number of lives the player has */
	int getLives();
	
	/** Removes a life from the player if possible.
	 * @return True if successful removal of life, false if player already has 0 lives left
	 * @post Private member lives is decremented by 1 if possible */
	bool removeLife();
	
	/** Adds a life to the player.
	 * @return True if life is successfully added, false if the player already has 3 lives
	 * @post Private member lives is incremented by 1 if possible */
	bool addLife();
	
	/** Returns the number of missiles that the player currently has in stock.
	 * @return An integer [0-3] corresponding to the number of missiles the player has */
	int getMissiles();
	
	/** Changes the number of missiles the player has by a certain amount.
	 * @pre Player must have 1 or more missiles to decrement, 2 or less missiles to increment
	 * @param num How many missiles to add or subtract */
	void changeMissile(int num);
	
	/** Returns the cardinal direction of the Marine
	 * @return Enum DIRECTION corresponding to what direction the Marine is facing (either UP, DOWN, LEFT, or RIGHT) */
	DIRECTION getDirection();
	
	/** Changes the direction the Marine is facing in the scene.
	 * @param newDirection The new direction to face */
	void changeDirection(DIRECTION newDirection);
	
	
public slots:
	/** Called every 1 millisecond by GameWindow's timer. Determines when to move the Marine, and
	 * how to act when invulnerable. */
	void handleTimer();
	
	
protected:
	/** Visibly moves the Marine in the scene towards its target location, and stops when it has reached said target. */
	void move();
	
	
private:
	QPixmap** sprites;		/**< The array holding the Marine's animation */
	DIRECTION direction;	/**< The DIRECTION in which the Marine is facing in the scene */
	
	bool invulnerable;			/**< Whether or not the Marine can currently take life damage. Any life damage sets this to true for a short period of time, preventing further damage. */
	int invulnerableCounter;	/**< How long the Marine is invulernable when invulerable is true. */
	bool sprOn;					/**< Whether or not the Marine's sprite is visible (Marine flashes on and off during invincibility) */
	
	int lives;		/**< The number of lives the Marine has [0-3] */
	int missiles;	/**< The number of missiles the Marine has [0-3] */
};

#endif
