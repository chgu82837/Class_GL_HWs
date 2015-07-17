/***************************
4101056017 邱冠喻 第2次作業 4/6
4101056017 Chiu Guan-Yu TheSecondHomework 4/6
***************************/

#include "stdafx.h"

const float blue[] = {0.2862745098039216,0.5411764705882353,0.8549019607843137};
const float red[] = {0.9490196078431373,0.3176470588235294,0.3333333333333333};
const float yellow[] = {0.9215686274509804,0.9529411764705882,0.2470588235294118};
const float green[] = {0.2588235294117647,0.9411764705882353,0.3450980392156863};

const float orange[] = {1.0, 0.7607843137, 0.4745098039};
const float purple[] = {0.7803921569, 0.4980392157, 0.9019607843};
const float cyan[] = {0.4980392157, 0.9019607843, 0.862745098};

const int w_width = 400;
const int w_height = 400;

#define ByGlDrawArrays 0
#define ByGlDrawElements 1
#define ByGlMultiDrawArrays 2
#define ByGlMultiDrawElements 3

int drawing_method = ByGlDrawArrays;

char* drawing_method_name[] = {"ByGlDrawArrays","ByGlDrawElements","ByGlMultiDrawArrays","ByGlMultiDrawElements"};

GLubyte indice[] = {0,1,2,3};
GLvoid* indiX[] = {indice};
GLint first[] = {0};
GLint count[] = {4};

void gen_ret(float top,float bot,float left,float right,const float* color)
{
	GLfloat intertwined[] = {
		color[0],color[1],color[2],left,top,0.0,
		color[0],color[1],color[2],right,top,0.0,
		color[0],color[1],color[2],right,bot,0.0,
		color[0],color[1],color[2],left,bot,0.0,
	};

	glInterleavedArrays (GL_C3F_V3F, 0, intertwined);
	switch(drawing_method){
	case ByGlDrawArrays:
		glDrawArrays(GL_POLYGON,0,4);
		break;
	case ByGlDrawElements:
		glDrawElements(GL_POLYGON,4,GL_UNSIGNED_BYTE,indice);
		break;
	case ByGlMultiDrawArrays:
#ifdef __APPLE__
        printf("Not supported in OSX!\n");
#else
		glMultiDrawArrays(GL_POLYGON,first,count,1);
#endif
		break;
	case ByGlMultiDrawElements:
#ifdef __APPLE__
        printf("Not supported in OSX!\n");
#else
		glMultiDrawElements(GL_POLYGON,count,GL_UNSIGNED_BYTE,indiX,1);
#endif
		break;
	}

}

void gen_circle(float x,float y,float w,float r,float d1,float d2,int step,const float* color)
{
	float dd = (d2 - d1) / step;

	float v1[] = {r,0.0,0.0};
	float v2[] = {r+w,0.0,0.0};
	float v3[] = {(r+w) * cos(dd * M_PI / 180),(r+w) * sin(dd * M_PI / 180),0.0};
	float v4[] = {r * cos(dd * M_PI / 180),r * sin(dd * M_PI / 180),0.0};

	GLfloat intertwined[] = {
		color[0],color[1],color[2],r,0.0,0.0,
		color[0],color[1],color[2],r+w,0.0,0.0,
		color[0],color[1],color[2],(r+w) * cos(dd * M_PI / 180),(r+w) * sin(dd * M_PI / 180),0.0,
		color[0],color[1],color[2],r * cos(dd * M_PI / 180),r * sin(dd * M_PI / 180),0.0,
	};

	glInterleavedArrays (GL_C3F_V3F, 0, intertwined);
	
	glPushMatrix();
	glTranslatef(x,y,0.0);
	glRotatef(d1,0.0,0.0,1.0);

	switch(drawing_method){
	case ByGlDrawArrays:
		for(int i = 0; i < step; i++){
			glDrawArrays(GL_POLYGON,0,4);
			glRotatef(dd,0.0,0.0,1.0);
		}
		break;
	case ByGlDrawElements:
		for(int i = 0; i < step; i++){
			glDrawElements(GL_POLYGON,4,GL_UNSIGNED_BYTE,indice);
			glRotatef(dd,0.0,0.0,1.0);
		}
		break;
	case ByGlMultiDrawArrays:
		for(int i = 0; i < step; i++){
#ifdef __APPLE__
            printf("Not supported in OSX!\n");
#else
			glMultiDrawArrays(GL_POLYGON,first,count,1);
#endif
			glRotatef(dd,0.0,0.0,1.0);
		}
		break;
	case ByGlMultiDrawElements:
		for(int i = 0; i < step; i++){
#ifdef __APPLE__
            printf("Not supported in OSX!\n");
#else
			glMultiDrawElements(GL_POLYGON,count,GL_UNSIGNED_BYTE,indiX,1);
#endif
			glRotatef(dd,0.0,0.0,1.0);
		}
		break;
	}

	glPopMatrix();
}

