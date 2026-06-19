
/* ----- CHAP_Mega_SHS ----- */

// Computer Home Automation Project(CHAP)
// This project built around "CHAP_Mega_SHS" uses an Arduino Mega2560
// clone with CH340 com chip.
// See the read me file:
//   https://github.com/ebobtron/CHAP_Mega_SHS/blob/master/README.md
// A Smart Home System

bool on = true, off = false;

// the following header files expose library functions for hardware
// using libraries WIKILCD_GUI
// comment out if not used
#include "Display.h"


// lamps represent remote devices that power lighting on and off
lamp L1 = {.x = 769, .y = 30, .r = 12, .state = off};
lamp L2 = {.x = 480, .y = 30, .r = 12, .state = off};

#include "SHS.h"

void setup() {

#ifdef DISPLAY_H
  uint8_t stairWidth = 45 /* inches */ / 12 * 20;
  uint8_t newelPost = 69 /* inches */ / 12 * 20;  // begining point



  Display_Setup();

  // Draw Objects (DOL,   x,   y,    x2,    y2,   w,   r,   l,   state);

  // draw first floor outline
  DrawObjects(DRAW_ROUND_RECTANGLE, 800 - 480, 0, 799, 479, 3, 20, 0, on);

  // draw stair chase inboard wall
  DrawObjects(
      DRAW_FAST_VLINE, 800 - 480 + stairWidth, newelPost,
      0, 0, 1, 0, round(8 * 16.7), on
  );

  // draw steps  (8 steps 9 lines)
  uint8_t steps = 8;
  for (uint8_t j = 0; j <= steps; j++) {
    DrawObjects(
        DRAW_FAST_HLINE,              // draw function
        /*x*/  320,                   // Horz from point
        /*y*/  newelPost + 16.7 * j,  // Vert from point
        /*x2*/ 0,                     // Horz to point
        /*y2*/ 0,                     // Vert to point
        /*w*/  1,                     // line width in pixels
        /*r*/  0,                     // radius in pixels
        /*l*/  stairWidth,            // length for fast lines in pixels
        /*state*/ on                  // display item on or off
    );
  }

  // draw center east west wall thin
  DrawObjects(
      DRAW_RECTANGLE,
      800 - 480 + stairWidth,
      newelPost + round(8 * 16.7),
      799,
      newelPost + 144 /* see#3 */,
      1,
      0,
      0,
      on
  );
     /*
      *  #3  value 144 = round(8 * 16.7) + round(6 * 1.67)
      */

  DrawObjects(DRAW_CIRCLE, L1.x, L1.y, 0, 0, 1, L1.r, 0, L1.state);
  DrawObjects(DRAW_CIRCLE, L2.x, L2.y, 0, 0, 1, L1.r, 0, L2.state);


  // DrawObjects(
  //    DOL,/*x*/x,/*y*/y,/*x2*/x2,/*y2*/y2,/*w*/w,/*r*/r,/*l*/l,/*state*/1
  // );

  DrawObjects(sayhello,0,0,0,0,0,0,0,0);

#endif // DISPLAY_H

}

// globals for loop
uint32_t tick = 0;
unsigned long previousMillis = 0;   // Stores last time the event happened
const long interval = 1000;         // Interval (1 second)
uint32_t loops = 0;


void loop() {
  if(tick % 2) {
    L1.state = on;
    L2.state = off;
  }
  else {
    L1.state = off;
    L2.state = on;
  }
  unsigned long currentMillis = millis(); // Get current time

  // Check if interval has passed
  if ((currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis; // Update the last-triggered time
    tick++;

#ifdef DISPLAY_H
    updateDeviceState();
    displayFauxClock(tick);
    displayLoops((loops % 4294967295) / 10000);
    displayClock(tick / 3600 % 12, tick % 3600 / 60, tick % 60, true);
#endif

  }
  loops++;
}
