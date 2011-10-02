/*
 * BlinkingViaHardwareCTC.cpp
 *
 * Created: 10/2/2011 9:13:10 AM
 *  Author: J Adam Crain
 */ 

#include <avr/io.h> 
#include <avr/interrupt.h> 

int main (void) 
{ 
	DDRB |= (1 << 5); // Set LED as output (PIN 11 on the Mega) 

	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode

	TCCR1A |= (1 << COM1A0); // Enable timer 1 Compare Output channel C in toggle mode 

	OCR1A = 15624; // Set CTC compare value for channel C to 1Hz at 16MHz AVR clock, with a prescaler of 1024
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Start timer at Fcpu/1024

	for (;;) 
	{ 

	} 
}