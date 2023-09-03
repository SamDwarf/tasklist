#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ncurses.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>

char *tl_path() // returns "~/.tasklist" string
{
	char *path = getenv("HOME");
	if (path == NULL) // if environment var is unset
		path = getpwuid(getuid())->pw_dir; // get dynamic info
	strcat(path, "/.tasklist");

	return path;
}

DIR *open_or_create(const char* path)
{
	DIR *dir = opendir(path);
	if (dir == NULL) // if not found
	{
		if (mkdir(path, 0755) == 0) // try to create it
			dir = opendir(path); // open again

		if (dir == NULL) // if failed, quit
		{
			fprintf(stderr, "Unable to open or create %s\n", path);
			exit(EXIT_FAILURE);
		}
	}

	return dir;
}

void init_screen()
{
	// init ncurses
	initscr(); // create console window
	raw(); // disable line buffering and controls
	noecho(); // disable user input echoing
	keypad(stdscr, TRUE); // enable function keys and arrows
	
	// print title and help
	// TODO
}

int main(int argc, char *argv[])
{
	// read program parameters
	// TODO

	DIR *tl_dir = open_or_create(tl_path()); // get tasklist home directory
	init_screen();
 
	// display lists
	struct dirent *entry = NULL;
	while ((entry = readdir(tl_dir)) != NULL) // foreach file in ~/.tasklist
	{
		if (entry->d_type == DT_REG) // if it's a regular file
			printw("%s\n", entry->d_name); // print its name
	}

	refresh(); // update screen display
	getch(); // wait for entry

	// close directory and ncurses
	closedir(tl_dir);
	endwin();

	return EXIT_SUCCESS;
}
