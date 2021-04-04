#include "Ground.h"

void ReadInitialCoordinates()
{
	for (int i = 0; i < ROWS / 10; i++)
		for (int j = 0; j < COLUMNS / 10; j++)
			heights[i * 10][j * 10] = INITIAL_HEIGHTS_MATRIX[i][j];
}

void TerrainChassis()
{
	int gap = 10;
	double lowBuffer, highBuffer;

	for (int i = 0; i < ROWS; i += gap)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (j % 10 == 0)
			{
				lowBuffer = heights[i][j];
				if (j < ROWS - 10)
					highBuffer = heights[i][j + 10];
				else
					highBuffer = heights[i][j] - 1;

			}
			else
				heights[i][j] = (lowBuffer - highBuffer) / 10 + lowBuffer;
		}
		if (i == ROWS - 10)
			gap = 9;
	}

	gap = 10;
	for (int j = 0; j < COLUMNS; j += gap)
	{
		for (int i = 0; i < ROWS; i++)
		{
			if (i % 10 == 0)
			{
				lowBuffer = heights[i][j];
				if (i < ROWS - 10)
					highBuffer = heights[i][j + 10];
				else
					highBuffer = heights[i][j] - 1;

			}
			else
				heights[i][j] = (lowBuffer - highBuffer) / 10 + lowBuffer;
		}
		if (j == ROWS - 10)
			gap = 9;
	}
}

void PrepareRoad()
{
	int j;

	for (j = 0; j < COLUMNS; j++)
		heights[41][j] = heights[39][j] = heights[40][j];
}

void SmoothTerrain()
{
	for (int i = 1; i < ROWS; i++)
		for (int j = 1; j < COLUMNS; j++)
			if (i % 10 != 0 && j % 10 != 0)
			{
				if (i == 1 || i == ROWS - 1 || j == 1 || j == ROWS - 1)
					heights[i][j] = heights[i - 1][j] / 2 + heights[i][j - 1] / 2;
				else
					heights[i][j] = (heights[i - 1][j] + heights[i - 2][j] + heights[i][j - 1]
						+ heights[i][j - 2] + heights[i - 1][j - 1]) / 5;
			}

	for (int counter = 0; counter < 10; counter++)
		for (int i = 1; i < ROWS - 1; i++)
			for (int j = 1; j < COLUMNS - 1; j++)
				heights[i][j] = (heights[i][j + 1] + heights[i][j - 1] +
					heights[i - 1][j - 1] + heights[i - 1][j] + heights[i - 1][j + 1] +
					heights[i + 1][j - 1] + heights[i + 1][j] + heights[i + 1][j + 1]) / 8;
}

void DrawGround()
{
	int i, j;
	glColor3d(0, 0, 0.3);

	for (i = 0; i < ROWS - 1; i++)
		for (j = 0; j < COLUMNS - 1; j++)
		{
			glBegin(GL_POLYGON);
			SetColor(heights[i][j]);
			glVertex3d((double)j - ROWS / 2, heights[i][j], (double)i - ROWS / 2);
			SetColor(heights[i][j + 1]);
			glVertex3d((double)j + 1 - ROWS / 2, heights[i][j + 1], (double)i - ROWS / 2);
			SetColor(heights[i + 1][j + 1]);
			glVertex3d((double)j + 1 - ROWS / 2, heights[i + 1][j + 1], (double)i + 1 - ROWS / 2);
			SetColor(heights[i + 1][j]);
			glVertex3d((double)j - ROWS / 2, heights[i + 1][j], (double)i + 1 - ROWS / 2);
			glEnd();
		}
	DrawRail();
	ScanRailSurface(50);
	DrawBridge();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0, 0.2, 0.6, 0.8);
	glBegin(GL_POLYGON);
	glVertex3d(-COLUMNS / 4, 0, -ROWS / 2);
	glVertex3d(-COLUMNS / 4, 0, ROWS / 2);
	glVertex3d(COLUMNS / 2, 0, ROWS / 2);
	glVertex3d(COLUMNS / 2, 0, -ROWS / 2);
	glEnd();
	glDisable(GL_BLEND);
}

void SetColor(double height)
{
	if (fabs(height) < 4)
		glColor3d(0.8, 0.7, 0.5);
	if (fabs(height) < 12)
		glColor3d(0.3 + height / 80, 0.6 - fabs(height) / 30, 0);
	else
		glColor3d(sqrt(height) / 5, sqrt(height) / 5, sqrt(height) / 4.0);
}

