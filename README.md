# led music rework
Music visualizer
Idea and execution by UsatiyNyan
## code for rpi 4
https://github.com/UsatiyNyan/ledmusicreworkembedded
## preview of desktop
[![desktop preview](https://img.youtube.com/vi/wxvgvQ8Cv6c/0.jpg)](https://www.youtube.com/watch?v=wxvgvQ8Cv6c "desktop preview")
## preview of embedded rpi
[![led preview](https://img.youtube.com/vi/zalfF9knbv4/0.jpg)](https://www.youtube.com/watch?v=zalfF9knbv4 "led preview")
## NOTE
App is written with Qt version 5.13.2 (you might need to install Qt5::SerialPort additionally).
PulseAudio sound server is used to read from soundcard(it might be already installed on your computer).
Choose sound card which has `.monitor` in it's name) 
## known bugs
1) polygons are not working for now (expansion is not working properly)
2) changing size of LED matrix through desktop causes SEGFAULT;) (feel free to change defaults in code which is pretty self explanatory)
3) might crash if you choose wrong audio source
4) with dark theme checkbox on the left side of `enable preview` becomes invisible
![on the left](https://github.com/UsatiyNyan/ledmusicrework/blob/master/missing_checkbox.png?raw=true) 
## HOW TO BUILD
```
git submodule update --init
mkdir build
cd build
cmake ..
make
```
or just build target led_player
## HOW TO RUN
in your build directory
```
cd build
cd project
./led_player
```
and then play with it! don't forget about <b>invisible</b> checkbox on the left side of `enable preview` in the bottom right corner
