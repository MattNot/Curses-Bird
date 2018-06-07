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
		points=0;
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
	init_color(COLOR_RED,   1000,0,    0);
	init_pair(1,COLOR_GREEN,COLOR_BLACK); // Pipe's color pair
	init_pair(2,COLOR_YELLOW,COLOR_BLACK); // Bird's color pair when vulnerable
	init_pair(3,COLOR_RED,COLOR_BLACK); //Bird's color pair when invincible
	bird=new Bird();
	start();
}

void restart()
{
	tmp=0;
	bird=new Bird();
	pipes.clear();
}

void play()
{
	restart();
	intro.stop();
	music.play();
	int spawnrate=19; //This sets the number of pipes on the screen e.g. 19=4, 15=6;
	bool difficulty=true;
	Pipe* pipe=new Pipe();
	pipes.push_back(*pipe);
	while(true)
	{
		box(stdscr, 0,0);
		mvprintw(0, (COLS/2)-5, "Points: %d",points);
		tmp++;
		// Create a new pipe and push back it into the vector "pipes" only if dicculty hasn't been just changed
		if(tmp%spawnrate==0 && difficulty)
		{
			Pipe* pipe=new Pipe();
			pipes.push_back(*pipe);
		}
		if(!difficulty)
		{
			difficulty=!difficulty;
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
			if((pipes[0].isHit(bird) || bird->gety()==LINES-1) && !bird->isInvincible()) //Lose condition
			{
				music.stop();
				death.play();
				clear();
				mvprintw(LINES/2, COLS/2-15, "YOU LOSE! Your points: %d", points);
				nodelay(stdscr,false);
				getch();
				return;
			}
			else if(pipes[0].isHit(bird))
			{
				bird->setInvincibility(false);
				if(pipes[0].x==bird->getx())
				{
					points++;
					if(points%5==0)
					{
						spawnrate-=2;
						difficulty=!difficulty;
					}
					if(points%10==0)
					{
						bird->setInvincibility(true);
					}
				}
			}
			else
			{
				if(pipes[0].x==bird->getx())
				{
					points++;
					if(points%5==0)
					{
						spawnrate-=2;
						difficulty=!difficulty;
					}
					if(points%10==0)
					{
						bird->setInvincibility(true);
					}
				}
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