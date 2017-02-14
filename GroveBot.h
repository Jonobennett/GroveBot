/*
   GroveBot.h - Library for driving the Guildford Grove robots.
 */

#ifndef GroveBot_h
#define GroveBot_h

#include "Arduino.h"

class GroveBot {
	public:
		GroveBot();
		float forward(float metres);
		float backward(float metres);
		float spinLeft(float degrees);
		float spinRight(float degrees);
    void flash(int flashes);
	private:
		int _pulsesPerMetre;
		void _robMove(int l1, int l2, int r1, int r2);
		void _halt();
    void _intLeft();
    void _intRight();
    int _L1, _L2, _L3, _L4; // Output Pins connected to Motor driver L298N H-Bridge module
    int _DL0, _DL1, _DR0, _DR1;    // Pins for Right and Left encoders. DL0 and DR0 must be Interrupt pins
    int _lStat0, _lStat1, _rStat0, _rStat1;        // variables to hold status of each speed sensor input
    int _lpos, _rpos;                    // variables keeping count of the pulses on each side
    String _dir;
    int _led; //Pin the LED is connected to



}


#endif
