
#include "stdafx.h"

hurtable::hurtable(int type,int mtl_i,float thick,float x1,float z1,float x2,float z2,int cnt,int damage){
    this->type = type;
    this->cd = cnt;
    this->cd_init = cnt;
    this->damage = damage;
    this->range = new wall(mtl_i,thick,x1,z1,x2,z2);
    this->fired = false;
}

hurtable::~hurtable()
{
	delete range;
}

void hurtable::fire(character** candidate, int len){
    this->candidate = candidate;
    this->candidate_l = len;
    this->fired = true;
}

bool hurtable::tick(){
    if(cd <= 0) return false;
    cd--;

    glPushMatrix();
    glTranslatef(0,((float) cd / (float) cd_init) * 10.0,0);
    switch(type){
        case HURTABLE_TYPE_NONE:
        break;
        case HURTABLE_TYPE_SPHERE:
			set_obj_type(true);
            this->range->draw();
			pop_obj_type();
        break;
        case HURTABLE_TYPE_CUBE:
			set_obj_type(false);
            this->range->draw();
			pop_obj_type();
        break;
    }
    glPopMatrix();

    if(cd == 3){
        for (int i = 0; i < candidate_l; ++i)
        {
            if(!candidate[i]->valid(range)) candidate[i]->injured(damage);
        }
    }

    return true;
}
