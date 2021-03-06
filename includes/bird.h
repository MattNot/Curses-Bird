#include <string>
using namespace std;

class Bird
{
    private:
        short int x;
        short int y;
        string shape;
        short int gravity;
        short int lift;
        bool invincibility;
        bool isUp;
    public:
        int getx();
        int gety();
        void show();
        void up();
        void update();
        bool isInvincible();
        bool setInvincibility(bool);
        Bird();
};