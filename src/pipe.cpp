#include "../includes/pipe.h"
#include <ncurses.h>
#include <cstdlib>
Pipe::Pipe(){
    this->x=COLS-1;
    this->speed=1;
    this->spacing=(rand()%4)+4;
    this->finishU=rand()%(LINES-5)+1;
    this->startB=finishU+spacing;
    
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
        refresh();
        attron(COLOR_PAIR(1));
        mvprintw(i,x,"#");
        attroff(COLOR_PAIR(1));
        refresh();
    }
    for(int i=startB-1; i<LINES; i++)
    {
        //y.push_back(i);
        mvprintw(i,x+1," ");
        refresh();
        attron(COLOR_PAIR(1));
        mvprintw(i,x,"#");
        attroff(COLOR_PAIR(1));
        refresh();
    }
}


bool Pipe::isHit(Bird* bird)
{
    if(bird->getx()+1==this->x)
    {
        for(int i=0; i<y.size();i++)
        {
            if(bird->gety()==y[i])
            {
                return true;
            }
        }
        return false;
    }
}