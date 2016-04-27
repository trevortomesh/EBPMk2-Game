/*
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
*/

#include "Energia.h"

// Include application, user and local libraries
#include <SPI.h>
#include <LCD_screen.h>
#include <LCD_screen_font.h>
#include <Screen_HX8353E.h>
#include "Energia.h"
void setup();
void loop();
void input();
void update();
void render();
void gameOver();
#line 22
Screen_HX8353E draw;



// Define variables and constants
#define joystickX 2
#define joystickY 26
float x, y, x00, y00, t; 
int score;

float ballx, bally;
float ballx0, bally0;
float ballvx, ballvy;

bool count = true; 

// Add setup code
void setup()
{
    // By default MSP432 has analogRead() set to 10 bits. 
    // This Sketch assumes 12 bits. Uncomment to line below to set analogRead()
    // to 12 bit resolution for MSP432.
    //analogReadResolution(12);

    draw.begin();
    x00 = 0;
    y00 = 0;
	
    ballx0 = 126/2; 
    bally0 = 126/2;

    ballx = 126/2;
    bally = 126/2;

    ballvx = random(-1,1);
    ballvy = 1;

    t = 0;
    score = 0;
    
}

// Add loop code
void loop()
{

	input();
	update();
	render();
    
	t += 1;
}

void input(){
    x = map(analogRead(joystickX), 0, 4096, 10, 128);
    y = map(analogRead(joystickY), 0, 4096, 128, 0);
    if (x < 1)      x = 10;
    if (x > 126)    x = 126;
    if (y < 1)      y = 2;
    if (y > 126)    y = 126;

}

void update(){

	ballx = ballx0 + ballvx; 
	bally = bally0 + ballvy; 

	if(ballx > 120){
	ballvx = -1;	
	}
	else if(ballx < 5){
	ballvx = 1;
	}
	if(bally > 120){
	ballvy = -1;}
	else if(bally < 5){
	ballvy = 1;
	}

	if(abs(ballx-x) < 10 && abs(bally-100) < 5){
	if(count == true){
	score++; 
	  count = false; 
	}
	
	ballvy = random(-1,1); 
	ballvx = random(-1,1);	
	
	}
	
  if(abs(ballx-x) > 10 || abs(bally-100) > 5){
	count = true;}

  if(bally > 110){ 
	gameOver();}

}


void render(){
	draw.setPenSolid(true);

	draw.dRectangle(ballx0-1, bally0-1, 3, 3, 0b0000000000000000);
        draw.dRectangle(ballx-1, bally-1, 3, 3, 0b1111111111111111);
        ballx0 = ballx;
        bally0 = bally;

	draw.line(x00-1, 100, x00-10, 100, 0b0000000000000000);
        draw.line(x-1, 100, x-10, 100, 0b1111111111111111);

	
	x00 = x; 		
	draw.gText(0, draw.screenSizeY()-draw.fontSizeY(), "Score= " + String(score), 0b1111111111111111);

}

void gameOver(){

	draw.gText(0, (draw.screenSizeY() - draw.fontSizeY())/2, "GAME OVER!", 0b1111111111111111);
	delay(1000);
	setup();
}

