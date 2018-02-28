// sda pc2
// scl pc3



#define SDA1 PORTC |= (1<<PORTC2)
#define SDA0 PORTC &= ~(1<<PORTC2)

#define SCL1 PORTC |= (1<<PORTC3)
#define SCL0 PORTC &= ~(1<<PORTC3)


class TWI2{
public:
	void begin();
	void beginTransmission(unsigned char address);
	void endTransmission();
	void write(unsigned char d);
};

extern TWI2 Wire2;
