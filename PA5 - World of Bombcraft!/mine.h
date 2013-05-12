#ifndef MINE_H
#define MINE_H

#include "gameobject.h"

class GameWindow;

#define MINE_COUNTDOWN 1750

/** A GameObject representing an explosive Mine. Explodes after 1.75 seconds automatically. */
class Mine : public GameObject {
	Q_OBJECT
	
public:
	/** Constructor. Creates a Mine at a location in the scene.
	 * @param nx The x coordinate of the Mine in the scene
	 * @param ny The y coordinate of the Mine in the scene
	 * @param pix The animation array containing the sprites for the Mine
	 * @param indx The index location of the Mine in the game's grid. Usually set to -1 because the mine does not collide with anything
	 * @param prnt The Mine's parent. Should be of type GameWindow */
	Mine(int nx, int ny, QPixmap** pix, int indx, GameWindow* prnt);
	
	/** Re-implemented from GameObject to do nothing, as Mines cannot move. */
	void move(int dx, int dy);
	
	
public slots:
	/** Animates the Mine and determines when the Mine should explode and be destroyed. */
	void handleTimer();
	
	
signals:
	/** Tells the GameWindow that the Mine should be destroyed and removed from the gameObjects list.
	 * @param e The mine to be destroyed (this) */
	void destroy(GameObject* e);
	
	/** Tells the GameWindow that the Mine is exploding and that an appropriate explosion should be created.
	 * @param x The x coordinate of the Mine in the scene
	 * @param y The y coordinate of the Mine in the scene
	 * @param dist The size of the explosion in every direction (3) */
	void explode(int x, int y, int dist);
	
	
protected:
	/** Re-implemented from GameObject to do nothing, as Mines cannot move. */
	void move() {};
	
	
private:
	bool on;			/**< Whether or not the Mine's animation shows the mine as flashing on or off */
	QPixmap** sprites;	/**< The array holding the Mine's animation sprites */
	
	int countdown;		/**< Time before the Mine explodes */
};

#endif
