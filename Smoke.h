#pragma once
#ifndef __SMOKE_H
#define __SMOKE_H
#include <math.h>

class Smoke
{
private:
	double cx, cy, cz;

public:
	Smoke(double i);
	void setLocation(double x, double y, double z, int chimney);
	double getX();
	double getY();
	double getZ();
};

#endif // !__SMOKE_H
