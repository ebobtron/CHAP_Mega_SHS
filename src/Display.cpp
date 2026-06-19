
/* ----- Display.cpp ----- */

// Display definitions and implementations for Papa's CHAP(Computer Home
// Automation Project) Smart Home System using  the Arduino Mega2560


// The following in copied from the LCDWIKI_GUI and _KBV libraries
// the 16bit mode only used in the Mega. you must modify the mode in the file
// lcd_mode.h when using the BREAKOUT BOARD only and using these 16 data
// lines to the LCD, pins usage in this implementation is as follows:

/// Display MAR4018 ->  CS CD WR RD RST D0 D1 D2 D3 D4 D5 D6 D7 D8 D9 D10 D11
/// Arduino Mega    ->  40 38 39 43  41 37 36 35 34 33 32 31 30 22 23  24  25

/// Display MAR4018 ->  D12 D13 D14 D15 TP_IRQ MOSI MISO TP_CS EX_CLK
/// Arduino Mega    ->   26  27  28  29   44    51   50    53    52

// Remember to set the pins to suit your display module!

#ifndef DISPLAY_H
#include "../Display.h"
#endif // DISPLAY_H

#include <LCDWIKI_GUI.h>  // Core graphics library
#include <LCDWIKI_KBV.h>  // Hardware-specific display

LCDWIKI_KBV my_lcd(
    NT35510,             // model / display driver IC
         40,             // CS PIN
         38,             // CD PIN
         39,             // WR PIN
         43,             // RD PIN
         41              // RESET PIN
);

void Display_Setup(
    uint8_t screen,
    uint8_t background,
    uint16_t textcolor,
    uint8_t textsize
) {

  my_lcd.Init_LCD();
  // rotation relative to how display pixels are drawn
  my_lcd.Set_Rotation(1);  // rotation default = 0 left to right
                           //                    1 top to bottom
                           //                    2 right to left
                           //                    3 bottom to top

  my_lcd.Set_Draw_color(0xce79);  // gray
  my_lcd.Fill_Screen(screen);
  my_lcd.Set_Text_Back_colour(background);
  my_lcd.Set_Text_colour(textcolor);     // white
  my_lcd.Set_Text_Size(textsize);

  uint8_t lineWidth = 1;       // drawn line width
  uint8_t footpixels = 20;     // one foot = 20 pixels, 20 pixels per foot
                               // one inch = 1.67 pixels per inch
  uint8_t stairWidth = 45 /* inches */ / 12 * 20;
  uint8_t newelPost = 69 /* inches */ / 12 * 20;

}


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
) {

/*
  DRAW_PIXEL,
  DRAW_FAST_VLINE,
  DRAW_FAST_HLINE,
  DRAW_LINE,
  DRAW_RECTANGLE,
  DRAW_ROUND_RECTANGLE,
  DRAW_CIRCLE,          // Draw_Circle(int16_t x, int16_t y, int16_t radius);
  DRAW_CIRCLE_HELPER,
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
*/

  bool on = true, off = false;

  switch(DOL) {
    case DRAW_CIRCLE:
      if (state != on) {
        my_lcd.Set_Draw_color(0, 0, 0);
        my_lcd.Fill_Circle(x, y, r + 8);
        my_lcd.Set_Draw_color(255, 255, 255);
        my_lcd.Draw_Circle(x, y, r);
      }
      else {
        my_lcd.Set_Draw_color(255, 140, 0);
        my_lcd.Fill_Circle(x, y, r);
        my_lcd.Draw_Circle(x, y, r + 4);
        my_lcd.Draw_Circle(x, y, r + 8);
        my_lcd.Set_Draw_color(255, 255, 255);
      }
      break;
    case DRAW_PIXEL:
      break;
    case DRAW_FAST_VLINE:
      for (uint8_t i = 0; i < w; i++) {  // redraw for line width
        my_lcd.Draw_Fast_VLine(x + i, y, l);
      }
      break;
    case DRAW_FAST_HLINE:
      for (uint8_t i = 0; i < w; i++) {  // redraw for line width
        my_lcd.Draw_Fast_HLine(x, y + i, l);
      }
      break;
    case DRAW_LINE:
      break;
    case DRAW_RECTANGLE:
      for (uint8_t i = 0; i < w; i++) {  // redraw for line width
        my_lcd.Draw_Rectangle(x + i, y + i, x2 - i, y2 - i);
      }
      break;
    case sayhello:
      my_lcd.Print_String("Hello", 44, 40);
      break;
    case DRAW_ROUND_RECTANGLE:  // round corner rectangle
      for (uint8_t i = 0; i < w; i++) {  // redraw for line width
        my_lcd.Draw_Round_Rectangle(
          x + i,    // starting x for outer walls
          y + i,    // starting y for outer walls
          x2 - i,   // ending x for outer walls
          y2 - i,   // ending y for outer walls
          r - i     // corner radius
        );
      }
      break;
    default:
      my_lcd.Print_String("Bye-bye", 44, 40);

  }
}

uint32_t seconds;

void displayFauxClock(uint32_t tick) {  // 86400 seconds in a day
  seconds = tick;
  my_lcd.Print_Number_Int(seconds, 40, 152, 6, '0', /* 8, 10 or 16 */ 10);
}

void displayLoops(uint32_t loops) {  // 86400
  my_lcd.Print_Number_Int(loops, 40, 240, 9, '0', /* 8, 10 or 16 */ 10);
}

void displayString(String st) {
  my_lcd.Print_String(st, 40, 350);
}

void displayClock(uint8_t hour, uint8_t minutes, uint8_t seconds, bool h12) {
  char time[9];
  snprintf(time, sizeof(time), "%02u:%02u:%02u", hour, minutes, seconds);
  String timestring = String(time);
  displayString(timestring);
}

