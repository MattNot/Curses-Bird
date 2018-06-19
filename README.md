# Curses-Bird

A Flappy bird clone using ncurses and c++. Project done for ICT exam at Università della Calabria (https://www.mat.unical.it/demacs)

In order to build you have to install CMake.

https://cmake.org/download/

If you are missing same libraries it will say to you what do you need. In general you have to install nCurses and SFML

```
sudo apt-get install libsfml-dev
sudo apt-get install libncurses-dev
```

Then you have to create a `build` folder go into it and type in a terminal

```cmake .. && make```

then type
```
./cursesbird
```

Enjoy!

Don't forget to open an issue if you get bugs or glitches!

Next project: A "simple" Neural network using TensorFlow for the bird!


IMPORTANT:
This project requires C++11 and has been developed and tested on Ubuntu 18.04 LTS and 16.
On Lubuntu 16 and Xubuntu 16 there are some graphical glitches caused by nCurses and how it works with different terminal emulator.
If your compiler doesn't have c++11 as a standard then you have compile it manually. Go into the `src` folder and type in a terminal
```
g++ *.cpp -lncurses -lsfml-audio -o cursesbird -std=c++11
```

Thanks to http://thecodingtrain.com/ (Daniel Shiffman (http://shiffman.net/)) and the Processing foundation for the idea and the amazing work they do.
