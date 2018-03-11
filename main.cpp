#include <ncurses.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include "bird.h"
#include "Pipe.h"
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
		Pipe* pipe= new Pipe();
		bird->show();
		pipe->isHit(bird);
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