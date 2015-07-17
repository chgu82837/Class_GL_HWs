
#include "stdafx.h"

#define LOOPER_TO_LOWER true
#define LOOPER_TRUN_BACK false

class looper{
private:
    float lower;
    float upper;
    float inteval;
    float cur;
    bool behavior;
    bool a_loop;

public:
    looper(float lower,float upper,int step,int init,bool behavior){
        this->lower = lower;
        this->upper = upper;
        this->inteval = (upper - lower) / step;
        this->cur = init;
        this->behavior = behavior;
        this->a_loop = false;
    }

    float next(){
        float r = cur + inteval;
        if(r > upper || r < lower){
            if(behavior){ // LOOPER_TO_LOWER
                r = lower;
            }
            else{ // LOOPER_TRUN_BACK
                inteval = -inteval;
                r = cur + inteval;
            }
        }
        return cur = r;
    }

    operator float() {
        if(a_loop) return next();
        else return this->cur;
    }

    void auto_loop(bool enable){
        this->a_loop = enable;
    }

    void toggle_auto_loop(){
        this->a_loop = !this->a_loop;
    }
};
