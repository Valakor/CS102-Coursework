#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QtGui>

class GameWindow;

/** An enumeration defining different GameObject types */
enum TYPE {
	NONE,		/**< No type defined */
	IWALL,		/**< Indestructible Wall (Wall) */
	DWALL,		/**< Destructible Wall (DWall) */
	MARINE,		/**< Marine */
	MINE,		/**< Mine */
	MISSILE,	/**< Missile */
	EXPLOSION,	/**< Explosion */
	POWERUP,	/**< missile Powerup */
	ALIEN,		/**< Alien */
	HEALTH		/**< Health powerup */
};

/** An enumeration defininig different cardinal directions */
enum DIRECTION {
	UP,		/**< Negative y direction */
	DOWN,	/**< Positive y direction */
	LEFT,	/**< Negative x direction */
	RIGHT	/**< Positive x direction */
};


/** Base class for all objects in gameplay. */
class GameObject : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT

public:
	/** Constructor. Creates a GameObject at a location with a given sprite.
	 * @param nx The x coordinate of the object in the scene
	 * @param ny The y coordinate of the object in the scene
	 * @param pix The sprite used to visualize the GameObject
	 * @param indx The index of the sprite in the game grid
	 * @param prnt The GameObject's parent (should be of type GameWindow)
	 * @param GSpd The game speed of the object that determines how fast it acts */
	GameObject(int nx, int ny, QPixmap* pix, int indx, GameWindow* prnt = 0, float GSpd = 1);
	
	/** Returns what type of GameObject this is
	 * @return The TYPE enumeration of this GameObject */
	virtual TYPE getType() { return type; };
	
	/** Tells the GameObject to move by a given amount in the scene by setting its target
	 * location. Must be re-implemented in derived classes.
	 * @param dx The amount to move in the x direction
	 * @param dy The amount to move in the y direction */
	virtual void move(int dx, int dy) = 0;
	
	/** Whether or not the GameObject is currently moving in the scene.
	 * @return True if moving, false otherwise */
	virtual bool moving() { return canMove; };
	
	/** Returns the location of this GameObject in the game's grid.
	 * @return The integer representation of this GameObject's location (between 0 and 324 if a collidable object, -1 otherwise) */
	virtual int getIndex() { return index; };
	
	/** Sets the location of this GameObject in the game's grid.
	 * @param indx The new index location */
	virtual void setIndex(int indx) { index = indx; };
	
	/** Sets this GameObject's game speed, which is used to change how fast it acts (moves)
	 * @param nSpeed This GameObject's new game speed */
	virtual void setGameSpeed(float nSpeed);
	
	
public slots:
	/** Called as much as necessary to cause this GameObject to take action. Must be
	 * re-implemented in derived classes, as most objects will have different behavior. */
	virtual void handleTimer() = 0;
	
	
protected:
	GameWindow* parent;	/**< This GameObjects's parent. Should be of type GameWindow */
	
	int counter;		/**< A generic counter that can be utilized in derived classes to create action */
	float gameSpeed;	/**< Modifies the GameObject's speed. A higher value makes the GameObject act faster */
	
	/** Moves the GameObject according to where GameObject::move(int, int) has determined, or in some other
	 * way defined by the derived class. Must be re-implemented by derived classes. */
	virtual void move() = 0;
	
	QPixmap* sprite;	/**< The sprite of this GameObject */
	
	int index;	/**< The current location of this GameObject in the game's grid vector */
	
	bool canMove;	/**< If false, the GameObject should calculate its next move. If true, the GameObject is moving */
	int tx;			/**< The target x coordinate used to move the GameObject to a new location */
	int ty;			/**< The target y coordinate used to move the GameObject to a new location */
	int vx;			/**< The horizontal velocity of the GameObject */
	int vy;			/**< The vertical velocity of the GameObject */
	int speed;		/**< The GameObject acts based upon this base value that can be modified by gameSpeed */
	
	TYPE type;	/**< The TYPE enumeration of this GameObject. Set to NONE for a base GameObject */
};

#endif
