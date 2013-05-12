#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtGui>
#include "gameobject.h"
#include "wall.h"
#include "dwall.h"
#include "marine.h"
#include "mine.h"
#include "explosion.h"
#include "missile.h"
#include "alien.h"
#include "powerup.h"
#include "health.h"

#include <list>
#include <time.h>

/** Visualizes the game in a QGraphicsView and handles all gameplay. */

class GameWindow : public QGraphicsView {
	Q_OBJECT

public:
	/** Main constructor. Creates a visible area for gameplay.
	 * @param nWidth Width of the visible window in pixels
	 * @param nHeight Height of the visible window in pixels
	 * @param prnt The parent of this object. Should be of type MainWindow */
	explicit GameWindow(int nWidth = 576, int nHeight = 576, QWidget* prnt = 0);
	
	/** Default destructor. Clears the list of GameObjects from the scene */
	~GameWindow();
	
	/** Starts the timer within the GameWindow, enabling movement and gameplay */
	void startTimer();
	
	/** Stops the timer within the GameWindow, disabling movement and gameplay */
	void stopTimer();
	
	/** Moves the player (a Marine) by a certain amount if the move is valid (there are no collidable
	 * objects in the direction of the move).
	 * @param dx Number of pixels to move in the x direction
	 * @param dy Number of pixels to move in the y direction */
	void movePlayer(int dx, int dy);
	
	/** Creates an explosive at the player's location. 
	 * @param type Either Mine or Missile */
	void spawnExplosive(QString type);

	
public slots:
	/** Called by MainWindow's start function. Generates random terrain, spawns the player,
	 * sets initial gameplay values, and starts the timer. */
	void start();
	
	/** Resets gameplay values to initial states and removes all terrain, the player, enemies, etc. from
	 * the scene. */
	void reset();
	
	/** Manages all gameplay. Handles the spawning of all objects in the scene and their collisions. */
	void handleTimer();
	
	/** Removes an object from the scene and from the list of all GameObjects and deletes it.
	 * @param g The object to destroy */
	void destroyObject(GameObject* g);
	
	/** Creates an explosion using Explosion objects at a given point and with a given explosive distance A Wall stops
	 * the explosion in the direction of the Wall, and a DWall decreases the Explosion distance by 1 in the direction of
	 * the DWall.
	 * @param x The x coordinate of the explosion's center
	 * @param y The y coordinate of the explosion's center
	 * @param dist The number of grid spaces the explosion spans in every direction */
	void createExplosion(int x, int y, int dist);
	
	
signals:
	/** Tells the MainWindow object to increase the score.
	 * @param amount The amount to increase the score by */
	void incrementScore(int amount);
	
	/** Tells the MainWindow object that the player has died, and that the game should end. */
	void gameOver();

		
protected:
	/** Creates randomized terrain within the game's grid out of destructible and indestructible walls. */
	void generateTerrain();
	
	/** Spawns an object at a random location in the game grid.
	 * @param type The type of thing to spawn (Alien, Powerup, or Health) */
	void spawnThing(QString type);


private:
	// Gameplay variables
	int height;				/**< The height of the game window */
	int width;				/**< The width of the game window */
	int gameTimer;			/**< The current time in seconds since the game has started */
	int gameCounter;		/**< Produces game-related actions (i.e. increases gameSpeed) */
	float gameSpeed;		/**< The current game speed. Initialized to 1, increases exponentially with regards to the gameTimer */
	int collisionCounter;	/**< Produces collision-related actions (i.e. checks collisions) */
	int mineCounter;		/**< Limits the number of mines a player can drop at once */
	int enemyCounter;		/**< Produces enemy-related actions (i.e. spawns enemies) */
	int powerupCounter;		/**< Produces powerup-related actions (i.e. spawns Missile powerups) */
	int powerupSpawnTime;	/**< Used to randomize the time between Missile powerup spawns */
	int numPowerups;		/**< Used to limit the number of Missile powerups in the game at one time to 3 */
	int healthCounter;		/**< Produces Health powerup-related actions (i.e. spawns Health powerups) */
	int numHealths;			/**< Used to limit the number of Health powerups in the game at one time to 2 */
	bool gameInProgress;	/**< Whether or not a game is currently in progress */
	Marine* marine;			/**< The player */
	
