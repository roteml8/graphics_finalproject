#include "train.h"

Train::Train(int num)
{
	this->numOfRailroadCars = num;
	this->locomotiveCoordinate = 0;
	this->speed = 0.5;
	this->wheelRotate = 0;
}

double Train::getLocomotiveCoordinate()
{
	return this->locomotiveCoordinate;
}

void Train::move()
{
	this->locomotiveCoordinate += this->speed;
	if (this->locomotiveCoordinate > 195)
		this->locomotiveCoordinate = -95;

	this->wheelRotate += 0.4;
	if (this->wheelRotate >= 2 * PI)
		this->wheelRotate = 0;
}

void Train::draw()
{
	this->drawLocomotive();

	for (int i = 0; i < this->numOfRailroadCars; i++)
		this->drawRailroadCar(i);
}

void Train::drawLocomotive()
{
	this->drawPanel(1, this->locomotiveCoordinate, this->locomotiveCoordinate -8, 2.55, 2.55, -55.75, -56.75, 0.15, 0.15, 0.15, -10);
	this->drawChassis(1, this->locomotiveCoordinate, this->locomotiveCoordinate - 8, 2.55, 2.55, -55.75, -56.75, 0.85, 0.85, 0.85, 1);
	
	this->drawPanel(2, this->locomotiveCoordinate, this->locomotiveCoordinate, 2.55, 3, -55.75, -56.75, 0.15, 0.15, 0.15, -10);
	this->drawChassis(2, this->locomotiveCoordinate, this->locomotiveCoordinate, 2.55, 3, -55.75, -56.75, 0.85, 0.85, 0.85, 1);
	
	this->drawPanel(2, this->locomotiveCoordinate - 8, this->locomotiveCoordinate - 8, 2.55, 3, -55.75, -56.75, 0.15, 0.15, 0.15, -10);
	this->drawChassis(2, this->locomotiveCoordinate - 8, this->locomotiveCoordinate - 8, 2.55, 3, -55.75, -56.75, 0.85, 0.85, 0.85, 1);

	this->drawPanel(1, this->locomotiveCoordinate, this->locomotiveCoordinate - 8, 3, 3, -55.75, -56.75, 0.15, 0.15, 0.15, -10);
	this->drawChassis(1, this->locomotiveCoordinate, this->locomotiveCoordinate - 8, 3, 3, -55.75, -56.75, 0.85, 0.85, 0.85, 1);

	this->drawPanel(3, this->locomotiveCoordinate, this->locomotiveCoordinate - 8, 2.55, 3, -56.75, -56.75, 0.15, 0.15, 0.15, -10);
	this->drawChassis(3, this->locomotiveCoordinate, this->locomotiveCoordinate - 8, 2.55, 3, -56.75, -56.75, 0.85, 0.85, 0.85, 1);

	this->drawPanel(3, this->locomotiveCoordinate, this->locomotiveCoordinate - 8, 2.55, 3, -55.75, -55.75, 0.15, 0.15, 0.15, -10);
	this->drawChassis(3, this->locomotiveCoordinate, this->locomotiveCoordinate - 8, 2.55, 3, -55.75, -55.75, 0.85, 0.85, 0.85, 1);

	glColor3d(0.25, 0.25, 0.25);
	double alpha, teta = 2 * PI / 12;
	for (alpha = 0 ; alpha <= 2 * PI ; alpha += teta)
	{
		glBegin(GL_POLYGON);
		glVertex3d(this->locomotiveCoordinate - 1, 3.5 + 0.6 * sin(alpha), -56.25 + 0.6 * cos(alpha));
		glVertex3d(this->locomotiveCoordinate - 1, 3.5 + 0.6 * sin(alpha + teta), -56.25 + 0.6 * cos(alpha + teta));
		glVertex3d(this->locomotiveCoordinate - 5, 3.5 + 0.6 * sin(alpha + teta), -56.25 + 0.6 * cos(alpha + teta));
		glVertex3d(this->locomotiveCoordinate - 5, 3.5 + 0.6 * sin(alpha), -56.25 + 0.6 * cos(alpha));
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3d(this->locomotiveCoordinate - 1, 3.5, -56.25);
		glVertex3d(this->locomotiveCoordinate - 1, 3.5 + 0.6 * sin(alpha), -56.25 + 0.6 * cos(alpha));
		glVertex3d(this->locomotiveCoordinate - 1, 3.5 + 0.6 * sin(alpha + teta), -56.25 + 0.6 * cos(alpha + teta));
		glEnd();
	}

	glBegin(GL_LINES);
	glColor3d(0.85, 0.85, 0.85);
	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		glVertex3d(this->locomotiveCoordinate - 1, 3.5 + 0.6 * sin(alpha), -56.25 + 0.6 * cos(alpha));
		glVertex3d(this->locomotiveCoordinate - 1, 3.5 + 0.6 * sin(alpha + teta), -56.25 + 0.6 * cos(alpha + teta));
	}
	glEnd();

	this->drawChimney();

	this->drawPanel(2, this->locomotiveCoordinate - 5, this->locomotiveCoordinate - 5, 3, 4.5, -55.75, -56.75, 0.3, 0.3, 0.3, -10);
	this->drawChassis(2, this->locomotiveCoordinate - 5, this->locomotiveCoordinate - 5, 3, 4.5, -55.75, -56.75, 0.75, 0.75, 0.75, 1);

	this->drawPanel(3, this->locomotiveCoordinate - 5, this->locomotiveCoordinate - 8, 3, 4.5, -55.75, -55.75, 0.3, 0.3, 0.3, -10);
	this->drawChassis(3, this->locomotiveCoordinate - 5, this->locomotiveCoordinate - 8, 3, 4.5, -55.75, -55.75, 0.75, 0.75, 0.75, 1);

	this->drawPanel(3, this->locomotiveCoordinate - 5, this->locomotiveCoordinate - 8, 3, 4.5, -56.75, -56.75, 0.3, 0.3, 0.3, -10);
	this->drawChassis(3, this->locomotiveCoordinate - 5, this->locomotiveCoordinate - 8, 3, 4.5, -56.75, -56.75, 0.75, 0.75, 0.75, 1);

	this->drawPanel(2, this->locomotiveCoordinate - 8, this->locomotiveCoordinate - 8, 3, 5.5, -55.75, -56.75, 0.3, 0.3, 0.3, -10);
	this->drawChassis(2, this->locomotiveCoordinate - 8, this->locomotiveCoordinate - 8, 3, 5.5, -55.75, -56.75, 0.75, 0.75, 0.75, 1);

	this->drawPanel(1, this->locomotiveCoordinate - 5, this->locomotiveCoordinate - 8, 5.5, 5.5, -55.75, -56.75, 0.3, 0.3, 0.3, -10);
	this->drawChassis(1, this->locomotiveCoordinate - 5, this->locomotiveCoordinate - 8, 5.5, 5.5, -55.75, -56.75, 0.75, 0.75, 0.75, 1);

	this->drawLocomotiveWindows();
	this->drawWheel(0, true); 
}

