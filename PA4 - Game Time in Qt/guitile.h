#ifndef GUITILE_H
#define GUITILE_H

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QObject>
#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QRectF>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>

#include <cmath>

/** Visual representation of a tile on screen. */

class GUITile : public QObject, public QGraphicsRectItem {
	Q_OBJECT
public:
	/** Constructor that must be used to declare a GUITile.
	 * @param val The value of the GUITile (the number on its face)
	 * @param nx The x coordinate of the upper left hand corner of the GUITile
	 * @param ny The y coordinate of the upper left hand corner of the GUITile
	 * @param w The width of the GUITile
	 * @param h The height of the GUITile */
	GUITile(int val, double nx, double ny, double w, double h);
	
	/** Default destructor. Deletes the face value object. */
	~GUITile();
	
	/** Gets the value on the face of the GUITile.
	 * @return The integer representation of the face value */
	int getVal();
	
	/** Snaps the GUITile to a new location.
	 * @param nx The new x coordinate for the GUITile
	 * @param ny The new y coordinate for the GUITile */
	void moveTile(qreal nx, qreal ny);
	
	/** Sets the target of the GUITile for an animated movement and begins the animation.
	 * @param nx The new x coordinate for the GUITile
	 * @param ny The new y coordinate for the GUITile */
	void setTargetAndMove(qreal nx, qreal ny);
	
	/** Gets the GUITile's current x coordinate
	 * @return A typdef'd double (qreal) representing the GUITile's x coordinate */
	qreal getX();
	
	/** Gets the GUITile's current y coordinate
	 * @return A typdef'd double (qreal) representing the GUITile's y coordinate */
	qreal getY();
	
	
public slots:
	/** Moves the tile one pixel towards its current target location. Used to animate
	 * a tile's movement.
	 * @pre The GUITile's internal animation timer must have been started */
	void moveTileAnimate();
	
	
signals:
	/** Signal emitted when this GUITile is clicked.
	 * @param val The value of the tile's face passed in the signal */
	void tilePressed(int val);
	
	/** Signal emitted when this GUITile is done animating towards its new location.
	 * Emitted in GUITile::moveTileAnimate(). */
	void doneMoving();


protected:
	/** Overloaded QGraphicsItem::mousePressEvent() that emits GUITile::myPressSignal(), telling
	 * the MainWindow which tile is being clicked on. */
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

	
private:
	int value_;						/**< The GUITile's face value displayed on screen */
	qreal x_;						/**< The GUITile's x coordinate in the scene */
	qreal y_;						/**< The GUITile's y coordinate in the scene */
	qreal w_;						/**< The GUITile's width */
	qreal h_;						/**< The GUITile's height */
	qreal targetX;					/**< The GUITile's target x coordinate for animation */
	qreal targetY;					/**< The GUITile's target y coordinate for animation */
	QGraphicsSimpleTextItem* face;	/**< The GUITile's Qt text item for displaying value_ */
	QTimer timer;					/**< The GUITile's internal animation timer */
	bool isMoving;					/**< Whether or not the GUITile is currently animating */
};

#endif