	// Missile display
	QGraphicsSimpleTextItem* missileDisplay;
	
	// This object's parent
	QWidget* parent;	/**< This object's parent. Should be of type MainWindow */
	
	// The Qt scene and view used to visualize gameplay
	QGraphicsView* view;	/**< The QGraphicsView used to display a QGraphicsScene */
	QGraphicsScene* scene;	/**< The QGraphicsScene used to visualize gameplay */
	
	// All textures and sprites used in the game
	QPixmap* backgroundPix;			/**< The background texture */
	QBrush* backgroundBrush;		/**< The brush used to paint the background in the scene */
	
	QPixmap* wallSpr;				/**< The indestructible Wall sprite */
	QPixmap* wallBrokenSpr;			/**< The destructible DWall sprite */
	
	QPixmap** spiderPackage;		/**< The array holding the Mine animation */
	QPixmap* spiderMineSpr;			/**< The Mine sprite (flashing on) */
	QPixmap* spiderMine_OffSpr;		/**< The Mine sprite (flashing off) */
	
	QPixmap* missileSpr;			/**< The Missile sprite */
	
	QPixmap* powerupSpr;			/**< The missile Powerup sprite */
	
	QPixmap* healthPickupSpr;		/**< The Health sprite */
	
	QPixmap** marinePackage;		/**< The array holding the Marine animation */
	QPixmap* marineSpr_up;			/**< The upwards-facing Marine */
	QPixmap* marineSpr_down;		/**< The downwards-facing Marine */
	QPixmap* marineSpr_left;		/**< The leftwards-facing Marine */
	QPixmap* marineSpr_right;		/**< The rightwards-facing Marine */
	
	QPixmap** zerglingPackage;		/**< The array holding the Alien animation */
	QPixmap* zerglingSpr_up;		/**< The upwards-facing Alien */
	QPixmap* zerglingSpr_down;		/**< The downwards-facing Alien*/
	QPixmap* zerglingSpr_left;		/**< The leftwards-facing Alien */
	QPixmap* zerglingSpr_right;		/**< The rightwards-facing Alien */
	
	QPixmap** explosionPackage;		/**< The array holding the Explosion animation */
	QPixmap* explosionSpr_1;		/**< Explosion animation part 1 */
	QPixmap* explosionSpr_2;		/**< Explosion animation part 2 */
	QPixmap* explosionSpr_3;		/**< Explosion animation part 3 */
	QPixmap* explosionSpr_4;		/**< Explosion animation part 4*/
	QPixmap* explosionSpr_5;		/**< Explosion animation part 5 */
	QPixmap* explosionSpr_6;		/**< Explosion animation part 6 */
	
	QPixmap** livesPackage;			/**< The array holding the sprites used to represent the player's current lives */
	QPixmap* hpSpr_0;				/**< The sprite representing the lives display outline */
	QGraphicsPixmapItem* hpBar;		/**< The graphical item for the lives display outline */
	QGraphicsPixmapItem* hpItem;	/**< The graphical item displaying the player's current lives */
	QPixmap* hpSpr_1;				/**< Player has 1 life left */	
	QPixmap* hpSpr_2;				/**< Player has 2 lives left */
	QPixmap* hpSpr_3;				/**< Player has 3 lives left */
	
	// The game's timer
	QTimer* timer;	/**< The timer used to create all actions in the game, including animation, movement, etc. */
	
	// Ways to keep track of objects in the scene
	std::vector<GameObject*>* grid;			/**< The abstract representation of an 18x18 grid with regards to the placement of in-game GameObjects */
	std::list<GameObject*>* gameObjects;	/**< The list of all in-game GameObjects */
};

#endif
