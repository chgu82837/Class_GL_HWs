
#define CHARACTER_TYPE_NONE 0
#define CHARACTER_TYPE_SPHERE 1
#define CHARACTER_TYPE_CUBE 2
#define CHARACTER_TYPE_DEBUG 5

#define CHARACTER_SPECIAL_ATTACK_TYPE_0 0
#define CHARACTER_SPECIAL_ATTACK_TYPE_1 1

class character{
private:
    int type;
    float x;
    float y;
    float z;
    float r;
    int jumpping;

	int mtl_i;
	int walker_cnt;
    int walker_sta;
    int inj_cd;
	int specialAtk_cd;

    character* lockTarget(character** candidate,int start,int len);
    void init(int type,float z,float x,float r,int leftHandType,int rightHandType,int mtl_i);

    int pmodel_list_index;

    bool debug;

public:
    character(const char* obj_path,float z,float x,float r,int leftHandType,int rightHandType,int mtl_i);
    character(int type,float z,float x,float r,int leftHandType,int rightHandType,int mtl_i);
    void leftAttack(character** candidate,int start,int len);
    void rightAttack(character** candidate,int start,int len);
    hurtable* specialAttack(int type);
    void move(float z,float x,float r,wall** w,int nw);
    void mount();
	void ui();
    void jump();
	void walk(character** candidate,int start,int len,wall** w,int nw);
    void draw();
    void injured(int damage);
    void enableDebug();
    bool valid(wall* w);

    hand* left;
    hand* right;
	int health;
};
