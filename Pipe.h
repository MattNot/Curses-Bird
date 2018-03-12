#include <vector>
#include <iostream>
using namespace std;
class Pipe
{
    public:
        int speed;
        int x;
        //char v[20]="ciao";
        vector<int> y;
        int finishU;
        int startB;
        void update();
        void show();
        bool isHit(Bird* bird);
        Pipe();
        Pipe(int);
};
Pipe::Pipe(){
    this->x=COLS-1;
    this->speed=1;
    do{
        this->finishU=((rand()%LINES))/2;
        this->startB=((rand()%LINES)+1)/2;
    }while(this->startB-this->finishU<2 || finishU==0);
   
    for(int i=0; i<this->finishU; i++)
    {
        y.push_back(i);
        mvprintw(i,x,"#");
        refresh();
    }
    for(int i=startB-1; i<LINES; i++)
    {
        y.push_back(i);
        mvprintw(i,x,"#");
        refresh();    
    }
}

void Pipe::update()
{
    this->x-=this->speed;
}

void Pipe::show()
{
    this->update();
    for(int i=0; i<this->finishU; i++)
    {
        //y.push_back(i);
        mvprintw(i,x+1," ");
        mvprintw(i,x,"#");
        refresh();
    }
    for(int i=startB-1; i<LINES; i++)
    {
        //y.push_back(i);
        mvprintw(i,x+1," ");
        mvprintw(i,x,"#");
        refresh();
    }
}