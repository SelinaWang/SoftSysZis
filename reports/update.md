# Text Editor in C Proposal
## Software Systems Project 1
### Zarin Bhuiyan and Ziyu (Selina) Wang
#### March 9th, 2018

## Project Goals

The goal of our project is to create a text editor in C. The lower bound of our project is that it should ideally be able to implement all the basic features one might expect in a minimal editor, including writing text (raw input/output) and being able to view text. Our stretch goals include implementing syntax highlighting and a search feature. Another stretch goal we hope to explore is looking into the ncurses library to take care of a lot of the low level terminal interaction for us to make our program more portable.

## Learning Goals

Our learning goals include learning C more intimately as well as learning how exactly to build a text editor from scratch. Hopefully by the end of the project we would both be proficient at C. If we do look into additional libraries, it would give us more exposure into what C libraries can do for us.

## Resources

We plan to use an online guide (https://viewsourcecode.org/snaptoken/kilo/index.html) linked from the SoftSys project resources page. We may need to look into more online resources for the stretch goals, depending on which we plan to explore. We believe we won't need more resources.

## Current Progress

We are working on completing raw mode. We currently have keypresses logged and echoing working. Next we will turn off all output processing signals as well as Ctrl signals (Ctrl-Z, Ctrl-Q, etc). With this task, a few tests proving that these signals are properly turned off is how we might define "done". We plan to collaborate on these tasks together.
