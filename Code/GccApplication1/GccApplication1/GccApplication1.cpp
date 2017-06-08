
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Init.h"
#include "PortIO.h"
#include "ClassCode.h"

void USART_Transmit( unsigned char data );
void USART_Init( unsigned int ubrr);

ISR(USART_RX_vect)
{
	
	int b;
	b = UDR;
	
	if (b=='1')
	{
		USART_Transmit('R');
		USART_Transmit(0x0d);
		USART_Transmit(0x0a);
		Motor.Run_Forward();
	}
	else
	if (b=='2')
	{
		USART_Transmit('L');
		USART_Transmit(0x0d);
		USART_Transmit(0x0a);
		Motor.Run_Backward();
	}
	else
	if (b=='3')
	{
		USART_Transmit('S');
		USART_Transmit(0x0d);
		USART_Transmit(0x0a);
		Motor.Stop();
	}
	UDR=0;
}






void USART_Transmit( unsigned char data ) 
{
	while ( !(UCSRA & (1<<UDRE)) ); 
	UDR = data; 
}




ISR(TIMER0_OVF_vect)//2mS
{
	TCNT0=0x80;
	if(!IPORT5 && Motor.state && !Motor.dirrect)
	{
		Motor.Stop();
		Motor.state=0;
		Motor.location=1;//TODO
	}
	if(!IPORT6 && Motor.state && Motor.dirrect)
	{
		Motor.Stop();
		Motor.state=0;
		Motor.location=2;//TODO
	}
}

ISR(TIMER1_OVF_vect)//1 Sec
{
	//PORTB=~PORTB;
}




int main(void)
{
	
	init();
	timer_init();
	USART_init();
	
	sei();
    while(1)
    {
		
	

    }
}