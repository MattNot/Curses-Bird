#include <ncurses.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include "bird.h"
#include "Pipe.h"
#include <cstdlib>
#include <time.h>
//#include <vector>
using namespace std;
Bird* bird;
void setup()
{
	srand(time(0));
	initscr();
	cbreak();
	keypad(stdscr,TRUE);
	//noecho();
	//curs_set(0);
	box(stdscr, 0,0);
	bird=new Bird((int)LINES,(int)COLS);
}

void draw()
{
	Pipe* pipe= new Pipe();
	while(true)
	{
		bird->show();
		//printw(pipe->v);
		//pipe->isHit(bird);
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