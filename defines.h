#ifndef __pacman_def__
#define __pacman_def__

#define WIDTH 380
#define HEIGHT 260
#define ROWS 13
#define COLS 19
const float WX = WIDTH*1.0/COLS;
const float WY = HEIGHT*1.0/ROWS;

const float SPEEDX = 2.5*WX;
const float SPEEDY = 2.5*WY;
const float gSPEEDX = 2.2*WX;
const float gSPEEDY = 2.2*WY;

const float PACSIZE = WX*0.45;

#endif
