#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <ncurses.h>
#include <dirent.h>
#include <fstream>
#include <cstring>

int main(int argc, char* argv[])
{
	// read program parameters
	// TODO

	// get ~/.tasklist string
	char* homedir = getenv("HOME");
	if (homedir == nullptr) // if env var is unset
		homedir = getpwuid(getuid())->pw_dir; // get dynamic info
	strcat(homedir, "/.tasklist");

	// open ~/.tasklist directory
	DIR* dir = opendir(homedir);
	if (dir == nullptr) // if not found
	{
		if (mkdir(homedir, 0755) == 0) // try to create it
			dir = opendir(homedir); // open again

		if (dir == nullptr) // if failed, quit
		{
			std::cerr << "Unable to open or create " << homedir << std::endl;
			return -1;
		}
	}

	// initialize ncurses
	initscr(); // create console window
	raw(); // disable line buffering and controls
	noecho(); // disable user input echoing
	keypad(stdscr, true); // enable function keys and arrows

	while (struct dirent* dir_info = readdir(dir)) // foreach file in ~/.tasklist
	{
		if (dir_info->d_type == DT_REG) // if it's a regular file
			printw("%s\n", dir_info->d_name); // print its name
	}
	refresh(); // update screen display

	// close directory and ncurses
	closedir(dir);
	getch();
	endwin();

	return 0;
}
