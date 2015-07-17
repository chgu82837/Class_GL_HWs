
#define HAND_WEAPONTYPE_STICK 2
#define HAND_WEAPONTYPE_SOLAR 1
#define HAND_WEAPONTYPE_NONE 0

class hand
{
public:
    hand(int weaponType);
    void attack();
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

    int weaponType;
    int attackState;
    character* target;

};
