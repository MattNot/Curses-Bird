string firstMenu[3]={
	"PLAY!",
	"CREDITS",
	"EXIT =("
};
string playMenu[5]={
	"Easy",
	"Medium",
	"Hard",
	"Go back!",
	"1MP0551BL3"
};
void play();
int showFirstMenu(int);
int printLogo();
void selection(int);
void selection(int ch)
{
    clear();
    mvprintw(0,0,"%d",ch);
    switch(ch)
    {
        case 0:
            play();
            return;
            break;
        case 1:
            mvprintw(LINES/2, COLS/2, "\n Curses Bird  Copyright (C) 2018  Matteo Notaro \n This program comes with ABSOLUTELY NO WARRANTY; \n This is free software, and you are welcome to redistribute it \n under certain conditions; see \"LICENSE\" file for details \n github: MattNot \n LinkedIn: matteo-notaro \n For info you can write me on linkedin or create a issue on github.");
            nodelay(stdscr, false);
            char c;
            while(1){c=getch(); if(c){clear(); showFirstMenu(printLogo());}}
            break;
        case 2:
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
	mvprintw(i++,0,R"( _    _      _                            _         )");
	mvprintw(i++,0,R"(| |  | |    | |                          | |        )");
	mvprintw(i++,0,R"(| |  | | ___| | ___ ___  _ __ ___   ___  | |_  ___  )");
	mvprintw(i++,0,R"(| |/\| |/ _ \ |/ __/ _ \| '_ \ _ \ / _ \ |  __/ _ \  )");
	mvprintw(i++,0,R"(\  /\  /  __/ | (_| (_) | | | | | |  __/ | |_| (_) | )");
	mvprintw(i++,0,R"( \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__|\___/  )");
	mvprintw(i++,0,R"(                                                    )");
	mvprintw(i++,0,R"(                                                    )");
	mvprintw(i++,0,R"( _____                           ______ _         _ )");
	mvprintw(i++,0,R"(/  __ \                          | ___ (_)       | |)");
	mvprintw(i++,0,R"(| /  \/_   _ _ __ ___  ___  ___  | |_/ /_ _ __ __| |)");
	mvprintw(i++,0,R"(| |   | | | | '__/ __|/ _ \/ __| | ___ \ | '__/ _  |)");
	mvprintw(i++,0,R"(| \__/\ |_| | |  \__ \  __/\__ \ | |_/ / | | | (_| |)");
	mvprintw(i++,0,R"( \____/\__,_|_|  |___/\___||___/ \____/|_|_|  \__,_|)");
	mvprintw(i++,0,R"(                                                    )");
	mvprintw(i++,0,R"(                                                   )");
	return i;
}
int showFirstMenu(int i)
{
	//clear();
	int choice, highlight=0;
	while(1)
	{
		for(int j=0; j<3; j++)
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
				if(highlight==3)
					highlight=2;
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
    selection(highlight);
	return -1;
}