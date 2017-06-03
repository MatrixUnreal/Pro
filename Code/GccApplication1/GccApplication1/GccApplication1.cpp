/*
 * GccApplication1.cpp
 *
 * Created: 02.06.2017 21:47:03
 *  Author: Rustam
 */ 


#include <avr/io.h>
#include "Init.h"

//// Timer 0 overflow interrupt service routine
//interrupt [TIM0_OVF] void timer0_ovf_isr(void)
//{
//// Place your code here
//
//}
//
//// Timer1 overflow interrupt service routine
//interrupt [TIM1_OVF] void timer1_ovf_isr(void)
//{
//// Place your code here
//
//}


int main(void)
{
	
	init();
	
	
    while(1)
    {
        //TODO:: Please write your application code 
		if(PIND&(1<<PD2))
		{
			PORTB=(0<<PD0)+(0<<PD4);
		}
		else
		{
			PORTB=(1<<PD0)+(1<<PD4);
		}
		
		
		
    }
}