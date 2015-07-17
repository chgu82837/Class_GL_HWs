
#define HAND_WEAPONTYPE_STICK 2
#define HAND_WEAPONTYPE_SOLAR 1
#define HAND_WEAPONTYPE_NONE 0

class hand
{
public:
    hand(int weaponType,bool is_sphere,int mtl_i);
    void attack(character *target);
    void draw();

    looper* sun_r;
    looper* planet_d;
    looper* planet_r;
    looper* sate_d;
    looper* sate_r;

    looper* shoulder;
    looper* elbow;
    looper* wrist;
    looper* thumb;

private:
    void draw_arm(GLfloat d1, GLfloat d2, GLfloat d3, GLfloat thick_d);

    int weaponType;
    int attackState;
    int mtl_i;
    bool is_sphere;
    int cd;
};
