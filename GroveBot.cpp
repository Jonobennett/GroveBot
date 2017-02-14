/*
   GroveBot.cpp - Library for controlling Initio robots
   Created by Jonathan Bennett 2016.
   Released into the public domain.
 */

#include "Arduino.h"
#include "GroveBot.h"


GroveBot::GroveBot() {

  _led = 13; // LED
  
  // initialize the digital pins we will use as an output.
  pinMode(_L1, OUTPUT);     
  pinMode(_L2, OUTPUT);     
  pinMode(_L3, OUTPUT);     
  pinMode(_L4, OUTPUT);

  // initialise input pins and interrupts for speed sensors
  pinMode(_DL0, INPUT);
  pinMode(_DL1, INPUT);
  pinMode(_DR0, INPUT);
  pinMode(_DR1, INPUT);

  //initialise LED
  pinMode(_led, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(_DL0), _intLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(_DR0), _intRight, RISING);

   _dir = "None";

  Serial.begin(115200);
   
}

// robMove routine switches the correct inputs to the L298N for the direction selected.
void GroveBot::_robMove(int l1, int l2, int r1, int r2)
{
  analogWrite(_L1, l1);
  digitalWrite(_L2, l2);
  analogWrite(_L3, r1);
  digitalWrite(_L4, r2);  
}

void GroveBot::_halt() {
	Serial.println("Stopping");
	_robMove(0, LOW, 0, LOW);
}

float GroveBot::forward(float metres) {
  _lpos = 0;
  _rpos = 0;
	Serial.println("Moving forward");
  _robMove(255, LOW, 255, LOW);

}

float GroveBot::backward(float metres) {
  _lpos = 0;
  _rpos = 0;
	Serial.println("Moving backward");
  _robMove(0, HIGH, 0, HIGH);
}

float GroveBot::spinLeft(float degrees) {
  _lpos = 0;
  _rpos = 0;
	Serial.println("Turning left");
  _robMove(0, HIGH, 255, LOW);
}

float GroveBot::spinRight(float degrees) {
  _lpos = 0;
  _rpos = 0;
	Serial.println("Turning right");
  _robMove(255, LOW, 0, HIGH);
}

void GroveBot::flash(int flashes) {
  for(int counter=0 ; counter < flashes ; counter++) {
    digitalWrite(_led,HIGH);
    delay(250);
    digitalWrite(_led,LOW);
    delay(250);
   }
}

void _intLeft() {  // This interrupt routine runs if the left side encoder is triggered (DL0) 
  _lStat0 = digitalRead(_DL0);
  _lStat1 = digitalRead(_DL1);
  if(_lStat1 > 0) // use DL1 to determine which direction we're moving. HIGH = Forwards
    _lpos++;
  else
    _lpos--;
  _dir = "Left";
}

void _intRight() {    // This interrupt routine runs if the right side encoder is triggered (DR0) 
  _rStat0 = digitalRead(_DR0);
  _rStat1 = digitalRead(_DR1);
  if(_rStat1 > 0) // use DR1 to determine which direction we're moving. HIGH = Backwards
    _rpos--;
  else
    _rpos++;
  _dir = "Right";
}
