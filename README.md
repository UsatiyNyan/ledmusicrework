# led music rework
Music visualizer
Idea and execution by UsatiyNyan
## code for rpi 4
https://github.com/UsatiyNyan/ledmusicreworkembedded
## preview of desktop
https://www.youtube.com/watch?v=wxvgvQ8Cv6c
## preview of embedded rpi
https://www.youtube.com/watch?v=zalfF9knbv4
## NOTE
App is written with Qt version 5.13.2 (you might need to install Qt5::SerialPort additionally).
PulseAudio sound server is used to read from soundcard(it might be already installed on your computer).
## known bugs
1) polygons are not working for now (expansion is not working properly)
2) changing size of LED matrix through desktop causes SEGFAULT;) (feel free to change defaults in code which is pretty self explanatory)
