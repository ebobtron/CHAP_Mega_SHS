
/*  -----  Display.h  -----  */

// Connecting and interfacing an LCDWIki 800 x 480 tft display
// board/shield in this case a MAR4018 touch screen with SD card slot like that
// at https://www.lcdwiki.com/4.0inch%20Arduino%20Display-Mega2560%20NT35510.
// It is important to download the libraries LCDWIKI_GUI and LCDWIKI_KBV from
// the page shown above as the libraries found in other locations on the 
// LCDWIKI site don't appear to support this board

// LCDWIKI_GUI and LCDWIKI_KBV from LCDWIKI.COM

#include <Arduino.h>

#ifndef DISPLAY_H
#define DISPLAY_H

struct lamp {
  uint16_t x;  // pixel width
  uint16_t y;  // pixel height
  uint16_t r;  // pixels
  bool state;  // on or off
};

void Display_Setup(
    uint8_t screen= 0x0000, // Fill Screen black
    uint8_t background = 0x0000, // Back Ground Color black
    uint16_t textcolor = 0xffff, // Text Color white)
    uint8_t textsize = 0x0004  // Text Size 4
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







