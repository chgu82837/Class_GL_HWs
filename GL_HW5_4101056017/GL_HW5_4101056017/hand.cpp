
#include "stdafx.h"

hand::hand(int weaponType,bool is_sphere,int mtl_i){
    this->weaponType = weaponType;
    this->is_sphere = is_sphere;
    this->mtl_i = mtl_i;

    this->shoulder = new looper(-35, 35, 10, -35, LOOPER_TRUN_BACK);
    this->elbow = new looper(-65, 0, 10, -65, LOOPER_TRUN_BACK);
    this->wrist = new looper(20, 50, 10, 20, LOOPER_TRUN_BACK);

	if(weaponType == HAND_WEAPONTYPE_STICK)
		this->thumb = new looper(0, 50, 30, 50, LOOPER_TRUN_BACK);
	else
		this->thumb = new looper(0, 50, 30, 10, LOOPER_TRUN_BACK);

    this->attackState = 0;

    if(weaponType == HAND_WEAPONTYPE_SOLAR){
        this->sun_r = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
        this->planet_r = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
        this->planet_d = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
        this->sate_r = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
        this->sate_d = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
    }

    this->cd = 0;
}

void hand::attack(character *target)
{
    if(cd) return;
    this->shoulder->auto_loop(LOOPER_AUTO_ENABLE_STOP);
    this->elbow->auto_loop(LOOPER_AUTO_ENABLE_STOP);
    this->wrist->auto_loop(LOOPER_AUTO_ENABLE_STOP);
    cd += 40;
    if(target == NULL) return;
    target->injured(10);
}

void hand::draw(){
    glPushMatrix();

    set_obj_type(is_sphere);

    if(cd){
        cd--;
        set_mtl(MTL_fire);
    }
    else
        set_mtl(mtl_i);

    draw_arm(*shoulder, -*elbow, *wrist, 0.25);

    for (int i = 0; i < 5; i++)
    {
        glPushMatrix();
        glRotatef(-30 + i * 15, 0.0, 1.0, 0.0);
        glTranslatef(0.5, 0.0, 0.0);
        glScalef(0.2, 0.3, 0.2);
        draw_arm(*thumb, *thumb + 20.0, *thumb + 10.0, 0.0);
        glPopMatrix();
    }

    switch(weaponType)
    {
    case HAND_WEAPONTYPE_STICK:
        glTranslatef(0.0, 0.4, 1.5);
        glScalef(0.5, 0.5, 3.0);
        set_mtl(MTL_red);
        glutSolidCube (1.0);
        pop_mtl();
        break;
    case HAND_WEAPONTYPE_SOLAR:

        glTranslatef(0.0, 1.0, 0.0);
        glRotatef (90.0, 1.0, 0.0, 0.0);

        set_mtl(MTL_sun);

        glPushMatrix();
        glRotatef(*sun_r, 0.0, 0.0, 1.0);
		glScalef(0.5,0.5,0.5);
        glutSolidSphere(0.75, 30, 30);
        glPopMatrix();

        pop_mtl();
        set_mtl(MTL_green);

        glRotatef(*planet_d, 0.0, 0.0, 1.0);
        glTranslatef(1.0 * (50 - *thumb) / 50, 0.0, 0.0);

        glPushMatrix();
        glRotatef(*planet_r, 0.0, 0.0, 1.0);
		glScalef(0.2,0.2,0.2);
        glutSolidSphere(0.75, 30, 30);
        glPopMatrix();

        pop_mtl();
        set_mtl(MTL_cyan);

        glRotatef(*sate_d, 0.0, 0.0, 1.0);
        glTranslatef(0.5 * (50 - *thumb) / 50, 0.0, 0.0);

        glPushMatrix();
        glRotatef(*sate_r, 0.0, 0.0, 1.0);
		glScalef(0.1,0.1,0.1);
        glutSolidSphere(0.75, 30, 30);
        glPopMatrix();

        pop_mtl();

        break;
    case HAND_WEAPONTYPE_NONE:
        break;
    }

    pop_mtl();
    pop_obj_type();

    glPopMatrix();
}

void hand::draw_arm(GLfloat d1, GLfloat d2, GLfloat d3, GLfloat thick_d)
{
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
}
