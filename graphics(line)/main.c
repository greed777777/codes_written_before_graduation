#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"dda.h"
#include"bresenham.h"
#include"midpoint.h"

int main() {
	int x1, y1, x2, y2, radius, lType, isFirst = TRUE, howMany, i,xa,yb;
	char r, g, b;
	srand(time(NULL));

	printf("DDA기법으로 선을 몇개나 그릴까요?\n");
	scanf("%d", &howMany);

	for (i = 0; i < howMany; i++) {
		x1 = rand() % 480;
		x2 = rand() % 480;
		y1 = rand() % 640;
		y2 = rand() % 640;
		lType = rand() % 3;
		r = (char)(rand() % 255);
		g = (char)(rand() % 255);
		b = (char)(rand() % 255);
		lineDDA(x1, y1, x2, y2, lType, r, g, b, isFirst);
		isFirst = FALSE;
	}

	isFirst = TRUE;

	printf("Bresenham기법으로 선을 몇개나 그릴까요?\n");
	scanf("%d", &howMany);

	for (i = 0; i < howMany; i++) {
		x1 = rand() % 480;
		x2 = rand() % 480;
		y1 = rand() % 640;
		y2 = rand() % 640;
		lType = rand() % 3;
		r = (char)(rand() % 255);
		g = (char)(rand() % 255);
		b = (char)(rand() % 255);
		lineBres(x1, y1, x2, y2,lType, r, g, b, isFirst);
		isFirst = FALSE;
	}

	isFirst = TRUE;

	printf("원을 몇개나 그릴까요?\n");
	scanf("%d", &howMany);

	for (i = 0; i < howMany; i++) {
		x1 = rand() % 480;
		y1 = rand() % 640;
		radius = rand() % 100;
		r = (char)(rand() % 255);
		g = (char)(rand() % 255);
		b = (char)(rand() % 255);
		circleMidpoint(x1,y1,radius,r,g,b,isFirst);
		isFirst = FALSE;
	}

	isFirst = TRUE;

	printf("타원을 몇개나 그릴까요?\n");
	scanf("%d", &howMany);

	for (i = 0; i < howMany; i++) {
		x1 = rand() % 480;
		y1 = rand() % 640;
		xa = rand() % 120;
		yb = rand() % 160;
		r = (char)(rand() % 255);
		g = (char)(rand() % 255);
		b = (char)(rand() % 255);
		ellipseMidpoint(x1, y1, xa, yb, r, g, b, isFirst);
		isFirst = FALSE;
	}

	system("pause");
}