int x_r = 0;
int z_r = 0;
int each_r = 0;

int fps = 0;
int t;

float ecampus_z = -1.0;
float ecampus_x = 0.0;

void ecampus()
{
	// e
	glPushMatrix();
	// glColor3fv(cyan);
	glTranslatef(70.0,90.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,-315.0,60,cyan);
	gen_ret(-5.0,5.0,-30.0,30.0,cyan);
	glPopMatrix();

	// C
	glPushMatrix();
	// glColor3fv(purple);
	glTranslatef(140,70.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,20.0,30.0,75.0,285.0,60,purple);
	glPopMatrix();

	// a
	glPushMatrix();
	// glColor3fv(orange);
	glTranslatef(175.0,100.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,7.0,15.0,0.0,360.0,60,orange);
	gen_circle(0.0,-15.0,7.0,15.0,0.0,-145.0,60,orange);
	gen_ret(-15.0,22.0,15.0,22.0,orange);
	glPopMatrix();

	// m
	glPushMatrix();
	// glColor3fv(green);
	glTranslatef(225.0,100.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_ret(-35.5,22.0,-23.5,-16.5,green);
	gen_circle(-10,-22.0,7.0,6.5,-180.0,0.0,10,green);
	gen_ret(-22.0,22.0,-3.5,3.5,green);
	gen_circle(10,-22.0,7.0,6.5,-180.0,0.0,10,green);
	gen_ret(-22.0,22.0,23.5,16.5,green);
	glPopMatrix();

	// p
	glPushMatrix();
	// glColor3fv(cyan);
	glTranslatef(280.0,90.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,-360.0,60,cyan);
	gen_ret(-30.0,70.0,-30.0,-20.0,cyan);
	glPopMatrix();

	// u
	glPushMatrix();
	// glColor3fv(purple);
	glTranslatef(335.0,90.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_ret(-30.0,0.0,-20.0,-30.0,purple);
	gen_circle(0.0,0.0,10.0,20.0,180.0,0.0,30,purple);
	gen_ret(-30.0,30.0,20.0,30.0,purple);
	glPopMatrix();

	// s
	glPushMatrix();
	// glColor3fv(orange);
	glTranslatef(385.0,90.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,-13.5,7.0,10.0,-45.0,-270.0,30,orange);
	gen_circle(0.0,13.5,7.0,10.0,-90.0,135.0,30,orange);
	glPopMatrix();
}

void google()
{
	// G
	glPushMatrix();
	// glColor3fv(blue);
	glTranslatef(70.0,90.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,40.0,-45.0,-360.0,60,blue);
	gen_ret(-5.0,5.0,20.0,50.0,blue);
	glPopMatrix();

	// o
	glPushMatrix();
	// glColor3fv(red);
	glTranslatef(150.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,360.0,60,red);
	glPopMatrix();

	// o
	glPushMatrix();
	// glColor3fv(yellow);
	glTranslatef(210.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,360.0,60,yellow);
	glPopMatrix();

	// g
	glPushMatrix();
	// glColor3fv(blue);
	glTranslatef(270.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,360.0,60,blue);
	gen_circle(0.0,60.0,7.0,17.0,0.0,360.0,60,blue);
	gen_ret(25.0,40.0,0.0,10.0,blue);
	gen_ret(-30.0,-20.0,0.0,30.0,blue);
	glPopMatrix();

	// l
	glPushMatrix();
	// glColor3fv(green);
	glTranslatef(310.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_ret(-65,30,-5,5,green);
	glPopMatrix();

	// e
	glPushMatrix();
	// glColor3fv(red);
	glTranslatef(350.0,110.0,0);
	glRotatef((float) each_r,0.0,1.0,0.0);
	gen_circle(0.0,0.0,10.0,20.0,0.0,-315.0,60,red);
	gen_ret(-5.0,5.0,-30.0,30.0,red);
	glPopMatrix();
}

bool muted = false;

void display(void)
{
	if(t != time(NULL)){
		if(!muted)
			printf("displaying at FPS: %d\n",fps);
		fps = 1;
		t = time(NULL);
	}
	else
		fps++;

	/* clear all pixels  */
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt ((float) w_width/2,(float) w_height/2, 3.0, (float) w_width/2,(float) w_height/2, 0.0, 0.0, 1.0, 0.0);

	glColor3f(1.0,1.0,1.0);
	
	glTranslatef((float) w_width/2,(float) w_height/2,0.0);
	glRotatef((float) z_r,0.0,0.0,1.0);
	glRotatef((float) x_r,1.0,0.0,0.0);
	glTranslatef((float) -w_width/2,(float) -w_height/2,0.0);

	glPushMatrix();
	glTranslatef(0.0,90.0,0.0);
	google();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.0 + ecampus_x,90.0,ecampus_z);
	ecampus();
	glPopMatrix();

	glutSwapBuffers();
	glFlush ();

	// printf("display called\n");
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
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	// printf("%c (code %d) is released!\n",key,key);
	if(key >= '1' && key <= '4'){
		drawing_method = key - '1';
		printf("Drawing method changed to %s!\n",drawing_method_name[drawing_method]);
	}
	else{
		switch (key)
		{
		case 'w':
			ecampus_z -= 0.5;
			break;
		case 's':
			ecampus_z += 0.5;
			break;
		case 'a':
			ecampus_x -= 10.0;
			break;
		case 'd':
			ecampus_x += 10.0;
			break;
		case 'm':
			muted = !muted;
			if(muted) printf("muted\n");
			return;
			break;
		default:
			break;
		}
		printf("eCampus position has changed to (%f,0.0,%f)!\n",ecampus_x,ecampus_z);
	}
}

void reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum (-w/2, w/2, h/2, -h/2, 2.0, 120.0);
	glMatrixMode (GL_MODELVIEW);
	printf("reshape called\n");
	display();
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

	/* enable depth test */
	glShadeModel (GL_FLAT);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);

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

	printf("Init OK!\nUsage:\n\n\tRight Click to rotate by x-axis\n\tLeft Click to rotate by z-axix\n\tMiddle Click to rotate each character\n\tRight + Left Click to reset rotation\n\tKeyboard `w` to Move the “eCampus” away\n\tKeyboard `a` to Move the “eCampus” to left\n\tKeyboard `s` to Move the “eCampus” to camera\n\tKeyboard `d` to Move the “eCampus” to right\n\tKeyboard `1` to Use glDrawArrays() when drawing\n\tKeyboard `2` to Use glDrawElements() when drawing\n\tKeyboard `3` to Use glMultiDrawArrays() when drawing\n\tKeyboard `4` to Use glMultiDrawElements() when drawing\n\tKeyboard `m` to mute the FPS message");

	/* start to display */
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	glutKeyboardUpFunc(keyboard);
	glutMainLoop();
	return 0;
}

/***************************
4101056017 邱冠喻 第2次作業 4/6
4101056017 Chiu Guan-Yu TheSecondHomework 4/6
***************************/
