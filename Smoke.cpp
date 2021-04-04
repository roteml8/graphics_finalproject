#include "Smoke.h"

Smoke::Smoke(double i)
{
	this->cx = 0;
	this->cy = 5.5;
	this->cz = 0;
}

void Smoke::setLocation(double x, double y, double z, int chimney)
{
	this->cx = x;
	this->cy = y;
	this->cz = z;
}

double Smoke::getX()
{
	return this->cx;
}
double Smoke::getY()
{
	return this->cy;
}
double Smoke::getZ()
{
	return this->cz;
}