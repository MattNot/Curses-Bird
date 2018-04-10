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
        bool isUp;
    public:
        int getx();
        int gety();
        void show();
        void up();
        void update();
        Bird(int,int);
};

Bird::Bird(int li, int col)
{
    this->y=li/2;
    this->x=5;
    this->shape="\'*\'";
    this->gravity=1;
    this->lift=4;
    this->isUp=false;
}

int Bird::getx(){return this->x;}
int Bird::gety(){return this->y;}

void Bird::up()
{
    mvprintw(this->y,this->x,"   ");
    this->y-=this->lift;
    if(this->y<=0)
    {
        this->y=0;
    }
    mvprintw(this->y,this->x,this->shape.c_str());
    refresh();
}

void Bird::show()
{
	this->update();
	usleep((2e4)*8);
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

    mvprintw(this->y,this->x,"   ");
    if(this->y>LINES-1)
    {
        this->y=LINES-1;
    }
    if (this->y<0)
    {
        this->y=1;
    }
}