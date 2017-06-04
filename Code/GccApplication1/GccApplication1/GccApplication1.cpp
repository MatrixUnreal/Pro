#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Init.h"
#include "PortIO.h"

#define nop() {asm("nop");}


ISR(TIMER0_OVF_vect)//2mS
{
	/*TCNT0=0x80;
	PORTB=~PORTB;	*/
}

ISR(TIMER1_OVF_vect)//
{
	//PORTB=~PORTB;
}




int main(void)
{
	
	init();
	timer_init();
	
	sei();
    while(1)
    {
		/*if(!ILED2)
		{
			ELED_ON;
			LED1_ON;			
		}
		else
		{
			ELED_OFF;
			LED1_OFF;
		}*/

    }
}