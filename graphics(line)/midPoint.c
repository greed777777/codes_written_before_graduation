#define _CRT_SECURE_NO_WARNINGS
#include"midpoint.h"
#include<stdio.h>

void circlePlot(int Cx, int Cy, int x, int y, int r, int g, int b)
{
	setPixel(Cx + x, Cy + y,  r,  g,  b);//marking function according to the output device
	setPixel(Cx - x, Cy + y,  r,  g,  b);
	setPixel(Cx + x, Cy - y,  r,  g,  b);
	setPixel(Cx - x, Cy - y,  r,  g,  b);
	setPixel(Cx + y, Cy + x,  r,  g,  b);
	setPixel(Cx - y, Cy + x,  r,  g,  b);
	setPixel(Cx + y, Cy - x,  r,  g,  b);
	setPixel(Cx - y, Cy - x,  r,  g,  b);
}

void ellipsePlot(int Cx, int Cy, int x, int y, int r, int g, int b)
{
	setPixel(Cx + x, Cy + y, r, g, b);//marking function according to the output device
	setPixel(Cx - x, Cy + y, r, g, b);
	setPixel(Cx + x, Cy - y, r, g, b);
	setPixel(Cx - x, Cy - y, r, g, b);
}

void circleMidpoint(int xCenter, int yCenter, int radius, int r, int g, int b,int isFirst)
{
	int x = 0, y = radius, p = 1 - radius;
	int i, j;
	FILE* fp;

	fp = fopen("D:\\CircleOut.ppm", "wb");
	//circlePlot(xCenter, yCenter, x, y);//start pixel marking..

	if (isFirst == TRUE) {
		for (i = 0; i < HEIGHT; i++)
			for (j = 0; j < WIDTH; j++)
			{
				Iarray[i][j][0] = 255;
				Iarray[i][j][1] = 255;
				Iarray[i][j][2] = 255;// start point marking with a user-defined color(r,g,b) 
			}
	}

	circlePlot(xCenter, yCenter, x, y, r, g, b);
	while (x <= y) {
		x++;
		if (p < 0) p += 2 * x + 1;
		else { y--; p += 2 * (x - y) + 1; }

		circlePlot(xCenter, yCenter, x, y,r,g,b);//marking..
	}

	fprintf(fp, "%c%d\n", 'P', 6);
	fprintf(fp, "%d %d\n", WIDTH, HEIGHT);
	fprintf(fp, "%d\n", MAX);

	fwrite(Iarray, sizeof(char), WIDTH*HEIGHT * 3, fp);
	fclose(fp);
}

void ellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry, int r, int g, int b,int isFirst)
{
	int Rx2 = Rx * Rx, Ry2 = Ry * Ry, twoRx2 = 2 * Rx2, twoRy2 = 2 * Ry2;
	int p, x = 0, y = Ry, px = 0, py = twoRx2 * y;
	int i, j;
	FILE* fp;

	fp = fopen("D:\\ellipseOut.ppm", "wb");

	

	if (isFirst == TRUE) {
		for (i = 0; i < HEIGHT; i++)
			for (j = 0; j < WIDTH; j++)
			{
				Iarray[i][j][0] = 255;
				Iarray[i][j][1] = 255;
				Iarray[i][j][2] = 255;// start point marking with a user-defined color(r,g,b) 
			}
	}

	//ellipsePlot(xCenter, yCenter, x, y, r, g, b);//start pixel marking..

	//Region 1
	p = ROUND(Ry2 - (Rx2*Ry) + (0.25*Rx2));
	while (px < py) {
		x++;
		px += twoRy2;
		if (p < 0) p += Ry2 + px;
		else { y--; py -= twoRx2; p += Ry2 + px - py; }

		ellipsePlot(xCenter, yCenter, x, y,r,g,b);//marking..
	}

	//Region 2
	p = ROUND(Ry2*(x + 0.5)*(x + 0.5) + Rx2 * (y - 1)*(y - 1) - Rx2 * Ry2);
	while (y > 0) {
		y--;
		py -= twoRx2;
		if (p > 0) p += Rx2 - py;
		else { x++; px += twoRy2; p += Rx2 - py + px; }

		ellipsePlot(xCenter, yCenter, x, y,r,g,b);//marking..
	}

	fprintf(fp, "%c%d\n", 'P', 6);
	fprintf(fp, "%d %d\n", WIDTH, HEIGHT);
	fprintf(fp, "%d\n", MAX);

	fwrite(Iarray, sizeof(char), WIDTH*HEIGHT * 3, fp);
}

void setPixel(int x, int y, int r,int g, int b) {
	x += HEIGHT;
	y += WIDTH;
	Iarray[x%HEIGHT][y%WIDTH][0] = r;	//
	Iarray[x%HEIGHT][y%WIDTH][1] = g;	//
	Iarray[x%HEIGHT][y%WIDTH][2] = b;	//
}

int ROUND(double x) {
	if ((x - (int)x) > 0.5)
		return (int)x;
	else
		return (int)x + 1;
}

