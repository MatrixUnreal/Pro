/*
 * PortIO.h
 *
 * Created: 04.06.2017 9:49:17
 *  Author: Rustam
 */ 



#ifndef PORTIO_H_
#define PORTIO_H_

#define LED1 PB0
#define LED2 PB1
#define LED3 PB2
#define LED4 PB3
#define ELED PB4

#define ELED_ON PORTB|=(1<<ELED)
#define ELED_OFF PORTB&=~(1<<ELED)
#define LED1_ON PORTB|=(1<<LED1)
#define LED1_OFF PORTB&=~(1<<LED1)
#define LED2_ON PORTB|=(1<<LED2)
#define LED2_OFF PORTB&=~(1<<LED2)
#define LED3_ON PORTB|=(1<<LED3)
#define LED3_OFF PORTB&=~(1<<LED3)
#define LED4_ON PORTB|=(1<<LED4)
#define LED4_OFF PORTB&=~(1<<LED4)

#define ILED0 (PIND&(1<<PD0))
#define ILED1 (PIND&(1<<PD1))
#define ILED2 (PIND&(1<<PD2))
#define ILED3 (PIND&(1<<PD3))
#define ILED4 (PIND&(1<<PD4))
#define ILED5 (PIND&(1<<PD5))
#define ILED6 (PIND&(1<<PD6))
#define ILED7 (PIND&(1<<PD7))
#define ILED8 (PIND&(1<<PD8))

#endif /* PORTIO_H_ */