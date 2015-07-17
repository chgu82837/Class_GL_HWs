
#include "stdafx.h"

hand::hand(int weaponType){
    this->weaponType = weaponType;

    this->shoulder = new looper(-35, 35, 10, -35, LOOPER_TRUN_BACK);
    this->elbow = new looper(-65, 0, 10, -65, LOOPER_TRUN_BACK);
    this->wrist = new looper(20, 50, 10, 20, LOOPER_TRUN_BACK);

	if(weaponType == HAND_WEAPONTYPE_STICK)
		this->thumb = new looper(0, 50, 30, 50, LOOPER_TRUN_BACK);
	else
		this->thumb = new looper(0, 50, 30, 10, LOOPER_TRUN_BACK);

    this->attackState = 0;
    this->target = NULL;

    if(weaponType == HAND_WEAPONTYPE_SOLAR){
        this->sun_r = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
        this->planet_r = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
        this->planet_d = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
        this->sate_r = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
        this->sate_d = new looper(0, 360, 60, 0, LOOPER_TO_LOWER);
    }
}

void hand::attack(){
	this->shoulder->auto_loop(LOOPER_AUTO_ENABLE_STOP);
	this->elbow->auto_loop(LOOPER_AUTO_ENABLE_STOP);
	this->wrist->auto_loop(LOOPER_AUTO_ENABLE_STOP);
}

void hand::draw(){
    glPushMatrix();

    nextColor();
    draw_arm(*shoulder, -*elbow, *wrist, 0.25);

    for (int i = 0; i < 5; i++)
    {
        glPushMatrix();
        glRotatef(-30 + i * 15, 0.0, 1.0, 0.0);
        glTranslatef(0.5, 0.0, 0.0);
        glScalef(0.2, 0.3, 0.2);
        // nextColor();
        draw_arm(*thumb, *thumb + 20.0, *thumb + 10.0, 0.0);
        glPopMatrix();
    }
	
	int ori_color_i = getColorI();
	bool ori_obj_type;

	setColorI(3);
    switch(weaponType)
    {
    case HAND_WEAPONTYPE_STICK:
        glTranslatef(0.0, 0.4, 1.5);
        glScalef(0.5, 0.5, 3.0);
		nextColor();
        draw_obj();
        break;
    case HAND_WEAPONTYPE_SOLAR:
        glTranslatef(0.0, 1.0, 0.0);
        glRotatef (90.0, 1.0, 0.0, 0.0);

		ori_obj_type = get_obj_type();
		set_obj_type(true);
		sun_mode(true);

        glPushMatrix();
        glRotatef(*sun_r, 0.0, 0.0, 1.0);
        nextColor();
		glScalef(0.5,0.5,0.5);
        draw_obj();
        glPopMatrix();

        glRotatef(*planet_d, 0.0, 0.0, 1.0);
        glTranslatef(1.0 * (50 - *thumb) / 50, 0.0, 0.0);

        glPushMatrix();
        glRotatef(*planet_r, 0.0, 0.0, 1.0);
        nextColor();
		glScalef(0.2,0.2,0.2);
        draw_obj();
        glPopMatrix();

        glRotatef(*sate_d, 0.0, 0.0, 1.0);
        glTranslatef(0.5 * (50 - *thumb) / 50, 0.0, 0.0);

        glPushMatrix();
        glRotatef(*sate_r, 0.0, 0.0, 1.0);
        nextColor();
		glScalef(0.1,0.1,0.1);
        draw_obj();
        glPopMatrix();

		set_obj_type(ori_obj_type);
		sun_mode(false);

        break;
    case HAND_WEAPONTYPE_NONE:
        break;
    }

	setColorI(ori_color_i);

    glPopMatrix();
}
