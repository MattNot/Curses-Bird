#include <string>
using namespace std;

class Bird
{
    private:
        int x;
        double y;
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
    this->x=5;
    this->shape="\'*\'";
    this->gravity=1;
    this->lift=5;
    this->vel=0;
    this->isUp=false;
    //printw("finito bird");
}
int Bird::getx(){return this->x;}
int Bird::gety(){return this->y;}
//int Bird::getSize(){return this->size;}
void Bird::up()
{
    mvprintw(this->y,this->x,"   ");
    this->y-=this->lift;
    //mvprintw(0,0,"%d",this->y);
    mvprintw(this->y,this->x,this->shape.c_str());
    refresh();
}

void Bird::show()
{
    //printw("show");
	this->update();
	usleep(2e5+1e4);
    mvprintw(this->y,this->x,this->shape.c_str());
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
    mvprintw(this->y,this->x,"   ");
    this->y+=this->gravity;
    //this->vel*=0,9;
    mvprintw(this->y,this->x,"   ");
    this->y+=this->vel;
    if(this->y>LINES-1)
    {
        this->y=LINES-1;
        this->vel=0;
    }
    if (this->y<0)
    {
        this->y=1;
    }
}