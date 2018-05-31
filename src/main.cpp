#include <ncurses.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include "../includes/pipe.h"
#include <SFML/Audio.hpp>
#include "../includes/logo.h"
using namespace std;
using namespace sf;

Music music;
Music intro;
SoundBuffer c;
SoundBuffer d;
Sound coin;
Sound death;
Bird* bird; //The bird
vector<Pipe> pipes; //Pipes
int points=0;
long unsigned tmp=0;
void start()
{
	while(1)
	{
		box(stdscr, 0,0);
		int k=printLogo();
		int x=showFirstMenu(k);
	}
}
void setup()
{
	c.loadFromFile("../resources/coin.wav");
	d.loadFromFile("../resources/death.wav");
	intro.openFromFile("../resources/intro.wav");
	music.openFromFile("../resources/Energy Theme.wav");
	coin.setBuffer(c);
	death.setBuffer(d);
	intro.setVolume(50);
	intro.setLoop(true);
	music.setVolume(100);
	music.setLoop(true);
	intro.play();
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
	init_pair(1,COLOR_GREEN,COLOR_BLACK); // Pipe's color pair
	init_pair(2,COLOR_YELLOW,COLOR_BLACK); // Bird's color pair
	bird=new Bird();
	start();
}

void restart()
{
	bird=new Bird();
	pipes.clear();
}
void play()
{
	restart();
	intro.stop();
	music.play();
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
		if(((points+1)%5)==0) //Add linear difficulty every 5 points
		{
			spawnrate-=2;
		}
		// Avoid some coredump failure
		if(pipes.size()>0)
		{
			if(pipes[0].x<0)
			{   
				//Delete and pop the pipe if it gets out the screen, I could use queue but I'm more confident with vector instead
				pipes.erase(pipes.begin());
			}
			for(int i=0; i<pipes.size();i++)
			{
				if(pipes[i].x==bird->getx())
					coin.play();
				pipes[i].show();
			}
			char c=getch();
			if(c==' ')
			{
				bird->up();
			}
			bird->show();
			if(pipes[0].isHit(bird) || bird->gety()==LINES-2) //Lose condition
			{
				music.stop();
				death.play();
				clear();
				mvprintw(LINES/2, COLS/2-15, "YOU LOSE! Your points: %d", points);
				nodelay(stdscr,false);
				getch();
				return;
			}
			else
			{
				if(pipes[0].x==bird->getx())
				points++;
			}
		}
	}
	spawnrate=20;
}

int main()
{
	setup();
	nodelay(stdscr,false);
	endwin();
}
