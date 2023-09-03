#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <ncurses.h>

int main()
{
	initscr();

	const char* homedir;

	if ((homedir = getenv("HOME")) == nullptr)
	{
		printw("ok\n");
		homedir = getpwuid(getuid())->pw_dir;
	}

	printw("%s", homedir);
	printw("\n");
	refresh();

	getch();
	endwin();

	return 0;
}
