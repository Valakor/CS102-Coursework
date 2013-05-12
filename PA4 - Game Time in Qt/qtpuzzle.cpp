#include <QtGui/QApplication>
#include "mainwindow.h"

/** @mainpage CSCI 102 PA4 - Game Time!
 * @section purpose Purpose/Overview
 * This programming assignment is to demonstrate the use of action-based
 * programming using Qt. It is a simple 8-puzzle game (technically an 8 or 15 puzzle) with
 * animating tiles, randomized game boards, and the ability for the user to cheat and determine
 * the best solution using the A* algorithm and either a Manhattan or Out of Place Heuristic.
 */

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	
	w.show();
	
	return a.exec();
}