void Train::drawRailroadCar(int i)
{
	this->drawPanel(1, this->locomotiveCoordinate - 9 * ((double)i + 1), this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, 2.55, 2.55, - 55.75, -56.75, 0.2, 0, 0.5, -10);
	this->drawPanel(1, this->locomotiveCoordinate - 9 * ((double)i + 1), this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, 4.95, 4.95, -55.75, -56.75, 0.5, 0.3, 0.8, -10);

	this->drawPanel(2, this->locomotiveCoordinate - 9 * ((double)i + 1), this->locomotiveCoordinate - 9 * ((double)i + 1), 2.55, 4.95, -55.75, -56.75, 0.2, 0, 0.5, 0.3);
	this->drawPanel(2, this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, 2.55, 4.95, -55.75, -56.75, 0.2, 0, 0.5, 0.3);

	this->drawPanel(3, this->locomotiveCoordinate - 9 * ((double)i + 1), this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, 2.55, 3.35, -55.75, -55.75, 0.2, 0, 0.5, 0.1);
	this->drawPanel(3, this->locomotiveCoordinate - 9 * ((double)i + 1), this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, 4.15, 4.95, -55.75, -55.75, 0.4, 0.2, 0.7, 0.1);

	this->drawPanel(3, this->locomotiveCoordinate - 9 * ((double)i + 1), this->locomotiveCoordinate - 9 * ((double)i + 1) - 1, 3.35, 4.15, -55.75, -55.75, 0.3, 0.1, 0.6, 0.1);
	this->drawPanel(3, this->locomotiveCoordinate - 9 * ((double)i + 1) - 7, this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, 3.35, 4.15, -55.75, -55.75, 0.3, 0.1, 0.6, 0.1);

	this->drawPanel(3, this->locomotiveCoordinate - 9 * ((double)i + 1), this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, 2.55, 3.35, -56.75, -56.75, 0.2, 0, 0.5, 0.1);
	this->drawPanel(3, this->locomotiveCoordinate - 9 * ((double)i + 1), this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, 4.15, 4.95, -56.75, -56.75, 0.4, 0.2, 0.7, 0.1);

	this->drawPanel(3, this->locomotiveCoordinate - 9 * ((double)i + 1), this->locomotiveCoordinate - 9 * ((double)i + 1) - 1, 3.35, 4.15, -56.75, -56.75, 0.3, 0.1, 0.6, 0.1);
	this->drawPanel(3, this->locomotiveCoordinate - 9 * ((double)i + 1) - 7, this->locomotiveCoordinate - 9 * ((double)i + 1) - 8, 3.35, 4.15, -56.75, -56.75, 0.3, 0.1, 0.6, 0.1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0, 0.3, 0.6, 0.7);
	glBegin(GL_POLYGON);
	glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) - 1, 3.35, -55.75);
	glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) - 1, 4.15, -55.75);
	glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) - 7, 4.15, -55.75);
	glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) - 7, 3.35, -55.75);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) - 1, 3.35, -56.75);
	glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) - 1, 4.15, -56.75);
	glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) - 7, 4.15, -56.75);
	glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) - 7, 3.35, -56.75);
	glEnd();
	glDisable(GL_BLEND);

	glColor3d(0.33, 0.33, 0.33);
	double alpha, teta = 2 * PI / 12;
	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		glBegin(GL_POLYGON);
		glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) + 1, 3 + 0.1 * sin(alpha), -56.6 + 0.1 * cos(alpha));
		glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) + 1, 3 + 0.1 * sin(alpha + teta), -56.6 + 0.1 * cos(alpha + teta));
		glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1), 3 + 0.1 * sin(alpha + teta), -56.6 + 0.1 * cos(alpha + teta));
		glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1), 3 + 0.1 * sin(alpha), -56.6 + 0.1 * cos(alpha));
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) + 1, 3 + 0.1 * sin(alpha), -56 + 0.1 * cos(alpha));
		glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1) + 1, 3 + 0.1 * sin(alpha + teta), -56 + 0.1 * cos(alpha + teta));
		glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1), 3 + 0.1 * sin(alpha + teta), -56 + 0.1 * cos(alpha + teta));
		glVertex3d(this->locomotiveCoordinate - 9 * ((double)i + 1), 3 + 0.1 * sin(alpha), -56 + 0.1 * cos(alpha));
		glEnd();
	}

	this->drawWheel(-4.5 * (i+1), false);
}

