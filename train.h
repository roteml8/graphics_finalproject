#pragma once
#include "Ground.h"

#ifndef __TRAIN_H
#define __TRAIN_H

class Train
{
private:
	double locomotiveCoordinate, speed, wheelRotate;
	int numOfRailroadCars;

public:
	Train(int num);
	double getLocomotiveCoordinate();
	void move();
	void draw();
	void drawLocomotive();
	void drawRailroadCar(int i);
	void drawLocomotiveWindows();
	void drawChimney();
	void drawWheel(double coordinate, bool isLocomotive);
	void drawPanel(int plain, double x1, double x2, double y1, double y2, double z1, double z2, double r, double g, double b, double shade);
	void drawChassis(int plain, double x1, double x2, double y1, double y2, double z1, double z2, double r, double g, double b, double width);
};

#endif // !__TRAIN_H
