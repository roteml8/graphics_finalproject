#include "Car.h"

Car::Car(double r, double g, double b, double x, double y, double z, double dx, double dy, double dz, double speed)
{
	red = r;
	green = g;
	blue = b;
	cx = x;
	cy = y;
	cz = z;
	dirx = dx;
	diry = dy;
	dirz = dz;
	this->speed = speed;
}

// kind of ring
void Car::DrawTyer(int n, double outer, double inner, double r, double g, double b, int jump)
{
	double alpha, teta = 2 * PI / n;
	double x, z;
	glColor3d(r, g, b);
	for (alpha = 0; alpha < 2 * PI; alpha += jump * teta)
	{
		glBegin(GL_POLYGON);
		x = outer * sin(alpha);
		z = outer * cos(alpha);
		glVertex3d(x, 0, z); // 1
		x = inner * sin(alpha);
		z = inner * cos(alpha);
		glVertex3d(x, 0, z); // 2
		x = inner * sin(alpha + teta);
		z = inner * cos(alpha + teta);
		glVertex3d(x, 0, z); // 3
		x = outer * sin(alpha + teta);
		z = outer * cos(alpha + teta);
		glVertex3d(x, 0, z); // 4
		glEnd();
	}
}

void Car::DrawCylinder3(int n, double r, double g, double b)
{
	double alpha, teta = 2 * PI / n;

	glColor3d(r, g, b);
	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		// defines one side

		glBegin(GL_POLYGON);
		glVertex3d(sin(alpha), 1, cos(alpha)); // vertex 1
		glVertex3d(sin(alpha + teta), 1, cos(alpha + teta)); // vertex 2
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta)); // vertex 3
		glVertex3d(sin(alpha), 0, cos(alpha)); // vertex 4
		glEnd();
	}
}

void Car::DrawWheel(double offset)
{
	glPushMatrix();
	glRotated(-5 * offset, 0, 1, 0);
	DrawCylinder3(50, 0.2, 0.2, 0.2);
	glPushMatrix();
	glScaled(0.7, 1, 0.7);
	DrawCylinder3(50, 0.2, 0.2, 0.2);
	glPopMatrix();

	DrawTyer(50, 1, 0.7, 0.4, 0.4, 0.4, 1);
	DrawTyer(20, 0.7, 0, 0.8, 0.8, 0.8, 2);
	glPushMatrix();
	glTranslated(0, 1, 0);
	DrawTyer(50, 1, 0.7, 0.4, 0.4, 0.4, 1);
	DrawTyer(20, 0.7, 0, 0.8, 0.8, 0.8, 2);
	glPopMatrix();
	glPopMatrix();

}

// compute the direction and update car center
void Car::Move(/*double heights[ROWS][COLUMNS]*/)
{
	int row = 0, col = 0;
	if (fabs(dirz) < 0.01 && fabs(dirx)>0.99) // if the direction is along X axis
	{
		// find column and row of cell in ground
		row = (int) (cz+ROWS/2);
		col = (int) (cx+COLUMNS/2);
		
		if (dirx > 0) // moving to the right
		{
			if (col >= /*COLUMNS - 1*/345) // if the car goes out of matrix return it back to the start
			{
				col = 0;
				cx = -COLUMNS / 2;
				cx += 100;
				if (heights[/*row*/40][/*col*/(int)cx + 100] > 0) cy = heights[/*row*/40][/*col*/(int)cx + 100];
				else cy = 1;
			}
			if (heights[/*row*/40][/*col*/(int)cx+100] > 0) diry = heights[row][/*col + 1*/(int)cx + 101] - heights[row][/*col*/(int)cx + 100];
			else diry = 0;
		}
		else // moving to the left
		{
			if (col < 0)
			{
				col = COLUMNS - 2;
				cx = COLUMNS / 2;
				if (heights[/*row*/40][col + 1] > 0) cy = heights[/*row*/40][col + 1];
				else cy = 1;
			}
			if (heights[/*row*/40][/*col + 1*/(int)cx + 101] > 0)
				diry = heights[/*row*/40][/*col*/(int)cx + 100] - heights[/*row*/40][/*col + 1*/(int)cx + 101];
			else
			{
				diry = 0;
				cy = 1;
			}
		}
	}
	// update center of a car
	cx += dirx * speed;
	cy += diry * speed;
	cz += dirz * speed;
	int tmp_col;
	tmp_col = (int)(cx + COLUMNS / 2);
	if (tmp_col != col && tmp_col < COLUMNS) // update cy
	{
		if (heights[row][tmp_col] > 0) cy = /*heights[row][tmp_col]*/2.5;
		else cy = 1;
	}
	

}

void Car::SetSpeed(double s)
{
	speed = s;
}

double Car::GetCx()
{
	return cx;
}

double Car::GetCy()
{
	return cy;
}

double Car::GetCz()
{
	return cz;
}

double Car::GetDirx()
{
	return dirx;
}

double Car::GetDiry()
{
	return diry;
}

double Car::GetDirz()
{
	return dirz;
}