void Train::drawLocomotiveWindows()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0.0, 0.3, 0.6, 0.5);
	
	glBegin(GL_POLYGON);
	glVertex3d(this->locomotiveCoordinate - 5, 4.5, -55.75);
	glVertex3d(this->locomotiveCoordinate - 5, 4.5, -56.75);
	glVertex3d(this->locomotiveCoordinate - 5, 5.5, -56.75);
	glVertex3d(this->locomotiveCoordinate - 5, 5.5, -55.75);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(this->locomotiveCoordinate - 5, 4.5, -55.75);
	glVertex3d(this->locomotiveCoordinate - 8, 4.5, -55.75);
	glVertex3d(this->locomotiveCoordinate - 8, 5.5, -55.75);
	glVertex3d(this->locomotiveCoordinate - 5, 5.5, -55.75);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(this->locomotiveCoordinate - 5, 4.5, -56.75);
	glVertex3d(this->locomotiveCoordinate - 8, 4.5, -56.75);
	glVertex3d(this->locomotiveCoordinate - 8, 5.5, -56.75);
	glVertex3d(this->locomotiveCoordinate - 5, 5.5, -56.75);
	glEnd();

	glDisable(GL_BLEND);

	glColor3d(0.75, 0.75, 0.75);
	glBegin(GL_LINES);
	glVertex3d(this->locomotiveCoordinate - 5 , 4.5, -56.75);
	glVertex3d(this->locomotiveCoordinate - 5, 5.5, -56.75);

	glVertex3d(this->locomotiveCoordinate - 5, 4.5, -55.75);
	glVertex3d(this->locomotiveCoordinate - 5, 5.5, -55.75);
	glEnd();
}

