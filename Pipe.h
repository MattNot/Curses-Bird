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
    do{
        this->finishU=((rand()%LINES))/2;
        this->startB=((rand()%LINES)+1)/2;
    }while(this->startB-this->finishU<=1 || finishU==0);
   // printw(to_string(finishU).c_str());
   // mvprintw(1,1,to_string(startB).c_str());
    int z=0;
    for(int i=0; i<this->finishU; i++)
    {
        y.push_back(i);
        usleep(1e6);
        mvprintw(i,x,to_string(y[i]).c_str());
        z=i;
        refresh();
    }
    for(int i=startB; i<LINES-1; i++)
    {
        //mvprintw(0,0,to_string(i).c_str());
       // printw(to_string(startB).c_str());
        y.push_back(i);
        mvprintw(0,0,to_string(i).c_str());
        usleep(1e6);
        mvprintw(i,COLS-1,to_string(y[i]).c_str());
        refresh();    
    }
}