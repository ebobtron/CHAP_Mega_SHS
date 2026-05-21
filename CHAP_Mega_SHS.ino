
/*  -----  CHAP_Mega_SHS  -----  */

// Computer Home Automation Project(CHAP)
// This project built around "CHAP_Mega_SHS" uses an Arduino Mega2560
// clone with CH340 com chip.
// See Readme file:
//   https://github.com/ebobtron/CHAP_Mega_SHS/blob/master/README.md
// A Smart Home System


#include "Display.h"


void setup() {
// put your setup code here, to run once:

#ifdef DISPLAY_H
  Display_Setup();
#endif
}

// burn in testing, millis function timing in loop
uint32_t tick = 0;
unsigned long previousMillis = 0;   // Stores last time the event happened
const long interval = 1000;         // Interval (1 second)
uint32_t loops = 0;


void loop() {

  unsigned long currentMillis = millis(); // Get current time

  // Check if interval has passed
  if ((currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis; // Update the last-triggered time
    tick++;

#ifdef DISPLAY_H
    displayFauxClock(tick);
    displayLoops(loops);

    displayClock(tick / 3600 % 12, tick % 3600 / 60, tick % 60, true);
#endif
  }
  loops++;
}
