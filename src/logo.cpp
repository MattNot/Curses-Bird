#include "../includes/logo.h"
#include <ncurses.h>
#include <cstdlib>
#include <string>
using namespace std;
string firstMenu[4]={
	"PLAY!",
	"CREDITS",
	"ISTRUCTIONS",
	"EXIT =("
};
//Execute the user input
void selection(int ch)
{
    clear();
    switch(ch)
    {
        case 0:
            play();
            return;
            break;
        case 1: //Copyright stuffs
            mvprintw(LINES/2, COLS/2, "\n Curses Bird  Copyright (C) 2018  Matteo Notaro \n This program comes with ABSOLUTELY NO WARRANTY; \n This is free software, and you are welcome to redistribute it \n under certain conditions; see \"LICENSE\" file for details \n github: MattNot \n LinkedIn: matteo-notaro \n For info you can write me on linkedin or create a issue on github.");
            nodelay(stdscr, false);
            char c;
            while(1){
				c=getch();
				if(c)
				{
					clear();
					return;
				}
			}
            break;
		case 2:
			mvprintw(LINES/2,COLS/2,"\nSPACEBAR->Jump\nIf the bird is red means that you're invincible for just ONE hit. You become invincible every 10 points.");
			nodelay(stdscr,false);
			char d;
			while(1){
				d=getch();
				if(d){
					clear();
					return;
				}
			}
			break;
        case 3:
            endwin();
            exit(1);
            break;
    }
    refresh();
}
int printLogo()
{
    nodelay(stdscr, true);
	int i=1;
	mvprintw(i++,2,R"( _    _      _                            _         )");
	mvprintw(i++,2,R"(| |  | |    | |                          | |        )");
	mvprintw(i++,2,R"(| |  | | ___| | ___ ___  _ __ ___   ___  | |_  ___  )");
	mvprintw(i++,2,R"(| |/\| |/ _ \ |/ __/ _ \| '_ \ _ \ / _ \ |  __/ _ \  )");
	mvprintw(i++,2,R"(\  /\  /  __/ | (_| (_) | | | | | |  __/ | |_| (_) | )");
	mvprintw(i++,2,R"( \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__|\___/  )");
	mvprintw(i++,2,R"(                                                    )");
	mvprintw(i++,2,R"(                                                    )");
	mvprintw(i++,2,R"( _____                           ______ _         _ )");
	mvprintw(i++,2,R"(/  __ \                          | ___ (_)       | |)");
	mvprintw(i++,2,R"(| /  \/_   _ _ __ ___  ___  ___  | |_/ /_ _ __ __| |)");
	mvprintw(i++,2,R"(| |   | | | | '__/ __|/ _ \/ __| | ___ \ | '__/ _  |)");
	mvprintw(i++,2,R"(| \__/\ |_| | |  \__ \  __/\__ \ | |_/ / | | | (_| |)");
	mvprintw(i++,2,R"( \____/\__,_|_|  |___/\___||___/ \____/|_|_|  \__,_|)");
	mvprintw(i++,2,R"(                                                    )");
	mvprintw(i++,2,R"(                                                   )");
	return i;
}
int showFirstMenu(int i)
{
	int choice, highlight=0;
	nodelay(stdscr, false);
	while(1)
	{
		for(int j=0; j<4; j++) //Show the actual choiche
		{
			if(j==highlight)
				wattron(stdscr,A_REVERSE);
			mvprintw(i+j,COLS/2,firstMenu[j].c_str());
			wattroff(stdscr,A_REVERSE);
		}
		choice=getch();
		switch(choice)
		{
			case KEY_UP:
				highlight--;
				if(highlight==-1)
					highlight=0;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight==4)
					highlight=3;
				break;
			default:
				break;
		}
		refresh();
		if(choice==10)
		{
			break;
		}
	}
	nodelay(stdscr, true);
	selection(highlight);
	return -1;
}