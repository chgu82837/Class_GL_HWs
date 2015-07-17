/***************************
4101056017 邱冠喻 第4次作業 5/11
4101056017 Chiu Guan-Yu TheFourthHomework 5/11
***************************/

#include "stdafx.h"

// == Color control ==

const float colors[] =
{
    0.9490196078431373, 0.3176470588235294, 0.3333333333333333, 1.0, /* red */
    0.6392156863000000, 0.6392156863000000, 0.6392156863000000, 1.0, /* gray */
    0.6000000000000000, 0.6000000000000000, 0.8000000000000000, 1.0, /* lavender */
    0.2862745098039216, 0.5411764705882353, 0.8549019607843137, 1.0, /* blue */
    0.9490196078431373, 0.3176470588235294, 0.3333333333333333, 1.0, /* red */
    0.9215686274509804, 0.9529411764705882, 0.2470588235294118, 1.0, /* yellow */
    1.0000000000000000, 0.7607843137000000, 0.4745098039000000, 1.0, /* orange */
    0.2588235294117647, 0.9411764705882353, 0.3450980392156863, 1.0, /* green */
    0.4980392157000000, 0.9019607843000000, 0.8627450980000000, 1.0, /* cyan */
    0.7803921569000000, 0.4980392157000000, 0.9019607843000000, 1.0, /* purple */
};

int color_i = 0;
void nextColor()
{
    static int color_size = sizeof(colors) / sizeof(float) / 4;
    // glColor3fv(colors + color_i * 3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors + color_i * 4);
    color_i = (color_i + 1) % color_size;
}

void setColorI(int index)
{
    color_i = index;
}

int getColorI()
{
    return color_i;
}

GLfloat light_position_origin[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat local_view[] = { 0.0 };

GLfloat no_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat sun_diffuse[] = { 0.9490196078431373, 0.3176470588235294, 0.33333333333333330, 1.0};
GLfloat head_diffuse[] = { 0.9215686274509804, 0.9529411764705882, 0.247058823529411, 1.0};

GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat mat_shininess[] = { 10.0 };
// GLfloat no_shininess[] = { 0.0 };

void init_light()
{
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glLightfv(GL_LIGHT0, GL_AMBIENT, no_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);

    glLightfv(GL_LIGHT1, GL_AMBIENT, no_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, head_diffuse);

    glMaterialfv(GL_FRONT, GL_AMBIENT, lmodel_ambient);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); as the main color
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void sun_mode(bool enable)
{
	const static GLfloat red[] = { 0.9490196078431373, 0.3176470588235294, 0.3333333333333333, 1.0};
	if(enable){
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_EMISSION, red);
	}
	else{
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	}
}

// =================

void draw_arm(GLfloat d1, GLfloat d2, GLfloat d3, GLfloat thick_d)
{
    // glPushMatrix();

    GLfloat thick = 1;

    glRotatef (d1, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);

    glPushMatrix();
    glScalef (2.0, thick -= thick_d, 1.0);
    draw_obj();
    glPopMatrix();

    glTranslatef (1.0, 0.0, 0.0);
    glRotatef (d2, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);

    glPushMatrix();
    glScalef (2.0, thick -= thick_d, 1.0);
    draw_obj();
    glPopMatrix();

    glTranslatef (1.0, 0.0, 0.0);
    glRotatef (d3, 0.0, 0.0, 1.0);
    glTranslatef (0.5, 0.0, 0.0);

    glPushMatrix();
    glScalef (1.0, thick -= thick_d, 1.0);
    draw_obj();
    glPopMatrix();

    // glPopMatrix(); // Keep the last state
}

// == use state to choose sphere or cube ==

bool use_sphere = false;

bool get_obj_type()
{
    return use_sphere;
}

void set_obj_type(bool is_sphere)
{
    use_sphere = is_sphere;
}

void draw_obj()
{
    if(use_sphere) glutSolidSphere(0.75, 30, 30);
    else glutSolidCube (1.0);
}

// ========================================
bool muted = true;

