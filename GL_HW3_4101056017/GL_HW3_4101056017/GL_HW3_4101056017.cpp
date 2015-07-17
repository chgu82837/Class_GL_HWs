/***************************
4101056017 邱冠喻 第3次作業 4/27
4101056017 Chiu Guan-Yu TheThirdHomework 4/27
***************************/

#include "stdafx.h"
#include "looper.cpp"

looper shoulder (0, 50, 25, 20, LOOPER_TRUN_BACK);
looper elbow (0, 90, 9, 20, LOOPER_TRUN_BACK);
looper hand (-70, 50, 12, -40, LOOPER_TRUN_BACK);
looper thumb (0, 50, 5, 0, LOOPER_TRUN_BACK);
looper sun_r (0, 360, 36, 0, LOOPER_TO_LOWER);
looper planet_d (0, 360, 36, 0, LOOPER_TO_LOWER);
looper planet_r (0, 360, 36, 0, LOOPER_TO_LOWER);
looper sate_d (0, 360, 36, 0, LOOPER_TO_LOWER);
looper sate_r (0, 360, 36, 0, LOOPER_TO_LOWER);
const float colors[] =
{
    0.6392156863000000, 0.6392156863000000, 0.6392156863000000, /* gray */
    0.6000000000000000, 0.6000000000000000, 0.8000000000000000, /* lavender */
    0.2862745098039216, 0.5411764705882353, 0.8549019607843137, /* blue */
    0.9490196078431373, 0.3176470588235294, 0.3333333333333333, /* red */
    0.9215686274509804, 0.9529411764705882, 0.2470588235294118, /* yellow */
    0.2588235294117647, 0.9411764705882353, 0.3450980392156863, /* green */
    1.0000000000000000, 0.7607843137000000, 0.4745098039000000, /* orange */
    0.4980392157000000, 0.9019607843000000, 0.8627450980000000, /* cyan */
    0.7803921569000000, 0.4980392157000000, 0.9019607843000000, /* purple */
};

void nextColor()
{
    static int color_i = 0;
    static int color_size = sizeof(colors) / sizeof(float) / 3;
    glColor3fv(colors + color_i * 3);
    color_i = (color_i + 1) % color_size;
}

void gen_arm(GLfloat d1, GLfloat d2, GLfloat d3, GLfloat thick_d)
{
    // glPushMatrix();

    GLfloat thick = 1;

    glRotatef (d1, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);

    glPushMatrix();
    glScalef (2.0, thick -= thick_d, 1.0);
    glutWireCube (1.0);
    glPopMatrix();

    glTranslatef (1.0, 0.0, 0.0);
    glRotatef (d2, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);

    glPushMatrix();
    glScalef (2.0, thick -= thick_d, 1.0);
    glutWireCube (1.0);
    glPopMatrix();

    glTranslatef (1.0, 0.0, 0.0);
    glRotatef (d3, 0.0, 0.0, 1.0);
    glTranslatef (0.5, 0.0, 0.0);

    glPushMatrix();
    glScalef (1.0, thick -= thick_d, 1.0);
    glutWireCube (1.0);
    glPopMatrix();

    // glPopMatrix(); // Keep the last state
}

bool muted = true;

float user_x = 0, user_z = 3.0, user_y = 0, user_r = 0;
int jumpping = 0;

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

    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    switch(jumpping)
    {
    case 1:
        user_y += 0.1;
        if(user_y >= 1) jumpping = 2;
        break;
    case 2:
        user_y -= 0.1;
        if(user_y <= 0) jumpping = 0;
        break;
    }
    float user_r_tmp = user_r * M_PI / 180;
    gluLookAt(user_x, user_y, user_z, user_x + sin(user_r_tmp), user_y, user_z - cos(user_r_tmp), 0.0, 1.0, 0.0);

    glPushMatrix();

    glTranslatef(-3.0, -3.0, 0.0);

    nextColor();
    gen_arm(shoulder, elbow, hand, 0.25);

    for (int i = 0; i < 5; i++)
    {
        glPushMatrix();
        glRotatef (-30 + i * 15, 0.0, 1.0, 0.0);
        glTranslatef (0.5, 0.0, 0.0);
        glScalef (0.2, 0.3, 0.2);
        nextColor();
        gen_arm(thumb, shoulder, elbow, 0.0);
        glPopMatrix();
    }

    glTranslatef(0.0, 1.0, 0.0);
    glRotatef (90.0, 1.0, 0.0, 0.0);

    glPushMatrix();
    glRotatef(sun_r, 0.0, 0.0, 1.0);
    nextColor();
    glutWireSphere(0.5, 20, 20);
    glPopMatrix();

    glRotatef(planet_d, 0.0, 0.0, 1.0);
    glTranslatef(1.0 * (50 - thumb) / 50, 0.0, 0.0);

    glPushMatrix();
    glRotatef(planet_r, 0.0, 0.0, 1.0);
    nextColor();
    glutWireSphere(0.3, 15, 10);
    glPopMatrix();

    glRotatef(sate_d, 0.0, 0.0, 1.0);
    glTranslatef(0.5 * (50 - thumb) / 50, 0.0, 0.0);

    glPushMatrix();
    glRotatef(sate_r, 0.0, 0.0, 1.0);
    nextColor();
    glutWireSphere(0.1, 10, 5);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(90.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}

