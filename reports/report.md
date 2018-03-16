# Text Editor in C
## Software Systems Project 1
### Zarin Bhuiyan and Ziyu (Selina) Wang
#### March 16th, 2018

## Project Goals

The goal of our project was to create a text editor in C. We achieved the original MVP goals for our project. We were able to implement all the basic features one might expect in a minimal text editor, including writing text (raw input/output), being able to view text, saving the text file, and some other features. We also completed a stretch goal - implementing a search feature. If we had more time, we would have completed our two other stretch goals: implementing syntax highlighting and exploring the ncurses library to make our program more portable.

## Learning Goals

Our learning goals involved learning C more intimately as well as learning how exactly to build a text editor from scratch. We think we did achieve our learning goals, as we understand C much better than we used to, and learned a lot about how one would make a text editor. 

## Resources

We used an online guide (https://viewsourcecode.org/snaptoken/kilo/index.html) linked from the SoftSys project resources page. We didn't need any other resources, as this one was plenty helpful for making a beginner text editor.

## End Product

We have a complete text editor with search functionality working, with about 800 lines of code. 

We learned some things about these libraries:

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

Here are a few important functions that we implemented that do different things.


Here is the function for saving a text file:

---
void editorSave() {
  if (E.filename == NULL) {
  	E.filename = editorPrompt("Save as: %s (ESC to cancel)", NULL);
    if (E.filename == NULL) {
      editorSetStatusMessage("Save aborted");
      return;
    }  
  }

  int len;
  char *buf = editorRowsToString(&len);
  int fd = open(E.filename, O_RDWR | O_CREAT, 0644);
  if (fd != -1) {
    if (ftruncate(fd, len) != -1) {
      if (write(fd, buf, len) == len) {
        close(fd);
        free(buf);
        E.dirty = 0;
        editorSetStatusMessage("%d bytes written to disk", len);
        return;
      }
    }
    close(fd);
  }
  free(buf);
  editorSetStatusMessage("Can't save! I/O error: %s", strerror(errno));
}
---


Here is the function for scrolling through our editor:

---
void editorScroll() {
	E.rx = 0;
	if (E.cy < E.numrows) {
		E.rx = editorRowCxToRx(&E.row[E.cy], E.cx);
	}

	if (E.cy < E.rowoff) {
     E.rowoff = E.cy;
  	}
  	if (E.cy >= E.rowoff + E.screenrows) {
    	E.rowoff = E.cy - E.screenrows + 1;
    }
	if (E.rx < E.coloff) {
		E.coloff = E.rx;
	}
	if (E.rx >= E.coloff + E.screencols) {
		E.coloff = E.rx - E.screencols + 1;
	}
}
---

And here's the function for getting window size:

---
int getWindowSize(int *rows, int *cols) {
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
	    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
	    return getCursorPosition(rows, cols);
	} else {
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return 0;
	}
}
---

Please view kilo.c for more. Run the file's output to try out our text editor! 



## Outcome

We definitely felt like we achieved our learning goals as we both are more comfortable with writing C code and we learned a lot about the basics of how text editors work. We achieved the lower bound we originally defined and were also able to implement one of our three stretch goals in the alotted time. 