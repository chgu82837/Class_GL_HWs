
class character{
private:
    bool is_sphere; // or cube
    float x;
    float y;
    float z;
    float r;
    int jumpping;

	int color_i;
	bool walker;
	int walker_cnt;

	void attack(character* candidate);

public:
    character(bool is_sphere,float z,float x,float r,int leftHandType,int rightHandType,int color_i,bool walker);
    void leftAttack(character* candidate);
    void rightAttack(character* candidate);
    void move(float z,float x,float r);
    void mount();
    void jump();
    void draw();

    hand* left;
    hand* right;
	int health;
};
