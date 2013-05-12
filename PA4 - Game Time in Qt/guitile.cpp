#include "guitile.h"

// ----------------------- GUITILE() -----------------------
GUITile::GUITile(int val, double nx, double ny, double w, double h) : QGraphicsRectItem(nx, ny, w, h) {
	// Initialize this GUITile's private data members
	value_ = val;
	x_ = nx;
	y_ = ny;
	w_ = w;
	h_ = h;
	targetX = 0;
	targetY = 0;
	
	// Make tiles look nice
	if (value_ != 0) {	// For normal tiles (value is not 0)
		QString qStr = QString::number(value_);
		face = new QGraphicsSimpleTextItem(qStr, this);
		QBrush whiteBrush(Qt::white);
		setBrush(whiteBrush);
		QPen outline(Qt::SolidLine);
		outline.setWidth(2);
		setPen(outline);
	} else {			// For the blank tile (value is 0)
		face = new QGraphicsSimpleTextItem(" ", this);
		setPen(Qt::NoPen);
	}
	QFont font("Helvetica", 20, 3, false);
	face->setFont(font);
	
	// Center text on tile based on the number of digits in the value
	if ((int)(log10(value_)) == 0) {
		face->setX(x_ + w_/2 - 7);
		face->setY(y_ + h_/2 - 15);
	} else {
		face->setX(x_ + w_/2 - 15);
		face->setY(y_ + h_/2 - 15);
	}
	
	// Connect timer to this object's move function
	isMoving = false;
	timer.setInterval(5);
	connect(&timer, SIGNAL(timeout()), this, SLOT(moveTileAnimate()));
}


// ----------------------- ~GUITILE() -----------------------
GUITile::~GUITile() {
	delete face;
}


// ----------------------- GETVAL() -----------------------
int GUITile::getVal() {
	return value_;
}


// ----------------------- MOVETILE() -----------------------
void GUITile::moveTile(qreal nx, qreal ny) {	
	// Move rect to new location	
	QRectF r(rect());
	r.moveTo(nx, ny);
	setRect(r);
	x_ = nx;
	y_ = ny;
	
	
	// Center text on tile based on the number of digits in the value
	if ((int)(log10(value_)) == 0) {
		face->setX(x_ + w_/2 - 7);
		face->setY(y_ + h_/2 - 15);
	} else {
		face->setX(x_ + w_/2 - 15);
		face->setY(y_ + h_/2 - 15);
	}
}


// ----------------------- SETTARGETANDMOVE() -----------------------
void GUITile::setTargetAndMove(qreal nx, qreal ny) {
	if (!isMoving) {
		targetX = nx;
		targetY = ny;
		timer.start();
		isMoving = true;
	}
}


// ----------------------- GETX() -----------------------
qreal GUITile::getX() { 
	return x_;
}


// ----------------------- GETY() -----------------------
qreal GUITile::getY() {
	return y_;
}


// ----------------------- MOVETILEANIMATE() -----------------------
void GUITile::moveTileAnimate() {
	// If at its target, stop the animation timer and tell the MainWindow that tile is done moving
	if (x_ == targetX && y_ == targetY) {
		timer.stop();
		isMoving = false;
		emit doneMoving();
		return;
	}
	
	// Change x or y by one pixel towards target coordinate
	if (targetX > x_) {
		x_++;
	} else if (targetX < x_) {
		x_--;
	}
	if (targetY > y_) {
		y_++;
	} else if (targetY < y_) {
		y_--;
	}
	
	// Move rect to new location
	QRectF r(rect());
	r.moveTo(x_, y_);
	setRect(r);
	
	// Center text on tile based on the number of digits in the value
	if ((int)(log10(value_)) == 0) {
		face->setX(x_ + w_/2 - 7);
		face->setY(y_ + h_/2 - 15);
	} else {
		face->setX(x_ + w_/2 - 15);
		face->setY(y_ + h_/2 - 15);
	}
}


// ----------------------- MOUSEPRESSEVENT() -----------------------
void GUITile::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (event->button() == Qt::LeftButton) emit tilePressed(value_);
}
