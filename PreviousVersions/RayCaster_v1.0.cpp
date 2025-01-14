#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>
typedef struct
{
	int w, a, d, s;		//button state on off
} ButtonKeys; ButtonKeys Keys;

int All_Textures[] =	//all 32x32 textures
{
	//checkerboard
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,	0,0,0,0,0,0,0,0,

	//swastika

	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,0,0,0,0,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,0,0,0,0,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,0,0,0,0,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,0,0,0,0,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,

	0,0,0,0,1,1,1,1,	1,0,0,0,0,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,0,0,0,0,1,1,1,	1,1,1,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,0,0,0,0,1,1,1,	1,1,1,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,0,0,0,0,1,1,1,	1,1,1,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,0,0,0,0,1,1,1,	1,1,1,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,

	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,1,1,1,	1,1,1,0,0,0,0,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,1,1,1,	1,1,1,0,0,0,0,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,1,1,1,	1,1,1,0,0,0,0,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,1,1,1,	1,1,1,0,0,0,0,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,0,0,0,0,1,	1,1,1,1,0,0,0,0,

	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,0,0,0,0,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,0,0,0,0,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,0,0,0,0,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,0,0,0,0,1,	1,1,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,

	//door
	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,0,0,0,	0,0,1,1,1,1,1,0,	0,0,1,1,1,1,0,0,	0,0,0,1,1,1,1,0,
	0,1,1,1,0,0,0,0,	0,0,0,1,1,1,1,0,	0,0,1,1,1,0,0,0,	0,0,0,0,1,1,1,0,
	0,1,1,0,0,0,0,0,	0,0,0,0,1,1,1,0,	0,0,1,1,0,0,0,0,	0,0,0,0,0,1,1,0,
	0,1,1,0,0,0,0,0,	0,0,0,0,1,1,1,0,	0,0,1,1,0,0,0,0,	0,0,0,0,0,1,1,0,
	0,1,1,0,0,0,0,0,	0,0,0,0,1,1,1,0,	0,0,1,1,0,0,0,0,	0,0,0,0,0,1,1,0,

	0,1,1,0,0,0,0,0,	0,0,0,0,1,1,1,0,	0,0,1,1,0,0,0,0,	0,0,0,0,0,1,1,0,
	0,1,1,1,0,0,0,0,	0,0,0,1,1,1,1,0,	0,0,1,1,1,0,0,0,	0,0,0,0,1,1,1,0,
	0,1,1,1,1,0,0,0,	0,0,1,1,1,1,1,0,	0,0,1,1,1,1,0,0,	0,0,0,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,0,0,0,	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,0,0,0,	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,0,

	0,1,1,1,1,1,1,1,	1,1,1,1,1,0,1,0,	0,0,1,0,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,0,1,0,	0,0,1,0,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,0,1,0,	0,0,1,0,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,0,0,0,	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,0,0,0,	0,0,0,0,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,

	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,	0,0,1,1,1,1,1,1,	1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,

	//brick
	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,

	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,

	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	1,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,	1,1,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,

	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,	0,0,0,0,1,0,0,0,
	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,	0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,1,0,0,0,0,0,0,
	1,0,0,0,0,0,0,1,	0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,1,	0,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0,	1,0,0,0,0,0,0,0

};

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533	//one degree in radians

//-----------------------------------------------------MAP---------------------------------------------------
#define mapX 8			//map width
#define mapY 8			//map height
#define mapS 64			//map cube size
int mapW[] =			//walls
{
	4,4,4,4,4,4,4,4,
	4,0,0,4,0,0,0,4,
	4,0,0,3,0,0,0,4,
	4,3,4,4,4,3,4,4,
	2,0,4,0,0,0,0,4,
	4,4,4,0,0,0,0,4,
	4,0,0,0,0,0,0,4,
	4,4,4,4,4,4,4,4,
};
int mapF[] =			//floors
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
};
int mapC[] =			//ceiling
{
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
};
void drawMap2D()
{
	int x, y, xo, yo;
	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			if (mapW[y * mapX + x] > 0) { glColor3f(1, 1, 1); }
			else { glColor3f(0, 0, 0); }
			xo = x * mapS; yo = y * mapS;
			glBegin(GL_QUADS);
			glVertex2i(xo + 1, yo + 1);
			glVertex2i(xo + 1, yo + mapS - 1);
			glVertex2i(xo + mapS - 1, yo + mapS - 1);
			glVertex2i(xo + mapS - 1, yo + 1);
			glEnd();
		}
	}
}
//----------------------------------------------Player--------------------------------------------------
float degToRad(float a) { return a * M_PI / 180.0; }
float FixAng(float a) { if (a > 359) { a -= 360; } if (a < 0) { a += 360; } return a; }
float px, py, pdx, pdy, pa;	//player position, p-x, p-y, p-delta x, p-delta y, & p-angle

