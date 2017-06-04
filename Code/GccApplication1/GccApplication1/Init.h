/*
 * Init.h
 *
 * Created: 02.06.2017 21:49:02
 *  Author: Rustam
 */ 


#ifndef INIT_H_
#define INIT_H_
void timer_init()
{

	TCCR0B=0x03;//1-64uS,2-510uS,3-4.1mS,4-16.3mS,5-65.5mS
    TCCR1B=0x03;
	
	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK= (1<<TOIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<ICIE1) | (0<<OCIE0B)| (1<<TOIE0)  | (0<<OCIE0A);

}


void init()
{	

	
	// Declare your local variables here

	// Crystal Oscillator division factor: 1
	#pragma optsize-
	CLKPR=(1<<CLKPCE);
	CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
	#ifdef _OPTIMIZE_SIZE_
	#pragma optsize+
	#endif

	// Input/Output Ports initialization
	// Port A initialization
	// Function: Bit2=In Bit1=Out Bit0=Out
	DDRA=0b011;
	// State: Bit2=T Bit1=1 Bit0=1
	PORTA=(0<<PORTA2) | (1<<PORTA1) | (1<<PORTA0);

	// Port B initialization
	// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
	DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
	// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
	PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

	// Port D initialization
	// Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRD=(0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
	// State: Bit6=P Bit5=P Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P
	PORTD=(1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	// Interrupt on any change on pins PCINT0-7: Off
	//GIMSK=(0<<INT1) | (0<<INT0) | (0<<PCIE);
	MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);

	#define XTAL 8000000L
	#define baudrate 9600L
	#define bauddivider (XTAL/(16*baudrate)-1)
	#define HI(x) ((x)>>8)
	#define LO(x) ((x)& 0xFF)
	
	UBRRL = LO(bauddivider);
	UBRRH = HI(bauddivider);
	UCSRA = 0;
	UCSRB = 1<<RXEN|1<<TXEN|1<<RXCIE|0<<TXCIE;
	UCSRC = 1<<UCSZ0|1<<UCSZ1;
	
/*
	// USART initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: On
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud Rate: 9600
	UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
	UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
	UCSRC=(0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
	UBRRH=0x00;
	UBRRL=0x19;
	
*/	

	// Analog Comparator initialization
	// Analog Comparator: Off
	// The Analog Comparator's positive input is
	// connected to the AIN0 pin
	// The Analog Comparator's negative input is
	// connected to the AIN1 pin
	//ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
	// Digital input buffer on AIN0: On
	// Digital input buffer on AIN1: On
//	DIDR=(0<<AIN0D) | (0<<AIN1D);
}




#endif /* INIT_H_ */