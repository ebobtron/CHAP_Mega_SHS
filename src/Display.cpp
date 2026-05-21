
/*  Display.cpp  */

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


#include "../Display.h"

#include <LCDWIKI_GUI.h>  // Core graphics library
#include <LCDWIKI_KBV.h>  // Hardware-specific display

LCDWIKI_KBV my_lcd(
    NT35510,             // model
         40,             // CS PIN
         38,             // CD PIN
         39,             // WR PIN
         43,             // RD PIN
         41              // RESET PIN
);


bool on = true, off = false;


// initilize lamp controler Icons

lamp L1 = {.x = 770, .y = 30, .r = 12, .state = off};
lamp L2 = {.x = 480, .y = 30, .r = 12, .state = off};

void Display_Setup(
    uint8_t screen,
    uint8_t background,
    uint16_t textcolor,
    uint8_t textsize
) {

  my_lcd.Init_LCD();
  // rotation relative to how display pixels are loaded
  my_lcd.Set_Rotation(1);  // rotation default = 0 left to right
                           //                    1 top to bottom
                           //                    2 right to left
                           //                    3 bottom to top

  my_lcd.Fill_Screen(screen);
  my_lcd.Set_Text_Back_colour(background);
  my_lcd.Set_Text_colour(textcolor);     // white
  my_lcd.Set_Text_Size(textsize);

  // my_lcd.Write_Cmd(0x11);
  // my_lcd.Write_Data(0x44);
  // my_lcd.Write_Cmd(0x51);   // Write Display Brightness
  // my_lcd.Write_Data(0x88);  // 0x88 50% brightness (0x00 = Off, 0xFF = Max)

  uint8_t lineWidth = 1;       // drawn line width
  uint8_t footpixels = 20;     // one foot = 20 pixels, 20 pixels per foot
                               // one inch = 1.67 pixels per foot

  uint8_t stairWidth = 45 /* inches */ / 12 * 20;
  uint8_t newelPost = 69 /* inches */ / 12 * 20;
  my_lcd.Set_Draw_color(0xce79);  // gray
    // 31 = max blue, equivilent to R(0)-G(0)-B(255)

  // draw 1st floor
  for (uint8_t i = 0; i < lineWidth; i++) {  // redraw for line width

    my_lcd.Draw_Round_Rectangle(
        800 - 480 + i,  // starting x for outer walls
        0 + i,          // starting y for outer walls
        799 - i,        // ending x for outer walls
        479 - i,        // ending y for outer walls
        20 - i          // corner radius
    );
    // draw stair chase
    my_lcd.Draw_Fast_VLine(
        800 - 480 + stairWidth + i,  // x start position
        newelPost,                   // y start position
        round(8 * 16.7) + lineWidth  // line length
    );

    for (uint8_t j = 0; j <= 8; j++) {  // draw stairs to 2nd floor

      my_lcd.Draw_Fast_HLine(
          320,
          newelPost + 16.7 * j + i,  // 10 inches * 1.67
          stairWidth
      );
    }

    // draw center east west wall thin
    my_lcd.Draw_Rectangle(
        800 - 480 + stairWidth + i,
        newelPost + round(8 * 16.7) + lineWidth,
        799 - lineWidth,
        newelPost + 144/* see#3 */ + lineWidth
    );

    /*
     *  #3  value 144 = round(8 * 16.7) + round(6 * 1.67)
     *
     *
     */


    my_lcd.Draw_Circle(L1.x, L1.y, L1.r);  // draw gray circle
    my_lcd.Draw_Circle(L2.x, L2.y, L2.r);  // draw gray circle

    /*
    my_lcd.Set_Draw_color(my_lcd.Color_To_565(255, 255, 0)); // color to yellow
    my_lcd.Fill_Circle(480, 30, 12);   // draw a filled circle
    my_lcd.Set_Draw_color(my_lcd.Color_To_565(0, 0, 0));  // color to black
    my_lcd.Fill_Circle(480, 30, 12);   // draw over yellow circle with black

    my_lcd.Set_Draw_color(0xce79);   // color to gray
    my_lcd.Draw_Circle(480, 30, 12);   // draw the gray circle
    */

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

