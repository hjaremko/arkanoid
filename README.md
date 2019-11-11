# Arkanoid

<p align="center">
  <img src ="https://i.imgur.com/Ly6RPjS.png"/>
</p>

### Requires
- ncurses

### Building on Windows with PDCurses
```
mkdir build && cd build
cmake .. -DCURSES_LIBRARY="pdcurses" -DCURSES_INCLUDE_PATH="<path to pdcurses>
cmake --build .
```
