#include <string>
using namespace std;
class Bird
{
    private:
        int x;
        int y;
        string shape;
        double gravity;
        double lift;
        double vel;
        bool isUp;
    public:
        int getx();
        int gety();
        //int getSize();
        void show();
        void up();
        void update();
        Bird(int,int);
};

Bird::Bird(int li, int col)
{
    //printw("creato bird");
    this->y=li/2;
    this->x=col/2;
    this->shape="\'*\'";
    this->gravity=1;
    this->lift=2;
    this->vel=0;
    this->isUp=false;
    //printw("finito bird");
}
int Bird::getx(){return this->x;}
int Bird::gety(){return this->y;}
//int Bird::getSize(){return this->size;}
void Bird::up()
{
    this->vel+=this->lift;
}
void Bird::update()
{
    if(this->isUp){
        this->shape=",*,";
        this->isUp=!this->isUp;
    }else{
        this->shape="'*'";
        this->isUp=!this->isUp;
    }
    this->vel+=this->gravity;
    this->vel*=0,9;
    //this->y+=this->vel;
    if(this->y>LINES)
    {
        this->y=LINES-1;
        this->vel=0;
    }
    if (this->y<0)
    {
        this->y=0;
        this->vel=0;
    }
}
