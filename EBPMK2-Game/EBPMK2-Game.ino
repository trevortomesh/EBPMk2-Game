/// EBPMK2-Game.ino
/// A game framework for the MSP430 Educational Boosterpack MkII
/// (c) Trevor Tomesh, 2016 -- The Unliscense

//-------------------------------
// Using libraries from Rei Vilo:
// http://embeddedcomputing.weebly.com
/// 11/12/2013 10:19
/// version	101
/// @copyright	(c) Rei Vilo, 2013
/// @copyright	CC = BY SA NC
//-------------------------------

/* Core library for code-sense
//We don't need these, either -- for now.
#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif*/

// Include application, user and local libraries
#include <SPI.h>
#include <Screen_HX8353E.h>
Screen_HX8353E draw; // define the screen

// We don't need these libraries -- for now.
//#include <Terminal6e.h>
//#include <Terminal8e.h>
//#include <LCD_screen.h>
//#include <LCD_utilities.h>

// Define variables and constants
#define joystickX 2
#define joystickY 26
uint16_t x, y, x00, y00;
uint16_t color;
uint32_t z;

float i = 0;

// Add setup code
void setup()
{

    draw.begin();
    x00 = 0;
    y00 = 0;
}

// Add loop code
void loop()
{
  // Joystick stuff -- ignore for now.
    x = map(analogRead(joystickX), 0, 4096, 0, 128);
    y = map(analogRead(joystickY), 0, 4096, 128, 0);
    if (x < 1)      x = 1;
    if (x > 106)    x = 106;
    if (y < 1)      y = 1;
    if (y > 126)    y = 126;

    //blackOut();
    draw.clear();
    draw.line(x,125,x+20,125,0b1111111111111111);
    draw.line(x,125,x+10,115,0b1111111111111111);
    draw.line(x+10,115,x+20,125,0b1111111111111111);
    
}

void blackOut(){
  for(int j = 0; j < 126; j++){
    for(int k = 0; k < 126; k++){
    draw.point(j,k,0b000000);
  }
  }


}
