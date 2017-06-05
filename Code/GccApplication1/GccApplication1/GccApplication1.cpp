
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000L
int baudrate = 9600; // �������� �������� ������ � ���/�

#include "Init.h"
#include "PortIO.h"

#define nop() {asm("nop");}

void USART_Transmit( unsigned char data );
void USART_Init( unsigned int ubrr);

ISR(USART_RX_vect)
{
	PORTB=~PORTB;
	int b;
	b = UDR;
	// ��������� ��������� ��������� �����
	if (b=='1')//���� ������� "1"
	{
		USART_Transmit('R');//���������� ����� "R"
		USART_Transmit(0x0d);//������� � ������ ������
		USART_Transmit(0x0a);//������� �� ����� ������
	}
	else//���� ���
	if (b=='2')//���� ������� "2"
	{
		USART_Transmit('L');//���������� ����� "L"
		USART_Transmit(0x0d);//������� � ������ ������
		USART_Transmit(0x0a);//������� �� ����� ������
	}
}




void USART_init()  // ������� ������������� USART 19200
{

		UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
		UCSRB=(1<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
		UCSRC=(0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
		UBRRH=0x00;
		UBRRL=0x19;
	
		
}

void USART_Transmit( unsigned char data ) //������� �������� ������
{
	while ( !(UCSRA & (1<<UDRE)) ); //�������� ����������� ������ ������
	UDR = data; //������ �������� ������
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
			
			USART_Transmit('O');//�������� ��� ���������
			USART_Transmit('k');//��������� "Ok!", ��� ���������������
			USART_Transmit('!');//� ��������� ������ ���������
			
			USART_Transmit(0x0d);//������� � ������ ������
			USART_Transmit(0x0a);//������� �� ����� ������
	
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