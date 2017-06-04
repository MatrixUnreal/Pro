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
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 115,200 kHz
	// Mode: CTC top=OCR0
	// OC0 output: Disconnected
	// Timer Period: 1,9965 ms
	TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (1<<WGM01) | (0<<CS02) | (1<<CS01) | (1<<CS00);
	TCNT0=0x00;
	OCR0=0xE5;

	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 28,800 kHz
	// Mode: CTC top=OCR1A
	// OC1A output: Clear on compare match
	// OC1B output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer Period: 1 s
	// Output Pulse(s):
	// OC1A Period: 1 s
	// Timer1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: On
	// Compare B Match Interrupt: Off
	TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
	TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x70;
	OCR1AL=0x7F;
	OCR1BH=0x00;
	OCR1BL=0x00;

	// Timer/Counter 2 initialization
	// Clock source: System Clock
	// Clock value: 7,200 kHz
	// Mode: CTC top=OCR2A
	// OC2 output: Clear on compare match
	// Timer Period: 10 ms
	// Output Pulse(s):
	// OC2 Period: 10 ms
	ASSR=0<<AS2;
	TCCR2=(0<<PWM2) | (1<<COM21) | (0<<COM20) | (1<<CTC2) | (1<<CS22) | (1<<CS21) | (1<<CS20);
	TCNT2=0xB8;
	OCR2=0x47;

	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=(0<<OCIE2) | (1<<TOIE2) | (0<<TICIE1) | (1<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);
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