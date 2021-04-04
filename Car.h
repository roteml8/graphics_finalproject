#pragma once
#include "Ground.h"

class Car
{
private:
	double red, green, blue;
	double cx, cy,cz; // center in world coordinates
	double dirx, diry, dirz;
	double speed;
public:
	Car(double r, double g, double b, double x, double y, double z, double dx, double dy, double dz, double speed);
	void DrawTyer(int n, double outer, double inner, double r, double g, double b, int jump);
	void DrawCylinder3(int n, double r, double g, double b);
	void DrawWheel(double offset);
	void Draw(double offset);
	void Move(/*double heights[ROWS][COLUMNS]*/);
	void SetSpeed(double s);
	double GetCx();
	double GetCy();
	double GetCz();
	double GetDirx();
	double GetDiry();
	double GetDirz();

};