int last_detec = 0;

void keyboard (unsigned char key, int x, int y)
{
    if(!muted) printf("Key down: %c\n",key);
	float mx = 0, mz = 0;
    switch(key)
    {
    case 'w':
		mz = -0.1;
        break;
    case 'a':
		mx = -0.1;
        break;
    case 's':
		mz = 0.1;
        break;
    case 'd':
		mx = 0.1;
        break;
    case ' ':
        jumpping = 1;
        user_y += 0.1;
        break;
    default:
        if(last_detec != 0) return;
        last_detec = glutGet(GLUT_ELAPSED_TIME);
    }

    float user_r_tmp = user_r * M_PI / 180;
	user_z += mz * cos(user_r_tmp) + mx * sin(user_r_tmp);
	user_x += mx * cos(-user_r_tmp) + mz * sin(-user_r_tmp);
}

void keyup(unsigned char key, int x, int y)
{
    if(!muted) printf("Key up: %c\n",key);
    looper *target = 0;
    int last_detec_tmp;
    switch (key)
    {
    case '9':
        target = &sate_d;
        break;
    case '8':
        target = &planet_d;
        break;
    case '7':
        target = &shoulder;
        break;
    case '6':
        target = &elbow;
        break;
    case '5':
        target = &hand;
        break;
    case '4':
        target = &thumb;
        break;
    case '3':
        target = &sate_r;
        break;
    case '2':
        target = &planet_r;
        last_detec_tmp = last_detec;
        keyup('3', x, y);
        last_detec = last_detec_tmp;
        break;
    case '1':
        target = &sun_r;
        break;
    case 'm':
        muted = !muted;
        return;
    case 27: // ESC
        exit(0);
    default:
        return;
        break;
    }

    int cur_t = glutGet(GLUT_ELAPSED_TIME);
    double inteval = cur_t - last_detec;

    if(inteval > 300)
        target->toggle_auto_loop();
    else
    {
        target->auto_loop(false);
        target->next();
    }

    last_detec = 0;
}

void mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN) return;
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(!muted) printf("Left key");
        user_r -= 10;
        break;
    case GLUT_RIGHT_BUTTON:
        if(!muted) printf("Right key");
        user_r += 10;
        break;
    case GLUT_MIDDLE_BUTTON:
        if(!muted) printf("Middle key");
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    // glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);

	// Manual
	printf("FOV controls:\nkey 'w' to move FOV forward\nkey 's' to move FOV backward\nkey 'a' to move FOV left\nkey 'd' to move FOV right\nmouse left key to rotate FOV counterclockwise\nmouse right key to rotate FOV clockwise\n\nrobot and solar control:\nkey '1' to rotate the sun, long press to keep rotating\nkey '2' to rotate the plant and the satellite, long press to keep rotating\nkey '3' to rotate the satellite, long press to keep rotating\nkey '4' to rotate the thumb, long press to keep rotating\nkey '5' to rotate the hand, long press to keep rotating\nkey '6' to rotate the elbow, long press to keep rotating\nkey '7' to rotate the shoulder, long press to keep rotating\nkey '8' to make the planet revolve the sun , long press to keep revolving\nkey '9' to make the satellite revolve the planet, long press to keep revolving\nkey 'm' to toggle fps and debug message\n\n");

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
4101056017 邱冠喻 第3次作業 4/27
4101056017 Chiu Guan-Yu TheThirdHomework 4/27
***************************/
