#include "../includes/bird.h"
#include <ncurses.h>
#include <unistd.h>

Bird::Bird()
{
    this->y=LINES/2;
    this->x=5;
    this->shape="\'*\'";
    this->gravity=1;
    this->lift=4;
    this->isUp=false;
    this->invincibility=false;
}

bool Bird::isInvincible(){return invincibility;}
bool Bird::setInvincibility(bool t){this->invincibility=t;}
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
    if(!invincibility){
        attron(COLOR_PAIR(2));
        mvprintw(this->y,this->x,this->shape.c_str());
        attroff(COLOR_PAIR(2));
    }else{
        attron(COLOR_PAIR(3));
        mvprintw(this->y,this->x,this->shape.c_str());
        attroff(COLOR_PAIR(3));
    }
    refresh();
}

void Bird::show()
{
	this->update();
	usleep((2e4)*6);
    if(!invincibility){
        attron(COLOR_PAIR(2));
        mvprintw(this->y,this->x,this->shape.c_str());
        attroff(COLOR_PAIR(2));
    }else{
        attron(COLOR_PAIR(3));
        mvprintw(this->y,this->x,this->shape.c_str());
        attroff(COLOR_PAIR(3));
    }
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