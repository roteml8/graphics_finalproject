#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include "train.h"
#include "Smoke.h"

const int W = 600;
const int H = 600;
const int TW = 512;
const int TH = 512;

// texture definitions
unsigned char tx0[TH][TW][3]; // 3 stands for rgb

// locomotion (ego-motion)
double eyex = -15, eyey = 10, eyez = -75;

double yaw = 0 * PI / 2, pitch = 0, roll;
double speed = 0, angularSpeed = 0;
double dir[3] = { sin(yaw),sin(pitch),cos(yaw) };

double offset = 0, smoke = 0;
Train* train;
Smoke** smokes;
double smoke_offset[30] = {0};

bool IsRailroadTie(int i, int j)
{
	for (int gap = 0; gap < TW; gap += 32 * 4)
		if (i <= gap + 32 && i >= gap)
			if (j >= 32 * 3 && j <= TW - 32 * 3)
				return true;
	return false;
}

void SetTexture(int kind)
{
	int i, j, delta, k, shade = -96;
	switch (kind)
	{
	case 1: // rail
		for (i = 0; i < TH; i++)
			for (j = 0; j < TW; j++)
			{
				if (j >= TW / 4 && j <= TW / 4 + 16 ||
					j <= 3 * TW / 4 && j >= 3 * TW / 4 - 16)
				{
					tx0[j][i][0] = 192 - fabs(shade);
					tx0[j][i][1] = 192 - fabs(shade);
					tx0[j][i][2] = 192 - fabs(shade);
					shade += 12;
					if (shade > 96)
						shade = -96;
				}
				else if (IsRailroadTie(i, j))
				{
					tx0[j][i][0] = 200;
					tx0[j][i][1] = 200;
					tx0[j][i][2] = 200;
				}
				else
				{
					int gap = rand() % 70;
					tx0[j][i][0] = 255 - gap;
					tx0[j][i][1] = 140;
					tx0[j][i][2] = gap;
				}
			}
		break;
	}
}

void PrepareGround(int startx, int startz, int endx, int endz, int height)
{
	for (int i = startz; i <= endz; i++)
		for (int j = startx; j <= endx; j++)
			heights[i][j] = height;
}


void init()
{
	srand(time(0));
	glClearColor(0.0, 0.6, 0.8, 0.0);// color of window background
	glEnable(GL_DEPTH_TEST);

	ReadInitialCoordinates();
	TerrainChassis();
	SmoothTerrain();

	PrepareRoad();

	glEnable(GL_NORMALIZE);// needs for lighting to normalize the vectors

	// Textures definitions
	SetTexture(1); // rail
	glBindTexture(GL_TEXTURE_2D, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TW, TH, 0, GL_RGB, GL_UNSIGNED_BYTE, tx0);

	train = new Train(3);
	smokes = new Smoke * [30];
		
	for (int i = 0; i < 30; i++)
	{
		smokes[i] = new Smoke(i);
		smoke_offset[i] = i * 5.0;
	}
}

void DrawCylinder(int n)
{
	double alpha, teta = 2 * PI / n;

	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		// defines one side

		glBegin(GL_POLYGON);
		glColor3d(fabs(sin(alpha)), (1 + cos(alpha)) / 2, 1 - fabs(sin(alpha + PI / 2)));
		glVertex3d(sin(alpha), 1, cos(alpha)); // vertex 1
		glVertex3d(sin(alpha + teta), 1, cos(alpha + teta)); // vertex 2
		glColor3d(fabs(sin(alpha)) / 2, (1 + cos(alpha)) / 4, 1 - fabs(sin(alpha + PI / 2)));
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta)); // vertex 3
		glVertex3d(sin(alpha), 0, cos(alpha)); // vertex 4
		glEnd();
	}
}