void Train::drawChimney()
{
	double alpha, teta = 2 * PI / 12;
	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		glColor3d(0.4, 0.4, 0.4);
		glBegin(GL_POLYGON);
		glVertex3d(this->locomotiveCoordinate - 2 + 0.25 * cos(alpha), 3.5, -56.25 + 0.25 * sin(alpha));
		glVertex3d(this->locomotiveCoordinate - 2 + 0.25 * cos(alpha + teta), 3.5, -56.25 + 0.25 * sin(alpha + teta));
		glVertex3d(this->locomotiveCoordinate - 2 + 0.25 * cos(alpha + teta), 5.5, -56.25 + 0.25 * sin(alpha + teta));
		glVertex3d(this->locomotiveCoordinate - 2 + 0.25 * cos(alpha), 5.5, -56.25 + 0.25 * sin(alpha));
		glEnd();

		glColor3d(0.85, 0.85, 0.85);
		glBegin(GL_LINES);
		glVertex3d(this->locomotiveCoordinate - 2 + 0.25 * cos(alpha), 5.5, -56.25 + 0.25 * sin(alpha));
		glVertex3d(this->locomotiveCoordinate - 2 + 0.25 * cos(alpha + teta), 5.5, -56.25 + 0.25 * sin(alpha + teta));
		glEnd();
	}
}

void Train::drawWheel(double coordinate, bool isLocomotive)
{
	glColor3d(0.33, 0.19, 0);
	double alpha, teta = 2 * PI / 12;
	for (int x = - 1; x >= - 7; x-= 2)
	{
		for (alpha = 0; alpha <= 2 * PI; alpha += teta)
		{
			glBegin(GL_POLYGON);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha), 2.5 + 0.3 * sin(alpha), -56.61);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha), 2.5 + 0.3 * sin(alpha), -56.59);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha + teta), 2.5 + 0.3 * sin(alpha + teta), -56.59);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha + teta), 2.5 + 0.3 * sin(alpha + teta), -56.61);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x, 2.5, -56.61);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha), 2.5 + 0.3 * sin(alpha), -56.61);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha + teta), 2.5 + 0.3 * sin(alpha + teta), -56.61);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x, 2.5, -56.59);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha), 2.5 + 0.3 * sin(alpha), -56.59);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha + teta), 2.5 + 0.2 * sin(alpha + teta), -56.59);
			glEnd();
			/*******************/
			glBegin(GL_POLYGON);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha), 2.5 + 0.3 * sin(alpha), -55.91);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha), 2.5 + 0.3 * sin(alpha), -55.89);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha + teta), 2.5 + 0.3 * sin(alpha + teta), -55.89);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha + teta), 2.5 + 0.3 * sin(alpha + teta), -55.91);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x, 2.5, -55.91);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha), 2.5 + 0.3 * sin(alpha), -55.91);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha + teta), 2.5 + 0.3 * sin(alpha + teta), -55.91);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x, 2.5, -55.89);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha), 2.5 + 0.3 * sin(alpha), -55.89);
			glVertex3d(this->locomotiveCoordinate + 2 * coordinate + x + 0.3 * cos(alpha + teta), 2.5 + 0.3 * sin(alpha + teta), -55.89);
			glEnd();
		}
	}
	if (isLocomotive)
	{
		glColor3d(0.5, 0.5, 0.5);
		glLineWidth(7);
		glBegin(GL_LINES);

		glVertex3d(this->locomotiveCoordinate + coordinate - 1 + 0.2 * cos(this->wheelRotate), 2.5 + 0.2 * sin(this->wheelRotate), -56.62);
		glVertex3d(this->locomotiveCoordinate + coordinate - 7 + 0.2 * cos(this->wheelRotate), 2.5 + 0.2 * sin(this->wheelRotate), -56.62);

		glVertex3d(this->locomotiveCoordinate + coordinate - 1 + 0.2 * cos(-this->wheelRotate), 2.5 + 0.2 * sin(-this->wheelRotate), -55.88);
		glVertex3d(this->locomotiveCoordinate + coordinate - 7 + 0.2 * cos(-this->wheelRotate), 2.5 + 0.2 * sin(-this->wheelRotate), -55.88);

		glLineWidth(3);
		for(int x = -1; x >= -7; x -= 2)
		{
			glVertex3d(this->locomotiveCoordinate + coordinate - x - 8, 3, -56.62);
			glVertex3d(this->locomotiveCoordinate + coordinate - x - 8 + 0.2 * cos(this->wheelRotate), 2.5 + 0.2 * sin(this->wheelRotate), -56.62);

			glVertex3d(this->locomotiveCoordinate + coordinate - x - 8, 3, -55.88);
			glVertex3d(this->locomotiveCoordinate + coordinate - x - 8 + 0.2 * cos(-this->wheelRotate), 2.5 + 0.2 * sin(-this->wheelRotate), -55.88);
		}
		glEnd();
	}
}

