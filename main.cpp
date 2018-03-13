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
vector<Pipe> pipes;
void setup()
{
	srand(time(0));
	initscr();
	cbreak();
	keypad(stdscr,TRUE);
	nodelay(stdscr, true);
	noecho();
	curs_set(0);
	box(stdscr, 0,0);
	bird=new Bird((int)LINES,(int)COLS);
}

void draw()
{
	Pipe* pipe=new Pipe();
	pipes.push_back(*pipe);
	while(true)
	{
		if(clock()%15==0){
			Pipe* pipe=new Pipe();
			pipes.push_back(*pipe);
		}
		bird->show();
		if(pipes[0].x<0)
		{
			pipes.erase(pipes.begin());
		}
		char c=getch();
		if(c==' ')
		{
			bird->up();
		}
		for(int i=0; i<pipes.size();i++)
		{
			pipes[i].show();
			if(pipes[i].isHit(bird))
			{
				return;
			}
		}
		refresh();
	}
}

int main()
{
	setup();
	draw();
	nodelay(stdscr,false);
	getch();
	endwin();
}