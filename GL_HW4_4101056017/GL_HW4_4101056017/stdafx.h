
#ifdef __APPLE__

#include <GL/glew.h>
#include <GLUT/glut.h>
#include <cstdlib>

#else

#pragma once

#include "targetver.h"

#include <tchar.h>
#include "GL/glew.h"
#include "GL/glut.h"

#endif

#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

// ============

#define X_MAX 10.0
#define X_MIN -10.0
#define Z_MAX 10.0
#define Z_MIN -10.0
#define MON_N 3

void draw_arm(GLfloat d1, GLfloat d2, GLfloat d3, GLfloat thick_d);
bool get_obj_type();
void set_obj_type(bool is_sphere);
void draw_obj();
void nextColor();
void setColorI(int index);
int getColorI();
void sun_mode(bool enable);

class looper;
class hand;
class character;

#include "looper.h"
#include "hand.h"
#include "character.h"
