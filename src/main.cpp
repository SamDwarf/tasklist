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
	//TODO

	// create .tasklist directory if not found
	char* homedir = getenv("HOME");
	if (homedir == nullptr)
		homedir = getpwuid(getuid())->pw_dir;
	strcat(homedir, "/.tasklist");

	DIR* dir = opendir(homedir);
	if (dir == nullptr)
	{
		if (mkdir(homedir, 0755) == 0)
			dir = opendir(homedir);

		if (dir == nullptr)
		{
			std::cerr << "Unable to open or create " << homedir << std::endl;
			return -1;
		}
	}

	// initialize ncurses if needed
	initscr();
	
	while (struct dirent* dir_info = readdir(dir)) // foreach file in ~/.tasklist
	{
		if (dir_info->d_type == DT_REG) // if it's a regular file
			printw("%s\n", dir_info->d_name); // print its name
	}
	refresh();

	// close ncurses

	closedir(dir);
	getch();
	endwin();

	return 0;
}
