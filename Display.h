
/*  -----  Display.h  -----  */

// this file is a container for interfacing a 800 x 480 tft display
// providing declarations for the use of of the libraries
// LCDWIKI_GUI and LCDWIKI_KBV from LCDWIKI


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

void displayLoops(uint32_t loops);

#endif  // DISPLAy_H

