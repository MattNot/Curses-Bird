#include <ncurses.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include "../includes/pipe.h"
#include "../includes/logo.h"
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
	start_color();
			//R	, G	 , B
	init_color(COLOR_YELLOW,1000,1000, 0); //Don't know why yellow was mustard
	init_color(COLOR_GREEN, 0,   1000, 0);
	init_color(COLOR_BLACK, 0,   0,    0);
	init_color(COLOR_WHITE, 1000,1000,1000);
	init_pair(1,COLOR_GREEN,COLOR_BLACK); // Pipes color pair
	init_pair(2,COLOR_YELLOW,COLOR_BLACK); // Bird color pair
	
	box(stdscr, 0,0);
	bird=new Bird((int)LINES,(int)COLS);
	int state=1;
	int k=printLogo();
	state=showFirstMenu(k);
}

void play()
{
	int spawnrate=20; //This sets the number of pipes on the screen e.g. 20=4, 15=6;
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
		if(pipes.size()>0)
		{
			if(pipes[0].x<0)
			{   
				//Delete and pop the pipe if it gets out the screen
				pipes.erase(pipes.begin());
			}
			for(int i=0; i<pipes.size();i++)
			{
				pipes[i].show();
			}

			if(pipes[0].isHit(bird) || bird->gety()==LINES-1) //Lose condition
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
			char c=getch();
			if(c==' ')
			{
				bird->up();
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