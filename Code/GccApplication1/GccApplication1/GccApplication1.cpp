
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <limits.h>



#include "Init.h"
#include "PortIO.h"
#include "ClassCode.h"


void USART_Transmit( unsigned char data );
void USART_Init( unsigned int ubrr);

MotorDC Motor;
MotorStep MotorS;
#define TIME_PRESS 500
#define STEP_COUNT_FOR_45 5




bool fRunMotorSForward,fRunMotorSBackward;
int StepCount=0;

ISR(USART_RX_vect)
{
	
	
	int b;
	b = UDR;
	
	if (b=='0')
	{
		Motor.Stop();
		MotorS.Stop();
	}
	else
	if (b=='1')
	{
		Motor.Run_Forward();
	}
	else
	if (b=='2')
	{
		Motor.Run_Backward();
	}
	
	UDR=0;
}


void USART_Transmit( unsigned char data ) 
{
	while ( !(UCSRA & (1<<UDRE)) ); 
	UDR = data; 
}

void StopNow()
{
	StepCount=0;
	MotorS.Stop();
	fRunMotorSForward=false;
	fRunMotorSBackward=false;
}


ISR(TIMER0_OVF_vect)//2mS
{
	TCNT0=0x80;
	
	static int TimePress=0;
	static bool fPress1=0,fPress2=0;
	if(!IPORT2 && !Motor.state && !MotorS.state)// нажата B1 при выключеных движках
	{
		fPress1=true;
		if(TimePress<INT_MAX-1)
		TimePress++;		
	}		
	else if (IPORT2 && !Motor.state && !MotorS.state)//отпустили B1
	{
		if(fPress1)
		{
			if(TimePress>TIME_PRESS)
			{
				Motor.Run(false);
			}		
			else
			{	
				fRunMotorSForward=true;			
			}		
			
		}
		fPress1=false;
		if(!fPress2)
		TimePress=0;
	}
	if(!IPORT3 && !Motor.state && !MotorS.state)// нажата B2 при выключеных движках
	{
		fPress2=true;
		if(TimePress<INT_MAX-1)
		TimePress++;
	}
	else if (IPORT3 && !Motor.state && !MotorS.state)//отпустили B2
	{
			if(fPress2)
			{
				if(TimePress>TIME_PRESS)
				{
					Motor.Run(true);
				}
				else
				{
					fRunMotorSBackward=true;
				}
				
			}
			fPress2=false;
			if(!fPress1)
			TimePress=0;
	}	
	
	if(!IPORT5 && Motor.state && !Motor.dirrect) //концевик
	{
		Motor.Stop();
		Motor.state=0;
		Motor.location=1;//TODO
	}
	if(!IPORT6 && Motor.state && Motor.dirrect)//концевик
	{
		Motor.Stop();
		Motor.state=0;
		Motor.location=2;//TODO
	}
	if(!IPORT4 )// во время работы нажата кнопка "стоп"
	{
		Motor.Stop();
		MotorS.Stop();
		fPress1=false;
		fPress2=false;
		fRunMotorSForward=false;
		fRunMotorSBackward=false;
		TimePress=0;
		StepCount=0;
	}
	

}

ISR(TIMER1_OVF_vect)//1 Sec
{
	
	if(fRunMotorSForward)
	{
		if(MotorS.position<3 && StepCount<STEP_COUNT_FOR_45)
		{
			StepCount++;
			++MotorS;
		}
		else 
		{
			+MotorS;
			StopNow();
		}
	}		
	if(fRunMotorSBackward)
	{
		if(MotorS.position && StepCount<STEP_COUNT_FOR_45)
		{
				StepCount++;
				--MotorS;
		}		
		else
		{
			-MotorS;
			StopNow();
		}
	}
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