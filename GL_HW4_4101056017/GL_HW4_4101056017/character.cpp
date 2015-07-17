
#include "stdafx.h"

character::character(bool is_sphere,float z,float x,float r,int leftHandType,int rightHandType,int color_i,bool walker){
    this->is_sphere = is_sphere;
    this->x = x;
    this->y = 0.0;
    this->z = z;
    this->r = r;

    this->left = new hand(leftHandType);
    this->right = new hand(rightHandType);

	this->color_i = color_i;

    this->jumpping = 0;

	this->walker = walker;
	this->health = 100;
}

void character::attack(character* candidate)
{
	float user_r_tmp = this->r * M_PI / 180;
	float debug;
	float atk_z = z - cos(user_r_tmp) * 3;
	float atk_x = x - sin(-user_r_tmp) * 3;
	for (int i = 0; i < MON_N; i++)
	{
		debug = (candidate[i].x - atk_x) * (candidate[i].x - atk_x) + (candidate[i].z - atk_z) * (candidate[i].z - atk_z);
		if(debug < 1)
            candidate[i].health -= 10;
	}
}

void character::leftAttack(character* candidate){
	if(health <= 0) return;
    left->attack();
	attack(candidate);
}

void character::rightAttack(character* candidate){
	if(health <= 0) return;
    right->attack();
	attack(candidate);
}

void character::jump(){
    if(health <= 0) return;
	this->jumpping = 1;
}

void character::move(float z,float x,float r){
	if(health <= 0) return;
    this->r += r;
    float user_r_tmp = this->r * M_PI / 180;
    this->z += z * cos(user_r_tmp) + x * sin(user_r_tmp);
    this->x += x * cos(-user_r_tmp) + z * sin(-user_r_tmp);
	if(this->z < Z_MIN) this->z = Z_MIN;
	if(this->z > Z_MAX) this->z = Z_MAX;
	if(this->x < X_MIN) this->x = X_MIN;
	if(this->x > X_MAX) this->x = X_MAX;
}

int inj_cd = 0;

void character::mount(){
    float r_tmp = r * M_PI / 180;
	if(health <= 0){
		gluLookAt(x + sin(r_tmp) * 0.9, y + 1.5, z  - cos(r_tmp) * 0.9, x + sin(r_tmp) * 1.5, y + 1.4, z - cos(r_tmp) * 1.5, 1.0, 0.0, 0.0);
		return;
	}
    gluLookAt(x + sin(r_tmp) * 0.9, y + 1.5, z  - cos(r_tmp) * 0.9, x + sin(r_tmp) * 1.5, y + 1.4, z - cos(r_tmp) * 1.5, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(x,y,z);
	GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glTranslated(x + sin(r_tmp) * 1.5, y + 2.0, z - cos(r_tmp) * 1.5);
	glScalef (health / 100.0, 0.1,0.1);
	glutSolidCube(1.0);
	glPopMatrix();

	if(!inj_cd){
		
	}
	else inj_cd--;
}

void character::draw(){
	if(health <= 0) return;

    int ori_use_sphere = get_obj_type();

	int ori_color_i = getColorI();
	setColorI(color_i);

	sun_mode(false);

    glPushMatrix();

    switch(jumpping)
    {
    case 1:
        y += 0.1;
        if(y >= 1) jumpping = 2;
        break;
    case 2:
        y -= 0.1;
        if(y <= 0) jumpping = 0;
        break;
    }

    glTranslatef(x,y,z);
    glRotatef (-r, 0.0, 1.0, 0.0);

	glPushMatrix(); // health bar
    glTranslatef(0.0,3.0,0.0);
    glScalef (health / 100.0, 0.1,0.1);
	sun_mode(true);
    glutSolidCube(1.0);
    glPopMatrix();
	sun_mode(false);

    set_obj_type(is_sphere);

    glPushMatrix(); // body
    glScalef (1.6, 3.0, 0.75);
	nextColor();
    draw_obj();
    glPopMatrix();

    glPushMatrix(); // head
    glTranslatef(0.0,2.0,0.0);
	nextColor();
    draw_obj();
    glPopMatrix();

    glPushMatrix(); // right foot
    glTranslatef(0.8,-1.5,0.0);
	nextColor();
    draw_obj();
    glPopMatrix();

    glPushMatrix(); // left foot
    glTranslatef(-0.8,-1.5,0.0);
	nextColor();
    draw_obj();
    glPopMatrix();

    glPushMatrix(); // right hand
    glTranslatef(0.8,1.0,0.0);
    glScalef (0.4, 0.4, 0.4);
    glRotatef (75, 0.0, 0.0, 1.0);
    glRotatef (90, 0.0, 1.0, 0.0);
    right->draw();
    glPopMatrix();

    glPushMatrix(); // left hand
    glTranslatef(-0.8,1.0,0.0);
    glScalef (-0.4, 0.4, 0.4);
    glRotatef (75, 0.0, 0.0, 1.0);
    glRotatef (90, 0.0, 1.0, 0.0);
    left->draw();
    glPopMatrix();

    glPopMatrix();

	setColorI(ori_color_i);
    set_obj_type(ori_use_sphere);
}