bool keyStates[256] = {0}; // 0 for mouse left, 1 for mouse right, 2 for mouse middle
character user(false, 3.0, 0, 0, HAND_WEAPONTYPE_NONE, HAND_WEAPONTYPE_SOLAR,0,false);
character mon0(true, -3.0, -3.0, 180, HAND_WEAPONTYPE_NONE, HAND_WEAPONTYPE_STICK, 0,true);
character mon1(true, -3.0, 0.0, 180, HAND_WEAPONTYPE_NONE, HAND_WEAPONTYPE_STICK, 0,true);
character mon2(true, -3.0, 3.0, 180, HAND_WEAPONTYPE_NONE, HAND_WEAPONTYPE_STICK, 0,true);
character* mon[] = {&mon0, &mon1, &mon2};
looper sun(-90.0, 90.0, 2880, 0.0, LOOPER_TRUN_BACK, LOOPER_AUTO_ENABLE);

void display(void)
{
    static int t;
    static int fps;
    if(t != time(NULL))
    {
        if(!muted) printf("displaying at FPS: %d\n", fps);
        fps = 1;
        t = time(NULL);
    }
    else
        fps++;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if(keyStates['d']) user.move(0.0, 0.05, 0.0);
    if(keyStates['a']) user.move(0.0, -0.05, 0.0);
    if(keyStates['w']) user.move(-0.05, 0.0, 0.0);
    if(keyStates['s']) user.move(0.05, 0.0, 0.0);
    if(keyStates[' ']) user.jump();
    if(keyStates[0]) user.move(0.0, 0.0, -2.5);
    if(keyStates[1]) user.move(0.0, 0.0, 2.5);
    if(keyStates['1']) user.right->sun_r->next();
    if(keyStates['2']) user.right->planet_d->next();
    if(keyStates['3']) user.right->sate_d->next();
    if(keyStates['4']) user.right->thumb->next();
    if(keyStates['5']) user.right->wrist->next();
    if(keyStates['6']) user.right->elbow->next();

    user.mount();

    glPushMatrix();
    glRotatef(sun, 0.0, 0.0, 1.0);
    glTranslatef(0.0,10.0,0.0);
    set_obj_type(true);
	sun_mode(true);
    draw_obj();
	sun_mode(false);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position_origin);
    glPopMatrix();

    glPushMatrix(); // The ground =====

	setColorI(0);
	nextColor();
    glTranslatef(0.0, -2.0, 0.0);
    glRotatef (-90, 1.0, 0.0, 0.0);
    glRectf (10.0, 10.0, -10.0, -10.0);

    glPopMatrix(); // =================

    user.draw();

	for (int i = 0; i < MON_N; i++)
	{
		mon[i]->draw();
	}

    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(90.0, (GLfloat) w / (GLfloat) h, 0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}

int last_detec = 0;

void keyboard (unsigned char key, int x, int y)
{
    keyStates[key] = true;

    switch(key)
    {
    case 27:
        exit(0);
        break;
    case 'l':
        glEnable(GL_LIGHT1);
        break;
	case 'z':
		user.leftAttack(*mon);
		break;
	case 'x':
		user.rightAttack(*mon);
		break;
    }
}

void keyup(unsigned char key, int x, int y)
{
    keyStates[key] = false;
}

void mouse(int button, int state, int x, int y)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(!muted) printf("Left key");
        keyStates[0] = state == GLUT_DOWN;
        break;
    case GLUT_RIGHT_BUTTON:
        if(!muted) printf("Right key");
        keyStates[1] = state == GLUT_DOWN;
        break;
    case GLUT_MIDDLE_BUTTON:
        if(!muted) printf("Middle key");
        keyStates[2] = state == GLUT_DOWN;
        break;
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    // glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    init_light();
    glEnable(GL_DEPTH_TEST);

    // Manual
    printf("");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyup);
    glutMouseFunc(mouse);
    glutIdleFunc((void (*)()) glutPostRedisplay);
    glutMainLoop();
    return 0;
}

/***************************
4101056017 邱冠喻 第4次作業 5/11
4101056017 Chiu Guan-Yu TheFourthHomework 5/11
***************************/
