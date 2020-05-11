#define COIN "../resources/coin.wav"
#define DEATH "../resources/death.wav"
#define INTRO "../resources/intro.wav"
#define THEME "../resources/Energy Theme.wav"
#define SCORE "../score.dat"

#include <ncurses.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <SFML/Audio.hpp>

#include "../includes/pipe.h"
#include "../includes/logo.h"

using namespace std;
using namespace sf;

//Highscore file
ofstream ofile;
ifstream ifile;

//Sounds
Music music;
Music intro;
SoundBuffer c;
SoundBuffer d;
Sound coin;
Sound death;

Bird* bird; //The bird
vector<Pipe> pipes; //Pipes

int points=0;
int highScore;
long unsigned cycles=0;

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

void setup() // Boring stuffs
{
	//sfml stuffs
	c.loadFromFile(COIN);
	d.loadFromFile(DEATH);
	intro.openFromFile(INTRO);
	music.openFromFile(THEME);
	coin.setBuffer(c);
	death.setBuffer(d);
	intro.setVolume(50);
	intro.setLoop(true);
	music.setVolume(100);
	music.setLoop(true);
	intro.play();
	
	srand(time(0));
	
	//ncurses inizialitazion 
	initscr();
	cbreak();
	keypad(stdscr,TRUE); 
	nodelay(stdscr, true); // true to ignore getch if the user hasn't pressed anything
	noecho();
	curs_set(0);
	start_color();
	//1000 stay for 255 in RGB
	init_color(COLOR_YELLOW,1000,1000, 0); //Don't know why yellow was mustard
	init_color(COLOR_GREEN, 0,   1000, 0);
	init_color(COLOR_BLACK, 0,   0,    0);
	init_color(COLOR_WHITE, 1000,1000,1000);
	init_color(COLOR_RED,   1000,0,    0);
	init_pair (1,COLOR_GREEN,COLOR_BLACK); // Pipe's color pair
	init_pair (2,COLOR_YELLOW,COLOR_BLACK); // Bird's color pair when vulnerable
	init_pair (3,COLOR_RED,COLOR_BLACK); //Bird's color pair when invincible
	bird=new Bird();
}

void restart()
{
	cycles=0;
	delete bird;
	bird=new Bird();
	pipes.clear();
}

void play()
{
	restart();
	intro.stop();
	music.play();
	
	ifile.open(SCORE);
	string hS;
	getline(ifile,hS);
	if(hS != ""){
		highScore=stoi(hS); //string to integer
	}else{
		highScore=0;
	}
	ifile.close();
	ofile.open(SCORE);
	
	int spawnrate=19; //This sets the number of pipes on the screen e.g. 19=4, 15=6;
	bool difficulty=true;
	Pipe* pipe=new Pipe();
	pipes.push_back(*pipe);
	while(true)
	{
		box(stdscr, 0,0);
		mvprintw(0, (COLS/2)-5, "Points: %d",points);
		cycles++; // how many cycles
		// Create a new pipe and push back it into the vector "pipes" only if dicculty hasn't been just changed
		if(cycles%spawnrate==0 && difficulty)
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
				pipes[i].show();
			}

			char c=getch();
			if(c==' ')
			{
				bird->up();
			}
			
			bird->show();
			for(int i=0; i<pipes.size();i++)
			{
				if((pipes[i].isHit(bird) || bird->gety()==LINES-1) && !bird->isInvincible()) //Lose condition
				{
					music.stop();
					death.play();
					clear();
					mvprintw(LINES/2, COLS/2-15, "YOU LOSE! Your points: %d", points);
					mvprintw(LINES/2+1,COLS/2-15,"Last highScore: %d",highScore);
					if(ofile.is_open())
					{
						if(points>highScore)
						{
							ofile<<to_string(points);
							ofile.flush();
							mvprintw(LINES/2+2,COLS/2-15,"New highscore %d", points);
						}else{
							ofile<<highScore;
							ofile.flush();
						}
						ofile.close();
					}
					nodelay(stdscr,false);
					getch();
					clear();
					return;
				}
				else if(pipes[i].isHit(bird)) // if this is true means that you're invincible while you hit a pipe
				{
					bird->setInvincibility(false);
					if(pipes[i].x==bird->getx())
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
					if(pipes[i].x==bird->getx())
					{
						coin.play();
						points++;
						if(points%5==0)
						{
							spawnrate-=2;
							if(spawnrate<2)
								spawnrate=4;
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
	}
	spawnrate=20;
}

int main()
{
	setup();
	start();
	nodelay(stdscr,false);
	endwin();
}
