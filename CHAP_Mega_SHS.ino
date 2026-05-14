
/*  -----  CHAP_Mega_SHS  -----  */

// Computer Home Automation Project(CHAP)
// This project built around "CHAP_Mega_SHS" uses an Arduino Mega2560
// clone using CH340 com chip.
// The Smart Home System


#include "Display.h"



// #ifndef DISPLAY_SETUP_H



// for testing millis function timing in loop
uint32_t tick = 0;
unsigned long previousMillis = 0;   // Stores last time the event happened
const long interval = 500;          // Interval (1/8 second)


void setup() {
// put your setup code here, to run once:

#ifdef DISPLAY_H
  Display_Setup();
#endif
}

uint32_t loops =  987654321;
void loop() {

  unsigned long currentMillis = millis(); // Get current time

  // Check if interval has passed
  if ((currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis; // Update the last-triggered time
    tick++;
    
#ifdef DISPLAY_H
    displayFauxClock(tick);
    displayLoops(loops);
#endif
  }
  loops++;
}
