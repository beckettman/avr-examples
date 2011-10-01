/*
Uses the timer and pre-scaler to blink an LED at 1Hz
*/

#include <avr/io.h>

#define F_CPU 16000000UL
#define BIT(x)	(1<<x)
#define SET(reg, bits) reg |= bits
#define CLEAR(reg, bits) reg &= ~bits
#define TOGGLE(reg, bits) reg ^= bits

/*
16000000 (op/sec) / 1024 (cnts/op) = 15635 cnts/sec

There we use the 1024 pre-scaler to and 15635 counts to get to 1Hz.

*/
int main (void) 
{ 
   SET(DDRB, BIT(7));		// Set PORTB, pin 7 as output
   SET(TCCR1B, BIT(CS10)|BIT(CS12));	// Set clock source, x1 

   for (;;) 
   { 
      // Check timer value in if statement, true when count matches 1/20 of a second 
      if (TCNT1 >= 15635) 
      { 
         TOGGLE(PORTB, BIT(7)); // Toggle the LED 
         TCNT1 = 0;				// Zero the timer
      } 
   } 
}