
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
	// ��������� ��������� ��������� �����
	if (b=='1')//���� ������� "1"
	{
		USART_Transmit('R');//���������� ����� "R"
		USART_Transmit(0x0d);//������� � ������ ������
		USART_Transmit(0x0a);//������� �� ����� ������
		Motor.Run_Forward();
	}
	else//���� ���
	if (b=='2')//���� ������� "2"
	{
		USART_Transmit('L');//���������� ����� "L"
		USART_Transmit(0x0d);//������� � ������ ������
		USART_Transmit(0x0a);//������� �� ����� ������
		Motor.Run_Backward();
	}
	else//���� ���
	if (b=='3')//���� ������� "2"
	{
		USART_Transmit('S');//���������� ����� "L"
		USART_Transmit(0x0d);//������� � ������ ������
		USART_Transmit(0x0a);//������� �� ����� ������
		Motor.Stop();
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