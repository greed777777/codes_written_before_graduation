#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include"bresenham.h"

void lineBres(int x1, int y1, int x2, int y2, int lType, char r, char g, char b,int isFirst)
{
	int dx = abs(x2 - x1), dy = abs(y2 - y1);
	int p, twoDy,twoDx, twoDyDx, twoDxDy;
	int x, y, xEnd, yEnd, IorD;
	int i, j;
	int mask[3][8] = { {1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0},{1,0,1,0,1,0,1,0} };
	FILE* fp;

	fp = fopen("D:\\BREout.ppm", "wb");
	fprintf(fp, "%c%d\n", 'P', 6);
	fprintf(fp, "%d %d\n", WIDTH, HEIGHT);
	fprintf(fp, "%d\n", MAX);
	if (dx > dy) {
		p = 2 * dy - dx; twoDy = 2 * dy; twoDyDx = 2 * (dy - dx);

		if (x1 > x2) { x = x2; y = y2; xEnd = x1; if (y1 - y2 > 0)IorD = 1; else IorD = -1; }
		else { x = x1; y = y1; xEnd = x2; if (y2 - y1 > 0)IorD = 1; else IorD = -1; }

		if(isFirst == TRUE)
			for(i = 0; i < HEIGHT; i++)
				for(j = 0; j<WIDTH; j++)
				{ 
					Iarray[i][j][0] = 255;
					Iarray[i][j][1] = 255;
					Iarray[i][j][2] = 255;// start point marking with a user-defined color(r,g,b) 
				}
		

		while (x < xEnd) {
			x++;
			if (p < 0) p += twoDy;
			else { y += IorD; p += twoDyDx; }
			if (mask[lType][x % 8] == 1) {
				Iarray[x][y][0] = r;
				Iarray[x][y][1] = g;
				Iarray[x][y][2] = b;//marking
			}
		}// end of while

		fwrite(Iarray, sizeof(char), WIDTH*HEIGHT * 3, fp);
		fclose(fp);
	}// end of if
	else {

		p = 2 * dx - dy; twoDx = 2 * dx; twoDxDy = 2 * (dx - dy);

		if (y1 > y2) { x = x2; y = y2; yEnd = y1; if (x1 - x2 > 0)IorD = 1; else IorD = -1; }
		else { x = x1; y = y1; yEnd = y2; if (x2 - x1 > 0)IorD = 1; else IorD = -1; }

		if(isFirst == TRUE)
			for (i = 0; i < HEIGHT; i++)
				for (j = 0; j < WIDTH; j++)
				{
					Iarray[i][j][0] = 255;
					Iarray[i][j][1] = 255;
					Iarray[i][j][2] = 255;// start point marking with a user-defined color(r,g,b) 
				}


		while (y < yEnd) {
			y++;
			if (p < 0) p += twoDx;
			else { x += IorD; p += twoDxDy; } // p = 2dx - 2dy

			if (mask[lType][y % 8] == 1) {
				Iarray[x][y][0] = r;
				Iarray[x][y][1] = g;
				Iarray[x][y][2] = b;//marking
			}
		}// end of while

		fwrite(Iarray, sizeof(char), WIDTH*HEIGHT * 3, fp);
		fclose(fp);

	}// end of else

}