void drawTree(int xc, int yc, int zc, int height, double r, double g, double b)
{
	double alpha, teta = 2 * PI / 100;
	// trunk
	glColor3d(0.396, 0.263, 0.129);
	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		// defines one side

		glBegin(GL_POLYGON);
		glVertex3d(xc + sin(alpha), yc + height, zc + cos(alpha)); // vertex 1
		glVertex3d(xc + sin(alpha + teta), yc + height, zc + cos(alpha + teta)); // vertex 2
		glVertex3d(xc + sin(alpha + teta), yc, zc + cos(alpha + teta)); // vertex 3
		glVertex3d(xc + sin(alpha), yc, zc + cos(alpha)); // vertex 4
		glEnd();
	}

	// leaves
	glColor3d(r, g, b);
	int line;
	int lastYC = yc + height;
	for (line = 1; line <= 4; line++)
	{
		for (alpha = 0; alpha <= 2 * PI; alpha += teta)
		{
			// defines one side

			glBegin(GL_POLYGON);
			glVertex3d(xc - line + sin(alpha), lastYC + 1, zc + cos(alpha)); // vertex 1
			glVertex3d(xc + line + sin(alpha + teta), lastYC, zc + cos(alpha + teta)); // vertex 2
			glVertex3d(xc + line + sin(alpha + teta), lastYC + 1, zc + cos(alpha + teta)); // vertex 3
			glVertex3d(xc - line + sin(alpha), lastYC, zc + cos(alpha)); // vertex 4
			glEnd();
		}
		lastYC++;
	}
	for (line = 3; line >= 1; line--)
	{
		for (alpha = 0; alpha <= 2 * PI; alpha += teta)
		{
			// defines one side

			glBegin(GL_POLYGON);
			glVertex3d(xc - line + sin(alpha), lastYC + 1, zc + cos(alpha)); // vertex 1
			glVertex3d(xc + line + sin(alpha + teta), lastYC, zc + cos(alpha + teta)); // vertex 2
			glVertex3d(xc + line + sin(alpha + teta), lastYC + 1, zc + cos(alpha + teta)); // vertex 3
			glVertex3d(xc - line + sin(alpha), lastYC, zc + cos(alpha)); // vertex 4
			glEnd();
		}
		lastYC++;
	}

}

void DrawTexCylinder2(int n, int tnum, int num_repeat, double tr, double br, double tpart, double bpart)
{
	double alpha, teta = 2 * PI / n;
	double part = num_repeat / (double)n;
	int counter;

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, tnum); // wall with window texture
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	for (alpha = 0, counter = 0; alpha <= 2 * PI; alpha += teta, counter++)
	{
		// defines one side

		glBegin(GL_POLYGON);
		//		glColor3d(0.3 + 0.7 * fabs(sin(alpha)), 0.3 + 0.7 * fabs(sin(alpha)), 0.3 + 0.7 * fabs(sin(alpha)));
		glTexCoord2d(counter * part, tpart);    glVertex3d(tr * sin(alpha), 1, tr * cos(alpha)); // vertex 1
		glTexCoord2d((counter + 1) * part, tpart);    		glVertex3d(tr * sin(alpha + teta), 1, tr * cos(alpha + teta)); // vertex 2
		glTexCoord2d((counter + 1) * part, bpart);    		glVertex3d(br * sin(alpha + teta), 0, br * cos(alpha + teta)); // vertex 3
		glTexCoord2d(counter * part, bpart);    		glVertex3d(br * sin(alpha), 0, br * cos(alpha)); // vertex 4
		glEnd();
	}

	//glDisable(GL_TEXTURE_2D);

}

void DrawTexSphere(int n, int sl, int tnum, int num_rep, int vert_rep)
{
	double beta, gamma = PI / sl;
	int counter;
	double part = vert_rep / (double)sl;

	for (beta = -PI / 2, counter = 0; beta <= PI / 2; beta += gamma, counter++)
	{
		glPushMatrix();
		glTranslated(0, sin(beta) / 4, 0);
		glScaled(1, sin(beta + gamma) - sin(beta), 1);
		DrawTexCylinder2(n, tnum, num_rep, cos(beta + gamma) / 4, cos(beta) / 4, (counter + 1) * part, counter * part);
		glPopMatrix();
	}
}

