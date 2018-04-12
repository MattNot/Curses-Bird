#include <ncurses.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include "./lib/bird.h"
#include "./lib/Pipe.h"
#include "./lib/logo.h"
using namespace std;

Bird* bird; //The bird
vector<Pipe> pipes; //Pipes
int points=0;
long unsigned tmp=0;

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
	int state=1;
	int k=printLogo();
	state=showFirstMenu(k);
}
void play()
{
	int spawnrate=20; //This sets the number of pipes on the screen e.s. 20=4, 15=6;
	Pipe* pipe=new Pipe();
	pipes.push_back(*pipe);
	while(true)
	{
		box(stdscr, 0,0);
		mvprintw(0, (COLS/2)-5, "Points: %d",points);
		tmp++;
		// Create a new pipe and push back it into the vector "pipes"
 		if(tmp%spawnrate==0)
		{
			Pipe* pipe=new Pipe();
			pipes.push_back(*pipe);
		}

		bird->show();
		
		// Avoid some coredump bugs
		if(pipes.size()>0){
			if(pipes[0].x<0)
			{   
				//Delete and pop the pipe if it gets out the screen
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
				if(pipes[i].isHit(bird)) //Lose condition
				{
					clear();
					mvprintw(LINES/2, COLS/2-15, "YOU LOSE! Your points: %d", points);
					nodelay(stdscr,false);
					getch();
					return;
				}
				else
				{
					points++;
				}
			}
		}
	}
}

int main()
{
	setup();
	nodelay(stdscr,false);
	endwin();
}