void Train::drawPanel(int plain, double x1, double x2, double y1, double y2, double z1, double z2, double r, double g, double b, double shade)
{
	glColor3d(r, g, b);
	glBegin(GL_POLYGON);
	switch (plain)
	{
	case 1: // parallel to the ground
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y1, z2);
		glVertex3d(x2, y1, z2);
		glVertex3d(x2, y1, z1);
		break;
	case 2: // Perpendicular to the rail
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y1, z2);
		if (fabs(shade <= 1))
		{
			if (r + shade <= 1 && r + shade >= 0) r += shade;
			if (g + shade <= 1 && g + shade >= 0) g += shade;
			if (b + shade <= 1 && b + shade >= 0) b += shade;
			glColor3d(r, g, b);
		}
		glVertex3d(x1, y2, z2);
		glVertex3d(x1, y2, z1);
		break;
	case 3: // parallel to the rail
		glVertex3d(x1, y1, z1);
		glVertex3d(x2, y1, z1);
		//glVertex3d(x1, y2, z1);
		if (fabs(shade <= 1))
		{
			if (r + shade <= 1 && r + shade >= 0) r += shade;
			if (g + shade <= 1 && g + shade >= 0) g += shade;
			if (b + shade <= 1 && b + shade >= 0) b += shade;
			glColor3d(r, g, b);
		}
		glVertex3d(x2, y2, z1);
		glVertex3d(x1, y2, z1);
		break;
	default:
		break;
	}
	glEnd();
}

void Train::drawChassis(int plain, double x1, double x2, double y1, double y2, double z1, double z2, double r, double g, double b, double width)
{
	glColor3d(r, g, b);
	glLineWidth(width);
	glBegin(GL_LINES);
	

	switch (plain)
	{
	case 1: // parallel to the ground
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y1, z2);

		glVertex3d(x1, y1, z2);
		glVertex3d(x2, y1, z2);

		glVertex3d(x2, y1, z2);
		glVertex3d(x2, y1, z1);

		glVertex3d(x2, y1, z1);
		glVertex3d(x1, y1, z1);
		break;
	case 2: // Perpendicular to the rail
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y1, z2);

		glVertex3d(x1, y1, z2);
		glVertex3d(x1, y2, z2);

		glVertex3d(x1, y2, z2);
		glVertex3d(x1, y2, z1);

		glVertex3d(x1, y2, z1);
		glVertex3d(x1, y1, z1);
		break;
	case 3:
		glVertex3d(x1, y1, z1);
		glVertex3d(x2, y1, z1);

		glVertex3d(x2, y1, z1);
		glVertex3d(x2, y2, z1);

		glVertex3d(x2, y2, z1);
		glVertex3d(x1, y2, z1);

		glVertex3d(x1, y2, z1);
		glVertex3d(x1, y1, z1);
		break;
	default:
		break;
	}
	glEnd();
}