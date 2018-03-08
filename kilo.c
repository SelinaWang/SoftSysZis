/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** data ***/

struct termios orig_termios;

/*** terminal ***/

void die(const char *s) {
	perror(s);
	exit(1);
}

void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
		die("tcsetattr");
	}
}

void enableRawMode() { // turns off echo
	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
		die("tcgetattr");
	}
	atexit(disableRawMode);

	struct termios raw = orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); //disables Ctrl-S and Ctrl-Q and fixes Ctrl-M
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8); // Bit mask, sets char size to 8 bits/byte
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0; // Sets timeout for read.
	raw.c_cc[VTIME] = 1;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
		die("tcsetattr");
	}
}

/*** init ***/

int main() {
	enableRawMode();

	while (1) {
		char c = '\0';
		if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
			die("read");
		}
		if (iscntrl(c)) {
	      printf("%d\r\n", c);
	    } else {
	      printf("%d ('%c')\r\n", c, c); //carriage return and newline
	    }
	    if (c == 'q') break;
	}

  return 0;
}
