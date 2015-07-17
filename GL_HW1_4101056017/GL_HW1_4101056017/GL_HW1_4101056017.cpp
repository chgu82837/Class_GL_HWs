/***************************
4101056017 邱冠喻 第一次作業 3/23
4101056017 Chiu Guan-Yu TheFirstHomework 3/23
***************************/

#include "stdafx.h"

const float blue[] = {0.2862745098039216,0.5411764705882353,0.8549019607843137};
const float red[] = {0.9490196078431373,0.3176470588235294,0.3333333333333333};
const float yellow[] = {0.9215686274509804,0.9529411764705882,0.2470588235294118};
const float green[] = {0.2588235294117647,0.9411764705882353,0.3450980392156863};

const int w_width = 400;
const int w_height = 400;
const float drawing_origin[] = {0.0,90.0,0.0};

void gen_ret(float top,float bot,float left,float right)
{
	glBegin(GL_POLYGON);
		glVertex3f(left,top,0.0);
		glVertex3f(right,top,0.0);
		glVertex3f(right,bot,0.0);
		glVertex3f(left,bot,0.0);
	glEnd();
}

void gen_circle(float x,float y,float w,float r,float d1,float d2,int step)
{
	float dd = (d2 - d1) / step;

	float v1[] = {r,0.0,0.0};
	float v2[] = {r+w,0.0,0.0};
	float v3[] = {(r+w) * cos(dd * M_PI / 180),(r+w) * sin(dd * M_PI / 180),0.0};
	float v4[] = {r * cos(dd * M_PI / 180),r * sin(dd * M_PI / 180),0.0};

	glPushMatrix();
	glTranslatef(x,y,0.0);
	glRotatef(d1,0.0,0.0,1.0);
	for(int i = 0; i < step; i++){
		glBegin(GL_POLYGON);
			glVertex3fv(v1);
			glVertex3fv(v2);
			glVertex3fv(v3);
			glVertex3fv(v4);
		glEnd();

		glRotatef(dd,0.0,0.0,1.0);
	}
	glPopMatrix();
}

int x_r = 0;
int z_r = 0;
int each_r = 0;

int fps = 0;
int t;

void display(void)
{
	if(t != time(NULL)){
		printf("displaying at FPS: %d\n",fps);
		fps = 1;
		t = time(NULL);
	}
	else
		fps++;

	/* clear all pixels  */
	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef((float) w_width/2,(float) w_height/2,0.0);
	glRotatef((float) z_r,0.0,0.0,1.0);
	glRotatef((float) x_r,1.0,0.0,0.0);
	glTranslatef((float) -w_width/2,(float) -w_height/2,0.0);

	glTranslatef(drawing_origin[0],drawing_origin[1],drawing_origin[2]);

	// G
	glPushMatrix();
	glColor3fv(blue);
	glTranslatef(70.0,90.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,40.0,-45.0,-360.0,60);
	gen_ret(-5.0,5.0,20.0,50.0);
	glPopMatrix();

	// o
	glPushMatrix();
	glColor3fv(red);
	glTranslatef(150.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,360.0,60);
	glPopMatrix();

	// o
	glPushMatrix();
	glColor3fv(yellow);
	glTranslatef(210.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,360.0,60);
	glPopMatrix();

	// g
	glPushMatrix();
	glColor3fv(blue);
	glTranslatef(270.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,360.0,60);
	gen_circle(0.0,60.0,7.0,17.0,0.0,360.0,60);
	gen_ret(25.0,40.0,0.0,10.0);
	gen_ret(-30.0,-20.0,0.0,30.0);
	glPopMatrix();

	// l
	glPushMatrix();
	glColor3fv(green);
	glTranslatef(310.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_ret(-65,30,-5,5);
	glPopMatrix();

	// e
	glPushMatrix();
	glColor3fv(red);
	glTranslatef(350.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,-315.0,60);
	gen_ret(-5.0,5.0,-30.0,30.0);
	glPopMatrix();

	glutSwapBuffers();
	// glFlush ();
}

int x_rd = 0;
int z_rd = 0;
int each_rd = 0;

void update()
{
	(x_r += x_rd) >= 360 ? x_r -= 360 : x_r;
	(z_r += z_rd) >= 360 ? z_r -= 360 : z_r;
	(each_r += each_rd) >= 360 ? each_r -= 360 : each_r;
	glutPostRedisplay();
}

int reset_s = 0;

void mouse(int button, int state, int x, int y)
{
	printf("Mouse: ");
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		printf("Left key");
		z_rd = (z_rd + 1) % 6;
		break;
	case GLUT_RIGHT_BUTTON:
		printf("Right key");
		x_rd = (x_rd + 1) % 6;
		break;
	case GLUT_MIDDLE_BUTTON:
		printf("Middle key");
		each_rd = (each_rd + 1) % 6;
		break;
	}
	switch(state)
	{
	case GLUT_UP:
		printf(" Up");
		if(reset_s == 3)
			reset_s = 4;
		else if(reset_s == 4){
			reset_s = -1;
			x_r = 0;
			z_r = 0;
			each_r = 0;
			x_rd = 0;
			z_rd = 0;
			each_rd = 0;
		}
		else
			reset_s--;
		break;
	case GLUT_DOWN:
		printf(" Down");

		reset_s++;
		if(reset_s == 2)
			reset_s = 3;
		break;
	}
	printf(" At x:%d y:%d\nRotating x at %d / z at %d / each at %d\n",x,y,x_rd,z_rd,each_rd);
	if(reset_s == -1){
		printf("All rotation has been reset!\n");
		reset_s = 0;
		glutIdleFunc(NULL);
		glutPostRedisplay();
	}
	else
		glutIdleFunc(update);
}

int main(int argc, char* argv[])
{
	glutInit(&argc,argv);

	/* init the window */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(w_width,w_height);
	glutCreateWindow("GL_HW1_4101056017");

	/* get info */
	printf( "OpenGL version: %s\n", (char*)glGetString(GL_VERSION));
	printf( "OpenGL renderer: %s\n", (char*)glGetString(GL_RENDERER));

	/* select clearing color */
	glClearColor (0.0, 0.0, 0.0, 0.0);

	/* initialize viewing values */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,(float) w_width,(float) w_height,0.0,-1.0,1.0);

	/* glew init */
#ifdef __APPLE__
#else
	glewInit();
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Failed to init glew! Exiting...");
		return 255;
	}
	printf("Using GLEW Version: %s\n", glewGetString(GLEW_VERSION));
#endif

	t = time(NULL);

	printf("Init OK!\nUsage:\n\n\tRight Click to rotate by x-axis\n\tLeft Click to rotate by z-axix\n\tMiddle Click to rotate each character\n\tRight + Left Click to reset rotation\n");

	/* start to display */
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}

/***************************
4101056017 邱冠喻 第一次作業 3/23
4101056017 Chiu Guan-Yu TheFirstHomework 3/23
***************************/
