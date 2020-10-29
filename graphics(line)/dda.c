#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"dda.h"

void lineDDA(int x1, int y1, int x2, int y2, int lineType, char r, char g, char b,int isFirst)
{
	FILE* fp;
	int dx = x2 - x1, dy = y2 - y1, step, i, j, k;
	enum lineType lType;
	lType = lineType;
	int mask[3][8] = { {1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0},{1,0,1,0,1,0,1,0} };

	float xinc, yinc, x = (float)x1, y = (float)y1;
	fp = fopen("D:\\DDAout.ppm", "wb");

	if (abs(dx) > abs(dy)) step = abs(dx);
	else step = abs(dy);
	xinc = dx / (float)step;
	yinc = dy / (float)step;

	//Iarray[x1][y1] = 0; // start pixel marking(setpixel function)

	if (isFirst == TRUE)
		for (i = 0; i < HEIGHT; i++)
			for (j = 0; j < WIDTH; j++)
				for (k = 0; k < 3; k++)
					Iarray[i][j][k] = 255;// r,g,b색상 모두 최대값을 대입

	for (k = 0; k < step; k++) {
		x += xinc;
		y += yinc;
		if (mask[lType][k % 8] == 1) {
			Iarray[(int)(x + 0.5)][(int)(y + 0.5)][0] = r;// marking(setpixel function)
			Iarray[(int)(x + 0.5)][(int)(y + 0.5)][1] = g;// marking(setpixel function)
			Iarray[(int)(x + 0.5)][(int)(y + 0.5)][2] = b;// marking(setpixel function)
		}
	}
	
	fprintf(fp, "%c%d\n", 'P', 6);
	fprintf(fp, "%s %d\n", "640", 480);
	fprintf(fp, "%d\n", 255);

	fwrite(Iarray, sizeof(char), HEIGHT * WIDTH* 3, fp);

	fclose(fp);

}