void Car::Draw(double offset)
{
	double beta;
	glPushMatrix();
	glTranslated(cx, /*cy+0.2*/2.5, cz); // position the car in its center (we lift the car by 0.2 to put wheels on road)
	// only when the motion is along X axis
	beta = atan(diry); // in rad
	glRotated(beta * 180 / PI, 0, 0, 1);
	glScaled(0.05, 0.05, 0.05);

	glPushMatrix();
	glTranslated(5, 0, 2.5);
	glRotated(90, 1, 0, 0);
	DrawWheel(offset);
	glPopMatrix();

	glPushMatrix();
	glTranslated(5, 0, -3.5);
	glRotated(90, 1, 0, 0);
	DrawWheel(offset);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5, 0, 2.5);
	glRotated(90, 1, 0, 0);
	DrawWheel(offset);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5, 0, -3.5);
	glRotated(90, 1, 0, 0);
	DrawWheel(offset);
	glPopMatrix();

	// body

	glPushMatrix();
	glTranslated(0, 0.3, 0);
	glRotated(90, 0, 0, 1);
	glScaled(1, 1, 4);
	glRotated(45, 0, 1, 0);
	glTranslated(0, -7.5, 0);
	glScaled(1, 15, 1);
	DrawCylinder3(4, red, green, blue);
	glPopMatrix();

	// roof
	glPushMatrix();
	glTranslated(0, 2.5, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0, 1, 4);
	glRotated(45, 0, 1, 0);
	glTranslated(0, -5, 0);
	glScaled(1, 10, 1);
	DrawCylinder3(4, red * 0.8, green * 0.8, blue * 0.8);
	glPopMatrix();

	// connections
	glColor3d(0.8, 0.8, 0.8);
	glBegin(GL_LINES);
	// front right
	glVertex3d(5, 2.5, 2.7);
	glVertex3d(5.5, 1, 2.7);
	//front left
	glVertex3d(5, 2.5, -2.7);
	glVertex3d(5.5, 1, -2.7);
	// rear right
	glVertex3d(-5, 2.5, 2.7);
	glVertex3d(-5.5, 1, 2.7);
	//rear left
	glVertex3d(-5, 2.5, -2.7);
	glVertex3d(-5.5, 1, -2.7);
	glEnd();

	// windows
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0.6, 0.3, 0.0, 0.5);
	// right side
	glBegin(GL_POLYGON);
	glVertex3d(-5, 2.5, 2.7);
	glVertex3d(5, 2.5, 2.7);
	glVertex3d(5.5, 1, 2.7);
	glVertex3d(-5.5, 1, 2.7);
	glEnd();
	// left side
	glBegin(GL_POLYGON);
	glVertex3d(-5, 2.5, -2.7);
	glVertex3d(5, 2.5, -2.7);
	glVertex3d(5.5, 1, -2.7);
	glVertex3d(-5.5, 1, -2.7);
	glEnd();

	// front
	glBegin(GL_POLYGON);
	glVertex3d(5, 2.5, -2.7);
	glVertex3d(5, 2.5, 2.7);
	glVertex3d(5.5, 1, 2.7);
	glVertex3d(5.5, 1, -2.7);
	glEnd();
	// rear
	glBegin(GL_POLYGON);
	glVertex3d(-5, 2.5, -2.7);
	glVertex3d(-5, 2.5, 2.7);
	glVertex3d(-5.5, 1, 2.7);
	glVertex3d(-5.5, 1, -2.7);
	glEnd();

	glDisable(GL_BLEND);

	// front panel
	glColor3d(red * 0.8, green * 0.8, blue * 0.8);
	glBegin(GL_POLYGON);
	glVertex3d(7.5, 1.0, -2.9);
	glVertex3d(7.5, 1.0, 2.9);
	glVertex3d(7.5, -0.4, 2.9);
	glVertex3d(7.5, -0.4, -2.9);
	glEnd();

	// front lights
	glPushMatrix();
	glTranslated(7.5, 0.3, -2.2);
	glScaled(0.1, 0.3, 0.5);
	DrawCylinder3(20, 1, 1, 0.9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(7.5, 0.3, 2.2);
	glScaled(0.1, 0.3, 0.5);
	DrawCylinder3(20, 1, 1, 0.9);
	glPopMatrix();

	// rear panel
	glColor3d(red * 0.8, green * 0.8, blue * 0.8);
	glBegin(GL_POLYGON);
	glVertex3d(-7.5, 1.0, -2.9);
	glVertex3d(-7.5, 1.0, 2.9);
	glVertex3d(-7.5, -0.4, 2.9);
	glVertex3d(-7.5, -0.4, -2.9);
	glEnd();

	// front lights
	glPushMatrix();
	glTranslated(-7.5, 0.3, -2.2);
	glScaled(0.1, 0.3, 0.5);
	DrawCylinder3(20, 1, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-7.5, 0.3, 2.2);
	glScaled(0.1, 0.3, 0.5);
	DrawCylinder3(20, 1, 0, 0);
	glPopMatrix();
	glPopMatrix();


}