void drawPlayer()
{
	glColor3f(1, 1, 0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(px, py);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(px, py);
	glVertex2i(px + pdx * 20, py + pdy * 20);
	glEnd();
}
//----------------------------------------------Draw Rays and Walls--------------------------------------------------
float dist(float ax, float ay, float bx, float by, float ang) { return cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay); }

void drawRays3D()
{
	glColor3f(0.1, 0.1, 0.1); glBegin(GL_QUADS); glVertex2i(526, 0); glVertex2i(1006, 0); glVertex2i(1006, 160); glVertex2i(526, 160); glEnd();
	//Hud /background colour
	glColor3f(0.3, 0.3, 0.3); glBegin(GL_QUADS); glVertex2i(526, 160); glVertex2i(1006, 160); glVertex2i(1006, 320); glVertex2i(526, 320); glEnd();

	int r, mx, my, mp, dof, side; float vx, vy, rx, ry, ra, xo, yo, disV, disH, disT{};
	ra = FixAng(pa + 30);
	for (r = 0; r < 60; r++)		//set ray back 30 degrees
	{
		int vmt = 0, hmt = 0;	//vertical and horizontal map texture number
		//---check vertical lines---
		dof = 0; side = 0; disV = 1000000;
		float Tan = tan(degToRad(ra));
		if (cos(degToRad(ra)) > 0.0001) { rx = (((int)px >> 6) << 6) + 64;		ry = (px - rx) * Tan + py; xo = 64; yo = -xo * Tan; }//looking left
		else if (cos(degToRad(ra)) < -0.0001) { rx = (((int)px >> 6) << 6) - 0.0001;   ry = (px - rx) * Tan + py; xo = -64; yo = -xo * Tan; }//looking right
		else { rx = px; ry = py; dof = 8; }													//looking straight up or down

		while (dof < 8)
		{
			mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapW[mp]>0) { vmt = mapW[mp] - 1; dof = 8; disV = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py); }//hit wall
			else { rx += xo; ry += yo; dof += 1; }//Next line
		}
		vx = rx; vy = ry;

		//---check horizontal lines---
		dof = 0; disH = 1000000,
			Tan = 1.0 / Tan;
		if (sin(degToRad(ra)) > 0.001) { ry = (((int)py >> 6) << 6) - 0.0001; rx = (py - ry) * Tan + px; yo = -64; xo = -yo * Tan; }//looking up
		else if (sin(degToRad(ra)) < -0.001) { ry = (((int)py >> 6) << 6) + 64;	 rx = (py - ry) * Tan + px; yo = 64; xo = -yo * Tan; }//looking down
		else { rx = px; ry = py; dof = 8; }																//looking straight left or right
		while (dof < 8)
		{
			mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapW[mp]>0) { hmt = mapW[mp] - 1; dof = 8; disH = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py); }//hit wall
			else { rx += xo; ry += yo; dof += 1; }//Next line
		}
		float shade = 1;
		glColor3f(0.8, 0, 0);
		if (disV < disH) { hmt = vmt; shade = 0.7; rx = vx; ry = vy; disH = disV; glColor3f(0.6, 0, 0); }		//horizontal wall hit
		glLineWidth(0); glBegin(GL_LINES); glVertex2i(px, py); glVertex2i(rx, ry); glEnd();//draw 2d ray

		int ca = FixAng(pa - ra); disH = disH * cos(degToRad(ca));						//fix fisheye
		int lineH = (mapS * 320) / (disH);
		float ty_step = 32.00 / (float)lineH;
		float ty_off = 0;
		if (lineH > 320) { ty_off = (lineH - 320) / 2.0; lineH = 320; }						//line height
		int lineO = 160 - (lineH >> 1);											//Line offset

		//---Draw 3D Walls---
		int y;
		float ty = ty_off * ty_step + hmt * 32;
		float tx;
		if (shade == 1) { tx = (int)(rx / 2.0) % 32; if (ra > 180) { tx = 31 - tx; } }
		else { tx = (int)(ry / 2.0) % 32; if (ra > 90 && ra < 270) { tx = 31 - tx; } }
		for (y = 0; y < lineH; y++)
		{
			float c = All_Textures[(int)(ty) * 32 + (int)(tx)] * shade;
			if (hmt == 0) { glColor3f(c, c / 2.0, c / 2.0); }	//checker
			if (hmt == 1) { glColor3f(1, c, c); }			//swastika
			if (hmt == 2) { glColor3f(0, c, c / 0.2); }		//doors
			if (hmt == 3) { glColor3f(0.4, c / 2.5, c / 2.0); }	//brick
			glPointSize(8); glBegin(GL_POINTS); glVertex2i(r * 8 + 530, y + lineO); glEnd();
			ty += ty_step;
		}
		//------Draw floors----------
		for (y = lineO + lineH; y < 320; y++)
		{
			float dy = y - (320 / 2.0), deg = degToRad(ra), raFix = cos(degToRad(FixAng(pa - ra)));
			tx = px / 2 + cos(deg) * 158 * 32 / dy / raFix;
			ty = py / 2 - sin(deg) * 158 * 32 / dy / raFix;
			int mp = mapF[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
			float c = All_Textures[((int)(ty) & 31) * 32 + ((int)(tx) & 31) + mp] * 0.7;
			glColor3f(c, c, c); glPointSize(8); glBegin(GL_POINTS); glVertex2i(r * 8 + 530, y); glEnd();

			//Draw ceiling
			mp = mapC[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
			c = All_Textures[((int)(ty) & 31) * 32 + ((int)(tx) & 31) + mp] * 0.7;
			glColor3f(0.2, c / 3, c / 3); glPointSize(8); glBegin(GL_POINTS); glVertex2i(r * 8 + 530, 320 - y); glEnd();

		}
		ra = FixAng(ra - 1);
	}
}