void displayPassenger()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clean frame buffer and depth buffer
	glViewport(0, 0, W, H);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // loads the Identity matrix to the Projection Matrix
	// define the camera model
	glFrustum(-1, 1, -1, 1, 1, 300);
	// define the viewing parameters

	yaw = 0;
	eyex = train->getLocomotiveCoordinate() - 13;
	eyey = 3.7;
	eyez = -57;

	gluLookAt(eyex, eyey, eyez, // eye coordinates
		eyex + dir[0], eyey + dir[1], eyez + dir[2], // point of interest coordinates
		0, 1, 0); // vector UP reflects roll

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // loads the Identity matrix to the TRASFORMATION Matrix

	DrawGround();

	drawTree(20, 7, 5, 3, 0, 0.502, 0); // medium green
	drawTree(40, 8, 5, 5, 0.251, 0.502, 0); // olive 
	drawTree(80, 3, 5, 10, 0, 0.204, 0); // dark green
	drawTree(20, 1, -90, 10, 0, 0.502, 0.251); // turquoise 
	drawTree(150, 5, -90, 10, 0, 0.502, 0); // medium green
	drawTree(60, 0, -80, 7, 0, 0.804, 0); // light green
	drawTree(135, 0, -30, 7, 0.251, 0.502, 0); // olive 
	drawTree(-50, 7, 5, 10, 0, 0.804, 0);// light green
	drawTree(-80, 3, -80, 5, 0, 0.204, 0); // dark green
	drawTree(-70, 5, -20, 4, 0, 0.502, 0); // medium green
	drawTree(-65, 6, 10, 3, 0, 0.502, 0.251); // turquoise 
	drawTree(-10, 3, -65, 8, 0.251, 0.502, 0); // olive

	train->draw();
	for (int i = 0; i < 30; i++)
	{
		smokes[i]->setLocation(train->getLocomotiveCoordinate() - 2 - smoke_offset[i], sqrt(smoke_offset[i]) + 5.5, -56.25, train->getLocomotiveCoordinate() - 2);
		glColor3d(smoke_offset[i] / 50, smoke_offset[i] / 50, smoke_offset[i] / 50);
		glPushMatrix();
		glTranslated(smokes[i]->getX(), smokes[i]->getY(), smokes[i]->getZ());
		DrawTexSphere(30, 30, 1, 1, 1);
		glScaled(50, 50, 50);
		glPopMatrix();
	}

	glutSwapBuffers(); // show all
}

void displayCabin()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clean frame buffer and depth buffer
	glViewport(0, 0, W, H);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // loads the Identity matrix to the Projection Matrix
	// define the camera model
	glFrustum(-1, 1, -1, 1, 1, 300);
	// define the viewing parameters

	yaw = PI / 2;
	eyex = train->getLocomotiveCoordinate() - 6.5;
	eyey = 5;
	eyez = -56.25;

	gluLookAt(eyex, eyey, eyez, // eye coordinates
		eyex + dir[0], eyey + dir[1], eyez + dir[2], // point of interest coordinates
		0, 1, 0); // vector UP reflects roll

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // loads the Identity matrix to the TRASFORMATION Matrix
	DrawGround();
	
	drawTree(20, 7, 5, 3, 0, 0.502, 0); // medium green
	drawTree(40, 8, 5, 5, 0.251, 0.502, 0); // olive 
	drawTree(80, 3, 5, 10, 0, 0.204, 0); // dark green
	drawTree(20, 1, -90, 10, 0, 0.502, 0.251); // turquoise 
	drawTree(150, 5, -90, 10, 0, 0.502, 0); // medium green
	drawTree(60, 0, -80, 7, 0, 0.804, 0); // light green
	drawTree(135, 0, -30, 7, 0.251, 0.502, 0); // olive 
	drawTree(-50, 7, 5, 10, 0, 0.804, 0);// light green
	drawTree(-80, 3, -80, 5, 0, 0.204, 0); // dark green
	drawTree(-70, 5, -20, 4, 0, 0.502, 0); // medium green
	drawTree(-65, 6, 10, 3, 0, 0.502, 0.251); // turquoise 
	drawTree(-10, 3, -65, 8, 0.251, 0.502, 0); // olive

	train->draw();
	for (int i = 0; i < 30; i++)
	{
		smokes[i]->setLocation(train->getLocomotiveCoordinate() - 2 - smoke_offset[i], sqrt(smoke_offset[i]) + 5.5, -56.25, train->getLocomotiveCoordinate() - 2);
		glColor3d(smoke_offset[i] / 50, smoke_offset[i] / 50, smoke_offset[i] / 50);
		glPushMatrix();
		glTranslated(smokes[i]->getX(), smokes[i]->getY(), smokes[i]->getZ());
		DrawTexSphere(30, 30, 1, 1, 1);
		glScaled(50, 50, 50);
		glPopMatrix();
	}

	glutSwapBuffers(); // show all
}

