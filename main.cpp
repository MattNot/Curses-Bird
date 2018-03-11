#include <ncurses.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include "bird.h"
using namespace std;
Bird* bird;
void setup()
{
	initscr();
	cbreak();
	keypad(stdscr,TRUE);
	noecho();
	curs_set(0);
	box(stdscr, 0,0);
	bird=new Bird((int)LINES,(int)COLS);
}

void draw()
{
	while(true)
	{
		bird->show();
		refresh();
	}
}

int main()
{
	setup();
	draw();
	getch();
	endwin();
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