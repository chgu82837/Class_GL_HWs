
#include "stdafx.h"
#include "glm.c"

#define CHARACTER_TYPE_OBJ 3

void character::init(int type, float z, float x, float r, int leftHandType, int rightHandType, int mtl_i)
{
    this->type = type;
    this->x = x;
    this->y = 0.0;
    this->z = z;
    this->r = r;

    this->left = new hand(leftHandType, type == CHARACTER_TYPE_SPHERE, mtl_i);
    this->right = new hand(rightHandType, type == CHARACTER_TYPE_SPHERE, mtl_i);
    this->mtl_i = mtl_i;

    this->walker_cnt = 0;
    this->walker_sta = 0;

    this->jumpping = 0;
    this->health = 100;
    this->inj_cd = 0;

    this->debug = false;
	this->specialAtk_cd = 0;
}

character::character(int type, float z, float x, float r, int leftHandType, int rightHandType, int mtl_i){
    init(type,z,x,r,leftHandType,rightHandType,mtl_i);
}

character::character(const char* obj_path, float z, float x, float r, int leftHandType, int rightHandType, int mtl_i){
    GLMmodel* pmodel = glmReadOBJ((char*) obj_path);
    if (!pmodel) {
        printf("WARN: '%s' not found!\n",obj_path);
        init(CHARACTER_TYPE_SPHERE,z,x,r,leftHandType,rightHandType,mtl_i);
    }
    else{
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90.0);
        init(CHARACTER_TYPE_OBJ,z,x,r,leftHandType,rightHandType,mtl_i);

        pmodel_list_index = glGenLists(1);
        if(pmodel_list_index == 0){
            printf("ERROR: Can not request a new glGenList!\n",obj_path);
            exit(255);
        }
        glNewList(pmodel_list_index,GL_COMPILE);
        glmDraw(pmodel, GLM_SMOOTH);
        glEndList();
    }
}

void character::injured(int damage)
{
    if (inj_cd) return;
    if(debug) printf("hit!\n");
    health -= damage;
    inj_cd += 15;
}
character *character::lockTarget(character** candidate, int start, int len)
{
    float user_r_tmp = this->r * M_PI / 180;
    float distance;
    float atk_z = z - cos(user_r_tmp) * 3;
    float atk_x = x - sin(-user_r_tmp) * 3;
    if(debug) printf("(atk_x,atk_z):(%f,%f)\n",atk_x,atk_z);
    for (int i = start; i < (start + len); i++)
    {
        distance = (candidate[i]->x - atk_x) * (candidate[i]->x - atk_x) + (candidate[i]->z - atk_z) * (candidate[i]->z - atk_z);
        if(debug) printf("mon %d, distance: %f\n",i,distance);
        if(distance < 1)
        {
            return candidate[i];
        }
    }
    return NULL;
}

void character::leftAttack(character** candidate, int start, int len)
{
    if(health <= 0) return;
    character *target = lockTarget(candidate, start, len);
    left->attack(target);
}

void character::rightAttack(character** candidate, int start, int len)
{
    if(health <= 0) return;
    character *target = lockTarget(candidate, start, len);
    right->attack(target);
}

void character::jump()
{
    if(health <= 0) return;
    this->jumpping = 1;
}

void character::move(float z, float x, float r,wall** w,int nw)
{
    if(health <= 0) return;
    this->r += r;
    float user_r_tmp = this->r * M_PI / 180;
    this->z += z * cos(user_r_tmp) + x * sin(user_r_tmp);
    this->x += x * cos(-user_r_tmp) + z * sin(-user_r_tmp);

	float* corrected_location;
    float tx,tz;

	for (int i = 0; i < nw; i++)
	{
		if(!w[i]->valid(this->x,this->z)){
			corrected_location = w[i]->closest(this->x,this->z);
			this->x = corrected_location[0];
			this->z = corrected_location[1];
            delete[] corrected_location;
		}
	}

    if(this->z < Z_MIN) this->z = Z_MIN;
    if(this->z > Z_MAX) this->z = Z_MAX;
    if(this->x < X_MIN) this->x = X_MIN;
    if(this->x > X_MAX) this->x = X_MAX;
}

