CFLAGS = -std=c++14 -O2 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wmisleading-indentation -Wnull-dereference
CURSESPATH = C:/Users/Hubert/Dropbox/C++/Biblioteki/pd

all:
	g++ $(CFLAGS) main.cpp Block.cpp Paddle.cpp Ball.cpp Map.cpp -o arkanoid -I$(CURSESPATH) -L$(CURSESPATH) -lpdcurses
# g++ main.cpp -o arkanoid -lncurses
	