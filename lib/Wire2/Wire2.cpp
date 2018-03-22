#define F_CPU 16000000UL

#include <avr/io.h>
#include "Wire2.h"
#include <util/delay.h>

#define DLY _delay_us(100)


void TWI2::begin(){
	DDRC |= (1<<DDC2) | (1<<DDC3);
}


// Initiate start condition
void TWI2::beginTransmission(unsigned char address)
{
	SDA1;
	DLY;
	SCL1;
	DLY;
	SDA0;

	write (address<<1);
}

// Initiate stop condition
void TWI2::endTransmission()
{
	SDA0;
	DLY;
	SDA0;
	DLY;
	SDA0;
	DLY;
	SDA0;
	DLY;
	SCL1;
	DLY;
	SCL1;
	DLY;
	SDA1;
	DLY;
}

void TWI2::write(unsigned char d)
{
	unsigned char i;

	SCL0;
	DLY;
    for (i = 1; i <= 8; i++)
	{
		if (d >> 7) SDA1;
			else SDA0;
			DLY;
		SCL1;
		DLY;
		d = d << 1;        /* increase SCL high time */
		SCL0;
		DLY;
	}
	SDA1;        /* Release the SDA line */
	DLY;
	SCL0;
	DLY;
	SCL1;
	DLY;
	SCL0;
	DLY;
}

TWI2 Wire2;
