
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000L
int baudrate = 9600; // Скорость передачи данных в бит/с

#include "Init.h"
#include "PortIO.h"

#define nop() {asm("nop");}

void USART_Transmit( unsigned char data );
void USART_Init( unsigned int ubrr);

class MotorDC
{
	public:
	char state,   //0-free,1-busy
	     dirrect, //0-counter-clockwise,1-clockwise
		 location;//0-middle,1-bottom,2-top
	int time_from_start;
	public:
	void Stop()
	{
		O_ROT1_OFF;
		O_ROT2_OFF;
		state=0;
	}
	void Run_Forward()
	{
		state=1;
		dirrect=0;
		O_ROT2_OFF;
		O_ROT1_ON;		
	}
	void Run_Backward()
	{
		state=1;
		dirrect=1;
		O_ROT1_OFF;
		O_ROT2_ON;		
	}
	
} Motor;


ISR(USART_RX_vect)
{
	
	int b;
	b = UDR;
	// Выполняем обработку принятого байта
	if (b=='1')//Если приняли "1"
	{
		USART_Transmit('R');//Отправляем букву "R"
		USART_Transmit(0x0d);//переход в начало строки
		USART_Transmit(0x0a);//переход на новую строку
		Motor.Run_Forward();
	}
	else//Если нет
	if (b=='2')//Если приняли "2"
	{
		USART_Transmit('L');//Отправляем букву "L"
		USART_Transmit(0x0d);//переход в начало строки
		USART_Transmit(0x0a);//переход на новую строку
		Motor.Run_Backward();
	}
	else//Если нет
	if (b=='3')//Если приняли "2"
	{
		USART_Transmit('S');//Отправляем букву "L"
		USART_Transmit(0x0d);//переход в начало строки
		USART_Transmit(0x0a);//переход на новую строку
		Motor.Stop();
	}
}




void USART_init()  // функция инициализации USART 19200
{

		UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
		UCSRB=(1<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
		UCSRC=(0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
		UBRRH=0x00;
		UBRRL=0x19;
	
		
}

void USART_Transmit( unsigned char data ) //Функция отправки данных
{
	while ( !(UCSRA & (1<<UDRE)) ); //Ожидание опустошения буфера приема
	UDR = data; //Начало передачи данных
}




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
	
	
			
			USART_init();
			
			USART_Transmit('O');//Передаем при включении
			USART_Transmit('k');//сообщение "Ok!", что свидетельствует
			USART_Transmit('!');//о правильно работе программы
			
			USART_Transmit(0x0d);//переход в начало строки
			USART_Transmit(0x0a);//переход на новую строку
	
	sei();
    while(1)
    {
		if(IPORT5)
		{
			Motor.Stop();
			Motor.state=0;
			Motor.location=1;
		}
		
		
		/*if(!IPORT2)
		{
			OPORTE_ON;
			OPORT1_ON;			
		}
		else
		{
			OPORTE_OFF;
			OPORT1_OFF;
		}*/

    }
}