#include <stdio.h>
#include <stdlib.h>
#include <glut.h>						//must install package freeglut.2.8.1.15 
#include "BmpLoader.h"
#include <time.h>
#include <math.h> 
#include "Textures/textures.ppm"		//Texture map array 
#include "Textures/sky.ppm"				//sky texture array
#include "Textures/mapW.ppm"			//Map layout array 
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>						//for printing fps to console
typedef struct
{
	int w, a, d, s, e;					//button state on off
} ButtonKeys; ButtonKeys Keys;
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533					//one degree in radians
int initial_time = time(NULL), final_time, frame_count = 0;
unsigned int ID;
float degToRad(float a) { return a * M_PI / 180.0; }
float FixAng(float a) { if (a > 359) { a -= 360; } if (a < 0) { a += 360; } return a; }
float frame1, frame2, fps;
float px, py, pdx, pdy, pa;				//player position

//-------------------------------------------------MAP-------------------------------------------------
#define mapX 16			//map width
#define mapY 16			//map height
#define mapS 32			//map cube size
int mapF[] =			//floors
{
	110,110,110,110,110,110,110,110,	110,110,110,110,110,110,110,110,
	110,100,100,111,110,110,110,110,	110,110,110,110,111,100,99 ,110,
	110,99 ,111,111,110,110,110,110,	110,110,110,110,111,111,100,110,
	110,111,111,181,182,181,181,181,	181,182,181,181,181,111,111,110,
	110,110,110,181,181,187,181,186,	187,181,181,181,181,110,110,110,
	110,110,110,181,181,181,181,187,	187,181,181,181,181,110,110,110,
	110,110,110,181,181,181,181,182,	186,181,186,185,181,110,110,110,
	110,110,110,186,181,187,181,186,	187,187,181,181,181,110,110,110,

	110,110,110,181,182,186,185,182,	185,182,181,181,181,110,110,110,
	110,110,110,181,181,187,181,186,	187,181,181,181,181,110,110,110,
	110,110,110,181,181,181,181,187,	187,181,185,181,182,110,110,110,
	110,110,110,181,182,181,181,185,	181,182,181,181,181,110,110,110,
	110,111,111,181,181,181,181,181,	181,181,181,181,181,111,111,110,
	110,99 ,111,111,110,110,110,110,	110,110,110,110,111,111,100,110,
	110,96 ,99 ,111,110,110,110,110,	110,110,110,110,111,100,100,110,
	110,110,110,110,110,110,110,110,	110,110,110,110,110,110,110,110,
};
int mapC[] =			//ceiling
{ 
	28,28,28,28,28,28,28,28,	28,28,28,28,28,28,28,28,
	28,28,28,28,28,28,28,28,	28,28,28,28,28,28,28,28,
	28,28,28,28,28,28,28,28,	28,28,28,28,28,28,28,28,
	28,28,28,28,28,28,28,28,	28,28,28,28,28,28,28,28,
	28,28,28,28, 0, 0, 0, 0,	0, 0, 0, 0, 28,28,28,28,
	28,28,28,28, 0, 0, 0, 0,	0, 0, 0, 0, 28,28,28,28,
	28,28,28,28, 0, 0, 0, 0,	0, 0, 0, 0, 28,28,28,28,
	28,28,28,28, 0, 0, 0, 0,	0, 0, 0, 0, 28,28,28,28,

	28,28,28,28, 0, 0, 0, 0,	0, 0, 0, 0, 28,28,28,28,
	28,28,28,28, 0, 0, 0, 0,	0, 0, 0, 0, 28,28,28,28,
	28,28,28,28, 0, 0, 0, 0,	0, 0, 0, 0, 28,28,28,28,
	28,28,28,28, 0, 0, 0, 0,	0, 0, 0, 0, 28,28,28,28,
	28,28,28,28,28,28,28,28,	28,28,28,28,28,28,28,28,
	28,28,28,28,28,28,28,28,	28,28,28,28,28,28,28,28,
	28,28,28,28,28,28,28,28,	28,28,28,28,28,28,28,28,
	28,28,28,28,28,28,28,28,	28,28,28,28,28,28,28,28,
};
//-------------------------------------------------Draw Rays and Walls-------------------------------------------------
float dist(float ax, float ay, float bx, float by, float ang) { return cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay); }
void drawRays3D()
{
	int r, mx, my, mp, dof, side; float vx, vy, rx, ry, ra, xo, yo, disV, disH, disT{};
	ra = FixAng(pa + 30);
	for (r = 0; r < 240; r++)						//set ray back 30 degrees
	{
		int vmt = 0, hmt = 0;						//vertical and horizontal map texture number
		//---------------check vertical lines------------
		dof = 0; side = 0; disV = 1000000;
		float Tan = tan(degToRad(ra));
		if (cos(degToRad(ra)) > 0.0001) { rx = (((int)px >> 6) << 6) + 64;		ry = (px - rx) * Tan + py; xo = 64; yo = -xo * Tan; }			//looking left
		else if (cos(degToRad(ra)) < -0.0001) { rx = (((int)px >> 6) << 6) - 0.0001;   ry = (px - rx) * Tan + py; xo = -64; yo = -xo * Tan; }	//looking right
		else { rx = px; ry = py; dof = 16; }		//looking straight up or down

		while (dof < 16)
		{
			mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapW[mp]>0) { vmt = mapW[mp] - 1; dof = 16; disV = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py); }//hit wall
			else { rx += xo; ry += yo; dof += 1; }	//Next line
		}
		vx = rx; vy = ry;

		//---------------check horizontal lines------------
		dof = 0; disH = 1000000,
			Tan = 1.0 / Tan;
		if (sin(degToRad(ra)) > 0.001) { ry = (((int)py >> 6) << 6) - 0.0001; rx = (py - ry) * Tan + px; yo = -64; xo = -yo * Tan; }	//looking up
		else if (sin(degToRad(ra)) < -0.001) { ry = (((int)py >> 6) << 6) + 64;	 rx = (py - ry) * Tan + px; yo = 64; xo = -yo * Tan; }	//looking down
		else { rx = px; ry = py; dof = 16; }		//looking straight left or right
		while (dof < 16)
		{
			mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapW[mp]>0) { hmt = mapW[mp] - 1; dof = 16; disH = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py); }//hit wall
			else { rx += xo; ry += yo; dof += 1; }	//Next line
		}
		float shade = 1;	
		if (disV < disH) { hmt = vmt; shade = 0.5; rx = vx; ry = vy; disH = disV; glColor3f(0.6, 0, 0); }	//horizontal wall hit

		int ca = FixAng(pa - ra); disH = disH * cos(degToRad(ca));				//fix fisheye
		int lineH = (mapS * 1500) / (disH);										//line height
		float ty_step = 64 / (float)lineH;										
		float ty_off = 0;
		if (lineH > 640) { ty_off = (lineH - 640) / 2.0; lineH = 640; }			//line height
		int lineO = 320 - (lineH >> 1);											//Line offset

		//-----------------Draw Walls-----------------------
		int y;
		float ty = ty_off * ty_step;//hmt = 0;
		float tx;
		if (shade==1) { tx=(int)(rx/1)%64; if (ra>180) { tx=63-tx; } }	//texture sizes x axis
		else { tx=(int)(ry/1)%64; if (ra>90 && ra<270) { tx=63-tx; } }	//texture sizes y axis
		for (y=0; y<lineH; y++)
		{
			int pixel = ((int)ty*64+(int)tx)*3+(hmt*64*64*3);			//texture map offsets
			int red		= textures[pixel+0]*shade;
			int green	= textures[pixel+1]*shade;
			int blue	= textures[pixel+2]*shade;
			glPointSize(8);	glColor3ub(red, green, blue); glBegin(GL_POINTS); glVertex2i(r * 4, y + lineO); glEnd();
			ty += ty_step;
		}
		//-----------------Draw floors----------------------
		
		for (y = lineO + lineH; y < 640; y++)
		{
			float dy=y-(640/2), deg=degToRad(ra), raFix=cos(degToRad(FixAng(pa-ra)));
			tx = px+cos(deg)*180*4*32/dy/raFix;
			ty = py-sin(deg)*180*4*32/dy/raFix;
			int mp=mapF[(int)(ty/64.0)*mapX+(int)(tx/64.0)]*64*64-4095;	//define texture # to mp
			int pixel = (((int)(ty) & 63)*64+((int)(tx) & 63))*3+mp*3;	//texture map offsets
			int red		= textures[pixel+0]*0.7;
			int green	= textures[pixel+1]*0.7;
			int blue	= textures[pixel+2]*0.7;
			glPointSize(8); glColor3ub(red, green, blue); glBegin(GL_POINTS); glVertex2i(r * 4, y); glEnd();
			
			//--------------Draw ceiling-------------------
			mp=mapC[(int)(ty/64.0)*mapX+(int)(tx/64.0)]*64*64-4095;		//define texture # to mp
			pixel = (((int)(ty) & 63)*64+((int)(tx) & 63))*3+mp*3;		//texture map offsets
			red		= textures[pixel+0];
			green	= textures[pixel+1];
			blue	= textures[pixel+2];
			if (mp>0){glPointSize(8);	glColor3ub(red,green,blue); glBegin(GL_POINTS); glVertex2i(r*4,640-y); glEnd();}
			
		}
			ra = FixAng(ra - 0.25);
	}
}
void LoadTexture(const char* filename)
{
	BmpLoader bl(filename);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData);
}
//-------------------------------------------------HUD element-------------------------------------------------
/*
void HUD()
{
	if (HUDtex == 0)
		HUDtex = LoadTexture("/hud.bmp");
	glBindTexture(GL_TEXTURE_2D, HUDtex);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);	glVertex2f(0.05, 0.05);
	glTexCoord2f(1.0, 1.0);	glVertex2f(0.3, 0.05);
	glTexCoord2f(1.0, 1.0);	glVertex2f(0.3, 0.15);
	glTexCoord2f(0.0, 0.0);	glVertex2f(0.05, 0.15);
	glEnd();
}
void drawHUD()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 0.1,0.1,0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	HUD::HUD();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
*/
//-------------------------------------------------Draw Sky-------------------------------------------------
void drawSky()
{
	int x, y;
	for (y = 0; y < 290; y++)						//size of image to display in y
	{
		for (x = 0; x < 960; x++)					//size of image in x (screen width)
		{
			int xo = (int)pa*13 - x; if (xo < 0) { xo += 720; } xo = xo % 720;	//image size x axis
			int pixel = (y * 720 + xo) * 3;		//texture map offsets
			int red = sky[pixel + 0];
			int green = sky[pixel + 1];
			int blue = sky[pixel + 2];
			glPointSize(2); glColor3ub(red, green, blue); glBegin(GL_POINTS); glVertex2i(x, y*1.2); glEnd();
		}
	}
}
void init()
{
	glClearColor(0.3, 0.3, 0.3, 0);					//background colour
	gluOrtho2D(0, 960, 640, 0);						//screen dimensions
	px = 500; py = 500; pa = 0;						//Player starting position
	pdx = cos(degToRad(pa)); pdy = sin(degToRad(pa));
}
int gameState = 0, timer = 0, sprint = 0;
void display()
{
	//frames per second
	frame2 = glutGet(GLUT_ELAPSED_TIME); fps = (frame2 - frame1); frame1 = glutGet(GLUT_ELAPSED_TIME);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//-----------------------------------------player movement-------------------------------------------------

	if (Keys.a == 1) { pa += 0.2 * fps; pa = FixAng(pa); pdx = cos(degToRad(pa)); pdy = -sin(degToRad(pa)); } //looking left
	if (Keys.d == 1) { pa -= 0.2 * fps; pa = FixAng(pa); pdx = cos(degToRad(pa)); pdy = -sin(degToRad(pa)); } //looking right

	int xo = 0; if (pdx < 0) { xo = -20; }
	else { xo = 20; }
	int yo = 0; if (pdy < 0) { yo = -20; }
	else { yo = 20; }
	int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0, ipx_sub_xo = (px - xo) / 64.0;
	int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0, ipy_sub_yo = (py - yo) / 64.0;

	if (Keys.w == 1 && sprint == 1)					//sprinting function 
	{
		timer += 1 * fps;
		if (mapW[ipy * mapX + ipx_add_xo] == 0) { px += pdx * 0.14 * fps; }
		if (mapW[ipy_add_yo * mapX + ipx] == 0) { py += pdy * 0.14 * fps; }
		if (timer > 5000 + timer/3) { timer = 0; sprint = 0; }		//sprint run timer
	}
	if (Keys.w == 1)								//move forward
	{
		if (mapW[ipy * mapX + ipx_add_xo] == 0) { px += pdx * 0.13 * fps; }
		if (mapW[ipy_add_yo * mapX + ipx] == 0) { py += pdy * 0.13 * fps; }
		timer += 1 * fps;
	}
	if (Keys.s == 1)								//move backwards
	{
		if (mapW[ipy * mapX + ipx_sub_xo] == 0) { px -= pdx * 0.1 * fps; }
		if (mapW[ipy_sub_yo * mapX + ipx] == 0) { py -= pdy * 0.1 * fps; }
	}
	//-----------------------------------------display order-------------------------------------------------
	glutPostRedisplay();
	drawSky();
	drawRays3D();
	//drawHUD();
	glutSwapBuffers();

	frame_count++;									//FPS counter
	final_time = time(NULL);
	if (final_time - initial_time > 0)
	{
		std::cout<<"FPS : "<<frame_count/(final_time - initial_time) <<std::endl;
		frame_count=0;
		initial_time=final_time;
	}
}
//----------------------------------------key control settings-------------------------------------------------
void ButtonDown(unsigned char key , int x, int y)	//button press	
{					
	if (key == 'a') { Keys.a = 1; }
	if (key == 'd') { Keys.d = 1; }
	if (key == 'w') { Keys.w = 1; }
	if (key == 's') { Keys.s = 1; }
	if (key == 'e')									//open doors function
	{
		int xo = 0; if (pdx < 0) { xo = -25; }
		else { xo = 25; }
		int yo = 0; if (pdy < 0) { yo = -25; }
		else { yo = 25; }
		int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0;
		int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0;		
		if (mapW[ipy_add_yo * mapX + ipx_add_xo] == 51)(mapW[ipy_add_yo * mapX + ipx_add_xo] = 0); 
	};												//door function texture number
	glutPostRedisplay();
}
void ButtonUp(unsigned char key, int x, int y)		//button release		
{					
	if (key == 'a') { Keys.a = 0; }
	if (key == 'd') { Keys.d = 0; }
	if (key == 'w') { Keys.w = 0; }
	if (key == 's') { Keys.s = 0; }
	if (Keys.w == 0 && timer > 0)					//sprint cooldown
	{
		sprint = 1;
		if (timer > 100 + timer/4)					//time between button presses
		{
			sprint = 0;
			timer = 0;
		}
	}
	glutPostRedisplay();
}
void resize(int w, int h)
{
	glutReshapeWindow(960, 640);
}
int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(960, 640);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - 960 / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - 640 / 2);
	glutCreateWindow("DarrensProject");
	//LoadTexture("tex.bmp");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(ButtonDown);
	glutKeyboardUpFunc(ButtonUp);
	glutMainLoop();
};