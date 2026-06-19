
/* ----- Display.h ----- */

// Connecting and interfacing an LCDWIkI described 800 x 480 TFT display
// board/shield in this case a MAR4018 touch screen with SD card slot like that
// at https://www.lcdwiki.com/4.0inch%20Arduino%20Display-Mega2560%20NT35510.
// It is important to download the libraries LCDWIKI_GUI and LCDWIKI_KBV from
// the page shown above as the libraries found in other locations on the
// LCDWIKI site don't appear to support this board

// LCDWIKI_GUI and LCDWIKI_KBV from LCDWIKI.COM

#include <Arduino.h>

#ifndef DISPLAY_H
#define DISPLAY_H


/*  */



enum dobjlist {
  DRAW_PIXEL,
  DRAW_FAST_VLINE,
  DRAW_FAST_HLINE,
  DRAW_LINE,
  DRAW_RECTANGLE,
  DRAW_ROUND_RECTANGLE,
  DRAW_CIRCLE,
  DRAW_CIRCLE_HELPER,
  sayhello,
  DRAW_TRIANGLE,
  DRAW_BITMAP,
  DRAW_CHAR,
  FIRST_F_OUTLINE,
  STAIR_CASE,
  STAIRS,
  WALL_DIVIDER,
  LAMP_1,
  LAMP_2,
  END
};

struct lamp {    // represents a light unfilled circle
  uint16_t x;    // position 0 - 799 pixels left / right
  uint16_t y;    // Position 0 - 479 pixels up / down
  uint16_t r;    // radius in pixels
  bool state;    // on or off  on = filled colored circle
};


void DrawObjects(           // must I explain  ??
    dobjlist DOL,   // item to draw
    uint16_t  x,    // horizontal position   0 - 799
    uint16_t  y,    // vertical position     0 - 479
    uint16_t x2,    // horizontal end position
    uint16_t y2,    // vertical end position
    uint8_t   w,    // line width pixels
    uint16_t  r,    // radius value circle or corner in pixels
    uint16_t  l,    // length in pixels
    bool state      // item displayed on or off
);




void Display_Setup(
    uint8_t screen     = 0x0000, // Fill Screen black
    uint8_t background = 0x0000, // Back Ground Color black
    uint16_t textcolor = 0xffff, // Text Color white)
    uint8_t textsize   = 0x0004  // Text Size 4
);


void displayString(String st);

void displayFauxClock(uint32_t tick);   // 86400 seconds in a day

void displayLoops(uint32_t loops);

void displayString(String st);

void displayClock(
                   uint8_t hour,
                   uint8_t minutes,
                   uint8_t seconds,
                   bool h12
                  );

#endif // DISPLAY_H