float frame1, frame2, fps;

void display()
{
	//frames per second
	frame2 = glutGet(GLUT_ELAPSED_TIME); fps = (frame2 - frame1); frame1 = glutGet(GLUT_ELAPSED_TIME);

	//Buttons
	if (Keys.a == 1) { pa += 0.2 * fps; pa = FixAng(pa); pdx = cos(degToRad(pa)); pdy = -sin(degToRad(pa)); } //looking left
	if (Keys.d == 1) { pa -= 0.2 * fps; pa = FixAng(pa); pdx = cos(degToRad(pa)); pdy = -sin(degToRad(pa)); } //looking right

	int xo = 0; if (pdx < 0) { xo = -20; }
	else { xo = 20; }
	int yo = 0; if (pdy < 0) { yo = -20; }
	else { yo = 20; }
	int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0, ipx_sub_xo = (px - xo) / 64.0;
	int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0, ipy_sub_yo = (py - yo) / 64.0;
	if (Keys.w == 1)
	{
		if (mapW[ipy * mapX + ipx_add_xo] == 0) { px += pdx * 0.2 * fps; }
		if (mapW[ipy_add_yo * mapX + ipx] == 0) { py += pdy * 0.2 * fps; }
	}
	if (Keys.s == 1)
	{
		if (mapW[ipy * mapX + ipx_sub_xo] == 0) { px -= pdx * 0.2 * fps; }
		if (mapW[ipy_sub_yo * mapX + ipx] == 0) { py -= pdy * 0.2 * fps; }
	}
	glutPostRedisplay();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	drawRays3D();
	drawPlayer();
	glutSwapBuffers();
}

void ButtonDown(unsigned char key, int x, int y)
{
	if (key == 'a') { Keys.a = 1; }
	if (key == 'd') { Keys.d = 1; }
	if (key == 'w') { Keys.w = 1; }
	if (key == 's') { Keys.s = 1; }
	if (key == 'e')		//open doors
	{
		int xo = 0; if (pdx < 0) { xo = -25; }
		else { xo = 25; }
		int yo = 0; if (pdy < 0) { yo = -25; }
		else { yo = 25; }
		int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0;
		int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0;
		if (mapW[ipy_add_yo * mapX + ipx_add_xo] == 3)(mapW[ipy_add_yo * mapX + ipx_add_xo] = 0);

	};
	glutPostRedisplay();
}
void ButtonUp(unsigned char key, int x, int y)
{
	if (key == 'a') { Keys.a = 0; }
	if (key == 'd') { Keys.d = 0; }
	if (key == 'w') { Keys.w = 0; }
	if (key == 's') { Keys.s = 0; }
	glutPostRedisplay();
}

void init()
{
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 512, 0);
	px = 150; py = 400; pa = 90;
	pdx = cos(degToRad(pa)); pdy = sin(degToRad(pa));
}

void resize(int w, int h)
{
	glutReshapeWindow(1024, 512);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 512);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("DarrensProject");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(ButtonDown);
	glutKeyboardUpFunc(ButtonUp);
	glutMainLoop();
};