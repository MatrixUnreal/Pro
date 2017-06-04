#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Init.h"
#include "PortIO.h"

#define nop() {asm("nop");}




//// Timer 0 overflow interrupt service routine
//interrupt [TIM0_OVF] void timer0_ovf_isr(void)
//{
// Place your code here

//}
////// Timer1 overflow interrupt service routine
//interrupt [TIM1_OVF] void timer1_ovf_isr(void)
//{
//// Place your code here
//
//}

//ISR(TIMER0_COMPA_vect)
//{
	//ELED_ON;
	//LED1_ON;
//}	




/*
ISR(USART_RXC_vect)
{
	switch(UDR)
	{
		case '1': 
		ELED_ON;
		LED1_ON;
		break;
		case '0':
		 ELED_OFF;
		 LED1_OFF;
		 break;
		default: break;
	}
}*/

ISR(INT0_vect)
{
	ELED_ON;
	LED1_ON;
}


int main(void)
{
	
	init();
	
	
	GIMSK=0x40;
	MCUCR=0x02;
	//TCCR0=0x05;
	TCNT0=0x00;
	sei();
    while(1)
    {
		if(!ILED2)
		{
			ELED_ON;
			LED1_ON;			
		}
		else
		{
			ELED_OFF;
			LED1_OFF;
		}

    }
}