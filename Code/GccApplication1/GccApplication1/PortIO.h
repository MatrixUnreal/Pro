/*
 * PortIO.h
 *
 * Created: 04.06.2017 9:49:17
 *  Author: Rustam
 */ 



#ifndef PORTIO_H_
#define PORTIO_H_

#define OPORT1 PB0
#define OPORT2 PB1
#define OPORT3 PB2
#define OPORT4 PB3
#define OPORTE PB4

#define O_ENABLE1 PB5 
#define O_ROT1 PB6
#define O_ROT2 PB7

#define OPORTE_ON PORTB|=(1<<OPORTE)
#define OPORTE_OFF PORTB&=~(1<<OPORTE)
#define OPORT1_ON PORTB|=(1<<OPORT1)
#define OPORT1_OFF PORTB&=~(1<<OPORT1)
#define OPORT2_ON PORTB|=(1<<OPORT2)
#define OPORT2_OFF PORTB&=~(1<<OPORT2)
#define OPORT3_ON PORTB|=(1<<OPORT3)
#define OPORT3_OFF PORTB&=~(1<<OPORT3)
#define OPORT4_ON PORTB|=(1<<OPORT4)
#define OPORT4_OFF PORTB&=~(1<<OPORT4)

#define OPORT5_ON PORTB|=(1<<O_ENABLE1)
#define OPORT5_OFF PORTB&=~(1<<O_ENABLE1)

#define O_ROT1_ON PORTB|=(1<<O_ROT1)
#define O_ROT1_OFF PORTB&=~(1<<O_ROT1)
#define O_ROT2_ON PORTB|=(1<<O_ROT2)
#define O_ROT2_OFF PORTB&=~(1<<O_ROT2)


#define IPORT2 (PIND&(1<<PD2))
#define IPORT3 (PIND&(1<<PD3))
#define IPORT4 (PIND&(1<<PD4))
#define IPORT5 (PIND&(1<<PD5))
#define IPORT6 (PIND&(1<<PD6))

#endif /* PORTIO_H_ */