void DrawRail()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	for (int j = 0; j < COLUMNS - 1; j++)
	{
		glBegin(GL_POLYGON);
		glTexCoord2d(0, 0);
		if (heights[40][j] >= 2)
			glVertex3d((double)j - 100, /*heights[40][j] + 0.2*/2.2, -58.5);
		else
			glVertex3d((double)j - 100, 2.2, -58.5);
		glTexCoord2d(1, 0);

		if (heights[40][j + 1] >= 2)
		{
			glVertex3d((double)j + 1 - 100, /*heights[40][j + 1] + 0.2*/2.2, -58.5);
			glTexCoord2d(1, 2);
			glVertex3d((double)j + 1 - 100, /*heights[40][j + 1] + 0.2*/2.2, -55.5);
		}
		else
		{
			glVertex3d((double)j + 1 - 100, 2.2, -58.5);
			glTexCoord2d(1, 2);
			glVertex3d((double)j + 1 - 100, 2.2, -55.5);
		}
		glTexCoord2d(0, 2);

		if (heights[40][j] >= 2)
			glVertex3d((double)j - 100, heights[40][j] + 0.2, -55.5);
		else
			glVertex3d((double)j - 100, 2.2, -55.5);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

void ScanRailSurface(int row)
{
	if (heights[row][get<0>(streamBed)] <= 0 && heights[row][get<1>(streamBed)] <= 0)
	{
		get<0>(streamBed) -= 5;
		get<1>(streamBed) += 5;
		return;
	}
	else
	{
		if (heights[row][get<0>(streamBed)] > 0)
			get<0>(streamBed) += 5;
		if (heights[row][get<1>(streamBed)] > 0)
			get<1>(streamBed) -= 5;
		ScanRailSurface(row);
	}
}

void DrawBridge()
{
	int counter = 0;
	for (int i = get<0>(streamBed); i <= get<1>(streamBed); i += 3)
		DrawBridgeColumns(i, counter++, 39);

	glColor3d(0.72, 0.45, 0.2);
	glBegin(GL_POLYGON);
	glVertex3d((double)get<0>(streamBed) - 105, 1.99, -60.1);
	glVertex3d((double)get<0>(streamBed) - 105, 1.99, -59.9);
	glVertex3d((double)get<1>(streamBed) - 105, 1.99, -59.9);
	glVertex3d((double)get<1>(streamBed) - 105, 1.99, -60.1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((double)get<0>(streamBed) - 105, 1.99, -54.1);
	glVertex3d((double)get<0>(streamBed) - 105, 1.99, -53.9);
	glVertex3d((double)get<1>(streamBed) - 105, 1.99, -53.9);
	glVertex3d((double)get<1>(streamBed) - 105, 1.99, -54.1);
	glEnd();

	glColor3d(0.8, 0.2, 0.1);
	glBegin(GL_POLYGON);
	glVertex3d((double)get<0>(streamBed) - 105, 1.99, -60.1);
	glVertex3d((double)get<0>(streamBed) - 105, 1.8, -60.1);
	glVertex3d((double)get<1>(streamBed) - 105, 1.8, -60.1);
	glVertex3d((double)get<1>(streamBed) - 105, 1.99, -60.1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((double)get<0>(streamBed) - 105, 1.99, -54.1);
	glVertex3d((double)get<0>(streamBed) - 105, 1.8, -54.1);
	glVertex3d((double)get<1>(streamBed) - 105, 1.8, -54.1);
	glVertex3d((double)get<1>(streamBed) - 105, 1.99, -54.1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((double)get<0>(streamBed) - 105, 1.99, -59.9);
	glVertex3d((double)get<0>(streamBed) - 105, 1.8, -59.9);
	glVertex3d((double)get<1>(streamBed) - 105, 1.8, -59.9);
	glVertex3d((double)get<1>(streamBed) - 105, 1.99, -59.9);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((double)get<0>(streamBed) - 105, 1.99, -53.9);
	glVertex3d((double)get<0>(streamBed) - 105, 1.8, -53.9);
	glVertex3d((double)get<1>(streamBed) - 105, 1.8, -53.9);
	glVertex3d((double)get<1>(streamBed) - 105, 1.99, -53.9);
	glEnd();
}

void DrawBridgeColumns(int columnPos, int i, int numOfColumns)
{
	double alpha, teta = 2 * PI / 10;

	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		// defines one side

		glBegin(GL_POLYGON);
		glColor3d(0.72, 0.45, 0.2);

		glVertex3d(sin(alpha) / 6 + columnPos - 105, 10 + 10 * sin(2 * PI * i / numOfColumns), cos(alpha) / 6 - 54); // vertex 1
		glVertex3d(sin(alpha + teta) / 6 + columnPos - 105, 10 + 10 * sin(2 * PI * i / numOfColumns), cos(alpha + teta) / 6 - 54); // vertex 2

		glColor3d(fabs(sin(alpha)) / 2, (1 + cos(alpha)) / 4, 1 - fabs(sin(alpha + PI / 2)));

		glVertex3d(sin(alpha + teta) / 6 + columnPos - 105, heights[40][columnPos], cos(alpha + teta) / 6 - 54); // vertex 3
		glVertex3d(sin(alpha) / 6 + columnPos - 105, heights[40][columnPos], cos(alpha) / 6 - 54); // vertex 4
		glEnd();

		glBegin(GL_POLYGON);
		glColor3d(0.72, 0.45, 0.2);
		glVertex3d(sin(alpha) / 6 + columnPos - 105, 10 + 10 * sin(2 * PI * i / numOfColumns), cos(alpha) / 6 - 60); // vertex 1
		glVertex3d(sin(alpha + teta) / 6 + columnPos - 105, 10 + 10 * sin(2 * PI * i / numOfColumns), cos(alpha + teta) / 6 - 60); // vertex 2
		glColor3d(fabs(sin(alpha)) / 2, (1 + cos(alpha)) / 4, 1 - fabs(sin(alpha + PI / 2)));
		glVertex3d(sin(alpha + teta) / 6 + columnPos - 105, heights[40][columnPos], cos(alpha + teta) / 6 - 60); // vertex 3
		glVertex3d(sin(alpha) / 6 + columnPos - 105, heights[40][columnPos], cos(alpha) / 6 - 60); // vertex 4
		glEnd();

		glBegin(GL_POLYGON); //Top Bar
		glColor3d(0.72, 0.45, 0.2);
		glVertex3d((double)columnPos - 105 + cos(alpha) / 6, 10 + 10 * sin(2 * PI * i / numOfColumns) + sin(alpha) / 6, -54);
		glVertex3d((double)columnPos - 105 + cos(alpha + teta) / 6, 10 + 10 * sin(2 * PI * i / numOfColumns) + sin(alpha + teta) / 6, -54);
		glVertex3d((double)columnPos - 105 + cos(alpha + teta) / 6, 10 + 10 * sin(2 * PI * i / numOfColumns) + sin(alpha + teta) / 6, -60);
		glVertex3d((double)columnPos - 105 + cos(alpha) / 6, 10 + 10 * sin(2 * PI * i / numOfColumns) + sin(alpha) / 6, -60);
		glEnd();

		if (i > 0)
		{
			glBegin(GL_POLYGON);
			glVertex3d((double)columnPos - 105, 10 + 10 * sin(2 * PI * i / numOfColumns) + sin(alpha) / 6, -54 + cos(alpha) / 6);
			glVertex3d((double)columnPos - 105, 10 + 10 * sin(2 * PI * i / numOfColumns) + sin(alpha + teta) / 6, -54 + cos(alpha + teta) / 6);
			glVertex3d((double)columnPos - 105 - 3, 10 + 10 * sin(2 * PI * ((double)i - 1) / numOfColumns) + sin(alpha + teta) / 6, -54 + cos(alpha + teta) / 6);
			glVertex3d((double)columnPos - 105 - 3, 10 + 10 * sin(2 * PI * ((double)i - 1) / numOfColumns) + sin(alpha) / 6, -54 + cos(alpha) / 6);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3d((double)columnPos - 105, 10 + 10 * sin(2 * PI * i / numOfColumns) + sin(alpha) / 6, -60 + cos(alpha) / 6);
			glVertex3d((double)columnPos - 105, 10 + 10 * sin(2 * PI * i / numOfColumns) + sin(alpha + teta) / 6, -60 + cos(alpha + teta) / 6);
			glVertex3d((double)columnPos - 105 - 3, 10 + 10 * sin(2 * PI * ((double)i - 1) / numOfColumns) + sin(alpha + teta) / 6, -60 + cos(alpha + teta) / 6);
			glVertex3d((double)columnPos - 105 - 3, 10 + 10 * sin(2 * PI * ((double)i - 1) / numOfColumns) + sin(alpha) / 6, -60 + cos(alpha) / 6);
			glEnd();
		}
	}

	glBegin(GL_POLYGON);
	glVertex3d((double)columnPos - 105 + 0.1, 1.99, -54);
	glVertex3d((double)columnPos - 105 - 0.1, 1.99, -54);
	glVertex3d((double)columnPos - 105 - 0.1, 1.99, -60);
	glVertex3d((double)columnPos - 105 + 0.1, 1.99, -60);
	glEnd();

	glColor3d(0.8, 0.2, 0.1);
	glBegin(GL_POLYGON);
	glVertex3d((double)columnPos - 105 + 0.1, 1.99, -60);
	glVertex3d((double)columnPos - 105 + 0.1, 1.99, -54);
	glVertex3d((double)columnPos - 105 + 0.1, 1.8, -54);
	glVertex3d((double)columnPos - 105 + 0.1, 1.8, -60);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((double)columnPos - 105 - 0.1, 1.99, -60);
	glVertex3d((double)columnPos - 105 - 0.1, 1.99, -54);
	glVertex3d((double)columnPos - 105 - 0.1, 1.8, -54);
	glVertex3d((double)columnPos - 105 - 0.1, 1.8, -60);
	glEnd();
}