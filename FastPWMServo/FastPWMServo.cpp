/*
 * FastPWMServo.cpp
 *
 * Created: 10/2/2011 10:21:36 AM
 *  Author: J Adam Crain
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
//#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << 5) | (1 << 7); // Set LED as output (PIN 11 on the Mega) 
	
	PORTB |= (1 << 7);
	
	// set phase + frequency correct PWM mode, WGM1[3:0] = 8 (0b1000)	
	TCCR1B |= (1 << WGM13);
	
	// Set on compare match when up counting, clear on compare match when down counting
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0); 
		
	TCCR1B |= (1 << CS11);	// Start timer at Fcpu/8
	
	uint16_t period = 30000;
	
	// this gives us 50hz signal (T=20ms) with pre-scaler set to 8
	ICR1 = period;
			
	uint16_t low = period - 1800;
	uint16_t high = period - 1200;
	
	// set compare register, this determines duty cycle (between 1.2ms and 1.8ms == [1200,1800]
	// therefore we have 1000 steps or between 9 and 10 bits of resolution for the servo!
	for(;;)	
	{		
		for(uint32_t pos = low; pos < high; ++pos)
		{
			OCR1A = pos;
			_delay_loop_2(20000);
		}
		
				
		for(uint32_t pos = high; pos > low; --pos)
		{			
			OCR1A = pos;
			_delay_loop_2(20000);
		}
		
	}
	
}