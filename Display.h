
/*  -----  Display.h  -----  */


#ifndef DISPLAY_H
#define DISPLAY_H

struct lamp {
  uint16_t x;  // pixel width
  uint16_t y;  // pixel height
  uint16_t r;  // pixels
  bool state;  // on or off
};


void Display_Setup();

void displayFauxClock(uint32_t tick);   // 86400 seconds in a day

void displayLoops(uint32_t loops);  // 86400

#endif  // DISPLAy_H