void character::mount()
{
    float r_tmp = r * M_PI / 180;
    glLoadIdentity();

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

    if(health)
        gluLookAt(x + sin(r_tmp) * 0.9, y + 1.6, z  - cos(r_tmp) * 0.9, x + sin(r_tmp) * 1.5, y + 1.4, z - cos(r_tmp) * 1.5, 0.0, 1.0, 0.0);
    else
        gluLookAt(x + sin(r_tmp) * 0.9, y + 1.6, z  - cos(r_tmp) * 0.9, x + sin(r_tmp) * 1.5, y + 1.4, z - cos(r_tmp) * 1.5, 1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslated(x, y + 1.5, z);
    glRotatef (-r, 0.0, 1.0, 0.0);
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();

}

void character::walk(character** candidate,int start,int len,wall** w,int nw)
{
    if(walker_cnt--)
    {
        if(walker_sta == 0) move(0.0, 0.0, -2.5,w,nw);
        else if(walker_sta == 1) move(0.0, 0.0, 2.5,w,nw);
        else if(walker_sta <= 5) move(-0.05, 0.0, 0.0,w,nw);
    }
    else
    {
        walker_sta = rand() % 10;
        walker_cnt = rand() % 120;

        character *target = lockTarget(candidate, start, len);
        if(target != NULL)
        {
            if(rand() % 2) left->attack(target);
            else right->attack(target);
        }
    }
}

void character::draw()
{
    if(health <= 0 || type == CHARACTER_TYPE_NONE) return;

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

    glTranslatef(x, y, z);
    glRotatef (-r, 0.0, 1.0, 0.0);

	if(specialAtk_cd){
		set_mtl(MTL_fire);
		specialAtk_cd--;
	}
    else if(inj_cd){
        set_mtl(MTL_blood);
        inj_cd--;
    }
    else
        set_mtl(mtl_i);

    glPushMatrix(); // health bar
    glTranslatef(0.0, 3.0, 0.0);

    set_mtl(MTL_blood);
    glScalef (health / 100.0, 0.1, 0.1);
    glRectf (0.5, 0.5, -0.5, -0.5);
    pop_mtl();
    glPopMatrix();

    if(type == CHARACTER_TYPE_OBJ){
        glPushMatrix(); // GLM
        glScalef(2.5,2.5,2.5);
        glRotatef (180, 0.0, 1.0, 0.0);
        glCallList(pmodel_list_index);
        glPopMatrix();
    }
    else if(type == CHARACTER_TYPE_SPHERE || type == CHARACTER_TYPE_CUBE)
    {
        set_obj_type(type == CHARACTER_TYPE_SPHERE);

        glPushMatrix(); // body
        glScalef (1.6, 3.0, 0.75);
        draw_obj();
        glPopMatrix();

        glPushMatrix(); // head
        glTranslatef(0.0, 2.0, 0.0);
        draw_obj();
        glPopMatrix();

        glPushMatrix(); // right foot
        glTranslatef(0.8, -1.5, 0.0);
        draw_obj();
        glPopMatrix();

        glPushMatrix(); // left foot
        glTranslatef(-0.8, -1.5, 0.0);
        draw_obj();
        glPopMatrix();

        glPushMatrix(); // right hand
        glTranslatef(0.8, 1.0, 0.0);
        glScalef (0.4, 0.4, 0.4);
        glRotatef (75, 0.0, 0.0, 1.0);
        glRotatef (90, 0.0, 1.0, 0.0);
        right->draw();
        glPopMatrix();

        glPushMatrix(); // left hand
        glTranslatef(-0.8, 1.0, 0.0);
        glScalef (-0.4, 0.4, 0.4);
        glRotatef (75, 0.0, 0.0, 1.0);
        glRotatef (90, 0.0, 1.0, 0.0);
        left->draw();
        glPopMatrix();

        pop_obj_type();
    }

    pop_mtl();
    glPopMatrix();
}

void character::ui()
{
    glClear (GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(x, y + 1.5, z);
    glRotatef (-r, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslated(0.0, -0.75, -1.5);
    glScalef (health / 100.0, 0.1, 0.1);
    set_mtl(MTL_blood);
    glRectf(0.5, 0.5, -0.5, -0.5);
    pop_mtl();
    glPopMatrix();

    if(health){
		if(specialAtk_cd){
			set_mtl(MTL_fire);
			specialAtk_cd--;
		}
        else if(!inj_cd)
            set_mtl(mtl_i);
        else{
            set_mtl(MTL_blood);
            inj_cd--;
        }
        set_obj_type(type == CHARACTER_TYPE_SPHERE);

        glTranslatef(0.0, -1.75, -1.0);

        glPushMatrix(); // right hand
        glTranslatef(0.8, 1.0, 0.0);

        glScalef (0.4, 0.4, 0.4);
        glRotatef (75, 0.0, 0.0, 1.0);
        glRotatef (90, 0.0, 1.0, 0.0);
        right->draw();
        glPopMatrix();

        glPushMatrix(); // left hand
        glTranslatef(-0.8, 1.0, 0.0);
        glScalef (-0.4, 0.4, 0.4);
        glRotatef (75, 0.0, 0.0, 1.0);
        glRotatef (90, 0.0, 1.0, 0.0);
        left->draw();
        glPopMatrix();

        pop_obj_type();
        pop_mtl();
    }
    else{
        glDisable(GL_LIGHTING);
		glPushMatrix();
        glColor4f(1.0, 0.0, 0.0, 0.2);
		glTranslated(0.0, -0.75, -1.5);
		glRectf(10.0,10.0,-10.0,-10.0);
		glPopMatrix();
        glEnable(GL_LIGHTING);
    }

    glPopMatrix();
}

void character::enableDebug(){
    this->debug = true;
}

bool character::valid(wall* w){
    return w->valid(this->x,this->z);
}

hurtable* character::specialAttack(int type){
	if(specialAtk_cd) return NULL;
	specialAtk_cd = 120;
	float user_r_tmp = this->r * M_PI / 180;
    switch(type){
        case CHARACTER_SPECIAL_ATTACK_TYPE_0:
			return new hurtable(HURTABLE_TYPE_CUBE,MTL_hurtable_fire,1,x - sin(-user_r_tmp) * 5,z - cos(user_r_tmp) * 5,x - sin(-user_r_tmp) * 9,z - cos(user_r_tmp) * 9,60,20);
        break;
        case CHARACTER_SPECIAL_ATTACK_TYPE_1:
            return new hurtable(HURTABLE_TYPE_SPHERE,MTL_hurtable_death,1,x - sin(-user_r_tmp) * 9,z - cos(user_r_tmp) * 9,x - sin(-user_r_tmp) * 10,z - cos(user_r_tmp) * 10,120,30);
        break;
    }
    return NULL;
}
