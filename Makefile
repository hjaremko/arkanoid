CFLAGS = -std=c++14 -O2 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wmisleading-indentation -Wnull-dereference
# CURSESPATH = <YOUR PATH>

ifndef CURSESPATH
$(error Path to curses is not set)
endif

all:
	g++ $(CFLAGS) main.cpp Entity.cpp Block.cpp Paddle.cpp Ball.cpp Map.cpp -o arkanoid -I$(CURSESPATH) -L$(CURSESPATH) -lpdcurses

