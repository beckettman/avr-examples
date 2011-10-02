/*
 * BlinkingViaTimerInterrupt.cpp
 *
 * Created: 10/1/2011 6:22:48 PM
 *  Author: J Adam Crain
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB |= (7 << 0); // Set LED as output 

	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode

	OCR1A   = 15624/2; // Set CTC compare value to 1Hz at 16MHz AVR clock, with a prescaler of 1024
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Start timer at Fcpu/1024
	
	TIMSK1 |= (1 << OCIE1A); // enable output compare interrupt for A compare
	sei();

	for (;;) {} 
} 

SIGNAL(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << 7); // Toggle the LED
}
