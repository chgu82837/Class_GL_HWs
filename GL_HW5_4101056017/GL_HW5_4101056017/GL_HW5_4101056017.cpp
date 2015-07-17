/***************************
4101056017 邱冠喻 第5次作業 6/2
4101056017 Chiu Guan-Yu TheFifthHomework 6/2
***************************/

#include "stdafx.h"

#define THE_BG 0.39,0.68,0.48,

GLfloat light_pos_ori[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_Ka[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_Kd[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_Ks[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat lightHead_Ka[] = { 0.7, 0.2, 0.2, 1.0 };
GLfloat lightHead_Kd[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat lightHead_Ks[] = { 1.0, 1.0, 0.45, 1.0 };

GLfloat lmodel_Ka[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat local_viewer[] = { 0.0 };

void init_light()
{
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_Ka);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_viewer);

    // Light0

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

    // Ligth1

    glLightfv(GL_LIGHT1, GL_AMBIENT, lightHead_Ka);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightHead_Kd);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightHead_Ks);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // glDisable(GL_LIGHT1);
}

// ========================================

bool muted = true;

bool keyStates[256] = {0}; // 0 for mouse left, 1 for mouse right, 2 for mouse middle
character user(CHARACTER_TYPE_CUBE, 3.0, 0, 0, HAND_WEAPONTYPE_NONE, HAND_WEAPONTYPE_SOLAR,MTL_orange);
character* users[] = { &user };
looper sun(-90.0, 90.0, 2880, 0.0, LOOPER_TRUN_BACK, LOOPER_AUTO_ENABLE);
character* mon[3];
wall* wa[5];
std::set<hurtable*> hurtables;

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

    if(keyStates['d']) user.move(0.0, 0.05, 0.0,wa,sizeof(wa) / sizeof(wall*));
    if(keyStates['a']) user.move(0.0, -0.05, 0.0,wa,sizeof(wa) / sizeof(wall*));
    if(keyStates['w']) user.move(-0.05, 0.0, 0.0,wa,sizeof(wa) / sizeof(wall*));
    if(keyStates['s']) user.move(0.05, 0.0, 0.0,wa,sizeof(wa) / sizeof(wall*));
    if(keyStates[' ']) user.jump();
    if(keyStates[0]) user.move(0.0, 0.0, -2.5,wa,sizeof(wa) / sizeof(wall*));
    if(keyStates[1]) user.move(0.0, 0.0, 2.5,wa,sizeof(wa) / sizeof(wall*));
    if(keyStates['[']) user.move(0.0, 0.0, -2.5,wa,sizeof(wa) / sizeof(wall*));
    if(keyStates[']']) user.move(0.0, 0.0, 2.5,wa,sizeof(wa) / sizeof(wall*));
    // if(keyStates['1']) user.right->sun_r->next();
    // if(keyStates['2']) user.right->planet_d->next();
    if(keyStates['3']) user.right->planet_d->next();
    if(keyStates['4']) user.right->sate_d->next();
    if(keyStates['5']) user.right->thumb->next();
    if(keyStates['6']) user.right->wrist->next();
    if(keyStates['7']) user.right->elbow->next();

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(THE_BG 1.0);
    user.mount();

    // The sun ========================

    glPushMatrix();
        glRotatef(sun, 0.0, 0.0, 1.0);
        glTranslatef(0.0,20.0,0.0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos_ori);
        set_mtl(MTL_fire);
            glutSolidSphere(0.75, 30, 30);
        pop_mtl();
    glPopMatrix();

    // The ground =====================

    glPushMatrix();
    set_mtl(MTL_gray);
    glTranslatef(0.0, -2.0, 0.0);
    glRotatef (90, 1.0, 0.0, 0.0);
    glRectf (10.0, 10.0, -10.0, -10.0);
    pop_mtl();
    glPopMatrix();

    // ================================

    for (int i = 0; i < sizeof(mon) / sizeof(character*); i++)
    {
		mon[i]->walk(users,0,1,wa,sizeof(wa) / sizeof(wall*));
        mon[i]->draw();
    }

    set_obj_type(false);
	for (int i = 0; i < sizeof(wa) / sizeof(wall*); i++)
	{
		wa[i]->draw();
	}
    pop_obj_type();

	std::set<hurtable*>::iterator toDelete;
	bool shouldDelete = false;
	for (std::set<hurtable*>::iterator it=hurtables.begin(); it!=hurtables.end(); ++it){
		if(!(*it)->tick()){
			toDelete = it;
			shouldDelete = true;
		}
	}
	if(shouldDelete){
		delete *toDelete;
		hurtables.erase(toDelete);
	}

    user.ui();

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
bool light1Enabled = false;
bool polyoffEnabled = false;
bool fogEnabled = false;

void keyboard (unsigned char key, int x, int y)
{
    keyStates[key] = true;
	hurtable* h_tmp;

    switch(key)
    {
    case 27:
        exit(0);
        break;
    case 'l':
        if(light1Enabled)
            glDisable(GL_LIGHT1);
        else
            glEnable(GL_LIGHT1);
        light1Enabled = !light1Enabled;
        break;
    case 'z':
        user.leftAttack(mon,0,sizeof(mon) / sizeof(character*));
        break;
    case 'x':
        user.rightAttack(mon,0,sizeof(mon) / sizeof(character*));
        break;
    case '1':
        h_tmp = user.specialAttack(CHARACTER_SPECIAL_ATTACK_TYPE_0);
		if(h_tmp != NULL){
			h_tmp->fire(mon,sizeof(mon)/sizeof(character*));
			hurtables.insert(h_tmp);
		}
        break;
    case '2':
        h_tmp = user.specialAttack(CHARACTER_SPECIAL_ATTACK_TYPE_1);
		if(h_tmp != NULL){
			h_tmp->fire(mon,sizeof(mon)/sizeof(character*));
			hurtables.insert(h_tmp);
		}
        break;
    case 'p':
        if(!polyoffEnabled){
            glEnable(GL_POLYGON_OFFSET_LINE);
            // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glPolygonOffset(0.8, 1);
        }
        else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDisable(GL_POLYGON_OFFSET_FILL);
        }
        polyoffEnabled = !polyoffEnabled;
        break;
    case 'f':
        if(!fogEnabled){
            GLfloat fogColor[4] = {THE_BG 1.0};
            glEnable(GL_FOG);
            glFogi (GL_FOG_MODE, GL_EXP);
            glFogfv (GL_FOG_COLOR, fogColor);
            glFogf (GL_FOG_DENSITY, 0.35);
            glFogf (GL_FOG_START, 10.0);
            glFogf (GL_FOG_END, 20.0);
        }
        else{
            glDisable(GL_FOG);
        }
        fogEnabled = !fogEnabled;
        break;
    case 'k':
        user.health = 0.0;
        break;
	case 'm':
		if(muted) printf("muted disabled...");
		else printf("muted...");
		muted = !muted;
		user.enableDebug();
		printf("There are %d of users, %d of mons, %d of walls, %d of hurtables\n",sizeof(users)/sizeof(character*),sizeof(mon)/sizeof(character*),hurtables.size());
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
    glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_3D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    srand (time(NULL));

    char* chara_0_obj_path = "./data/Hulk.obj";
    char* chara_1_obj_path = "./data/Luigi_obj.obj";
    char* chara_2_obj_path = "./data/mario_obj.obj";
    switch(argc){
        case 4:
            chara_2_obj_path = argv[3];
        case 3:
            chara_1_obj_path = argv[2];
        case 2:
            chara_0_obj_path = argv[1];
        break;
    }

    wa[0] = new wall(MTL_wall_blue,1);
    wa[1] = new wall(MTL_wall_gray,1);
    wa[2] = new wall(MTL_wall_lavender,1);
    wa[3] = new wall(MTL_wall_red,1);
    wa[4] = new wall(MTL_wall_yellow,1);
    
    mon[0] = new character(chara_0_obj_path, -3.0, -3.0, 180, HAND_WEAPONTYPE_NONE, HAND_WEAPONTYPE_STICK, MTL_blue);
    mon[1] = new character(chara_1_obj_path, -3.0, 0.0, 180, HAND_WEAPONTYPE_NONE, HAND_WEAPONTYPE_STICK, MTL_orange);
    mon[2] = new character(chara_2_obj_path, -3.0, 3.0, 180, HAND_WEAPONTYPE_NONE, HAND_WEAPONTYPE_STICK, MTL_lavender);

    // Manual
    printf("User's character controls:\nkey 'w' to move character forward\nkey 's' to move character backward\nkey 'a' to move character left\nkey 'd' to move character right\nkey ' ' (space) to make character jump\nmouse left key or ']' to rotate character counterclockwise\nmouse right key or '[' to rotate character clockwise\nkey 'z' to do a left hand short attack\nkey 'x' to do a right hand short attack\nkey '1' to do a laser long range attack\nkey '2' to do a long long range attack\n\nother control:\nkey '3' to make the planet revolve the sun , long press to keep revolving\nkey '4' to make the satellite revolve the planet, long press to keep revolving\nkey '5' to move the thumb, long press to keep moving\nkey '6' to move the wrist, long press to keep moving\nkey '7' to move the elbow, long press to keep moving\nkey 'l' to toggle head light\nkey 'p' to toggle Polygon offset mode\nkey 'f' to toggle fog\nkey 'k' to suicide\nkey 'm' to toggle fps and debug message\n");

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
4101056017 邱冠喻 第5次作業 6/2
4101056017 Chiu Guan-Yu TheFifthHomework 6/2
***************************/