void display()
{
	double x, y, beta;

	//frame buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clean frame buffer and depth buffer
	glViewport(0, 0, W, H);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // loads the Identity matrix to the Projection Matrix
	// define the camera model
	glFrustum(-1, 1, -1, 1, 1, 300);
	// define the viewing parameters

	//yaw = 0;
	eyex = train->getLocomotiveCoordinate() - 15;
	//eyey = 15;
	//eyez = -75;

	gluLookAt(eyex, eyey, eyez, // eye coordinates
		eyex + dir[0], eyey + dir[1], eyez + dir[2], // point of interest coordinates
		0, 1, 0); // vector UP reflects roll

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // loads the Identity matrix to the TRASFORMATION Matrix

	DrawGround();

	eyex = train->getLocomotiveCoordinate() - 15;

	train->draw();
	drawTree(20, 7, 5, 3, 0, 0.502, 0); // medium green
	drawTree(40, 8, 5, 5, 0.251, 0.502, 0); // olive 
	drawTree(80, 3, 5, 10, 0, 0.204, 0); // dark green
	drawTree(20, 1, -90, 10, 0, 0.502, 0.251); // turquoise 
	drawTree(150, 5, -90, 10, 0, 0.502, 0); // medium green
	drawTree(60, 0, -80, 7, 0, 0.804, 0); // light green
	drawTree(135, 0, -30, 7, 0.251, 0.502, 0); // olive 
	drawTree(-50, 7, 5, 10, 0, 0.804, 0);// light green
	drawTree(-80, 3, -80, 5, 0, 0.204, 0); // dark green
	drawTree(-70, 5, -20, 4, 0, 0.502, 0); // medium green
	drawTree(-65, 6, 10, 3, 0, 0.502, 0.251); // turquoise 
	drawTree(-10, 3, -65, 8, 0.251, 0.502, 0); // olive

	for (int i = 0; i < 30; i++)
	{
		smokes[i]->setLocation(train->getLocomotiveCoordinate() - 2 - smoke_offset[i], sqrt(smoke_offset[i]) + 5.5, -56.25, train->getLocomotiveCoordinate() - 2);
		glColor3d(smoke_offset[i] / 50, smoke_offset[i] / 50, smoke_offset[i] / 50);
		glPushMatrix();
		glTranslated(smokes[i]->getX(), smokes[i]->getY(), smokes[i]->getZ());
		DrawTexSphere(30, 30, 1, 1, 1);
		glScaled(50, 50, 50);
		glPopMatrix();
	}
	glutSwapBuffers(); // show all
}

void idle()
{
	int i, j;
	double dist;
	offset += 0.2;
	smoke += 0.5;
	if (smoke > 50)
		smoke = 0;
	for (int i = 0; i < 30; i++)
	{
		smoke_offset[i] += 0.5;
		if (smoke_offset[i] > 50)
			smoke_offset[i] = 0;
	}

	// set locomotion direction 
	yaw += angularSpeed;
	// setup the sight direction
	dir[0] = sin(yaw);
	dir[1] = sin(pitch);
	dir[2] = cos(yaw);
	// setup the motion
	eyex += speed * dir[0];
	eyey += speed * dir[1];
	eyez += speed * dir[2];

	train->move();

	glutPostRedisplay(); // posts message (with request to show the frame ) to main window
}


void special_key(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		angularSpeed += 0.001;
		break;
	case GLUT_KEY_RIGHT:
		angularSpeed -= 0.001;
		break;
	case GLUT_KEY_UP:
		speed += 0.01;
		break;
	case GLUT_KEY_DOWN:
		speed -= 0.01;
		break;
	case GLUT_KEY_PAGE_UP:
		pitch += 0.1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		pitch -= 0.1;
		break;
	}
}

void menu(int choice)
{
	switch (choice)
	{
	case 1:
		glutDisplayFunc(display); // refresh window function
		break;
	case 2:
		glutDisplayFunc(displayCabin);
		break;
	case 3:
		glutDisplayFunc(displayPassenger);
			break;
	}
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	// defines BUFFERS: Color buffer (frame buffer) and Depth buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(300, 30);
	glutCreateWindow("3D Example");

	glutDisplayFunc(display); // refresh window function
	glutIdleFunc(idle); // kind of timer function

	glutSpecialFunc(special_key);
	// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Regular view", 1);
	glutAddMenuEntry("Cabin view", 2);
	glutAddMenuEntry("Passenger view", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}