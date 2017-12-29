// last update 24/06/17

#ifndef _TFT9341_H_
#define _TFT9341_H_

//#define CAV 1

#include <avr/pgmspace.h>
#include "registers.h"

#define SWAP(a, b) { int16_t t = a; a = b; b = t; }
#define ABS(x) ((x)>0?(x):-(x))

#define _SPI_DDR	DDRB
#define _SPI_PORT	PORTB

#define _DC		PDB1
#define _RES	PDB0
#ifdef CAV
#define T_SS	POD5
#else
#define T_SS	POD7
#endif
#define T_IRQ	PID2


#define O_SS	POB2
#define O_DC	POB1
#define O_RES	POB0

#ifndef DEC
#define DEC	10
#define HEX	16
#define OCT	8
#define BIN	2
#endif

#define WIDTH			320
#define HEIGHT			240

enum class Color: uint16_t {
	BLACK = 0x0000,
	GRAY = 0x8410,
	BLUE = 0x001F,
	RED = 0xF800,
	GREEN = 0x07E0,
	CYAN = 0x07FF,
	MAGENTA = 0xF81F,
	PURPLE = 0x7194,
	ORANGE = 0xFE00,
	YELLOW = 0xFFE0,
	WHITE = 0xFFFF,
};
// #define	BLACK		0x0000
// #define	GRAY			0x8410
// #define	BLUE			0x001F
// #define	RED				0xF800
// #define	GREEN		0x07E0
// #define	CYAN			0x07FF
// #define	MAGENTA 0xF81F
// #define	PURPLE		0x7194
// #define	ORANGE	0xFE00
// #define	YELLOW	0xFFE0
// #define	WHITE		0xFFFF

#define up2down		0x08
#define down2up		0xc8
#define right2left		0x68
#define left2right		0xa8

#define MADCTL  0x36

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

#define INVOFF  0x20
#define INVON   0x21

#define scrollup		2
#define scrolldown	1

#define CASET   0x2A
#define PASET   0x2B
#define RAMWR   0x2C

class tft9341 {
	uint16_t  color, background;
	int16_t x, y, width, height;
	uint8_t rotation, fontSize;
	int16_t numbera ,numberb ,number1, number2;

	void writeData(uint8_t data8);
	void writeCommand(uint8_t cmd);
	void writeData2bytes(uint8_t dataHigh,uint8_t dataLow);
	void putChar(char c);

	public:
	tft9341();
	inline void gotoxy (uint16_t x,uint16_t y) { this->x = x; this->y = y;}
	inline int16_t getX() {return (this->x);}
	inline int16_t getY() {return (this->y);}
	inline uint8_t getFont () { return (this->fontSize); }
	inline void setFont (uint8_t fontSize) { this->fontSize = fontSize; }
	inline uint16_t getColor () { return (this->color); }
	inline void setColor (uint16_t color) { this->color = color;}
	inline void setColor (Color color) { this->color = static_cast<uint16_t>(color);}
	inline void setColor (Color color, Color background) {
		this->color=static_cast<uint16_t>(color); this->background=static_cast<uint16_t>(background);
	}
	inline uint16_t getBackground () {	return (this->background); }
	inline void setBackground (Color background) { this->background = static_cast<uint16_t>(background); }
	inline uint16_t getHeight() { return (this->height); }
	inline uint16_t getWidth() { return (this->width); }
	inline uint8_t	 getRotation() { return (this->rotation); }
	void setRotation(uint8_t m);
	inline void switchColors () { SWAP (this->color, this->background); }
	void sector(int16_t x0,int16_t x1,int16_t y0,int16_t y1);

	void begin();
	void begin(uint8_t r){begin(); setRotation (r);}
	void clrscr();
	void clrscr(Color background) {setBackground (background); clrscr();};

	void write (char c);
	void print (int16_t num) {print(num,DEC);};
	void print (uint16_t num);
	void print (int8_t num) {print(num,DEC);};
	void print (uint8_t num) {print(num,DEC);};
	void print (int16_t num, uint8_t radix);
	void print (uint16_t num, uint8_t radix);
	void print (uint8_t num, uint8_t radix);
	void print (int8_t num, uint8_t radix);
	void print (char const* str);
	void print (double fnum, uint8_t s);
	void print (double fnum) {print (fnum,2);};

	void writeln (char c);
	void println ();
	void println (int16_t num) {println(num,DEC);};
	void println (uint16_t num);
	void println (int8_t num) {println(num,DEC);};
	void println (uint8_t num) {println(num,DEC);};
	void println (int16_t num, uint8_t radix);
	void println (uint16_t num, uint8_t radix);
	void println (uint8_t num, uint8_t radix);
	void println (int8_t num, uint8_t radix);
	void println (char *str);
	void println (double fnum, uint8_t s);
	void println (double fnum) {print (fnum,2);};

	void drawPixel (int16_t x,int16_t y);
	void drawPixel (int16_t x,int16_t y, Color color) { setColor (color); drawPixel (x,y);};
	void drawHLine (int16_t x,int16_t y, int16_t w);
	void drawHLine (int16_t x,int16_t y, int16_t w, Color color) { setColor (color); drawHLine (x,y,w);};
	void drawVLine (int16_t x,int16_t y, int16_t h);
	void drawVLine (int16_t x,int16_t y, int16_t h, Color color) { setColor (color); drawVLine (x,y,h);};
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, Color color) { setColor (color); drawLine(x0,y0,x1,y1);};
	void drawLinePolar (int16_t x0, int16_t y0, int16_t r, int16_t angle);
	void drawLinePolar (int16_t x0, int16_t y0, int16_t r, int16_t angle, Color color) { setColor (color); drawLinePolar (x0,y0,r,angle);};

	void drawRect (int16_t x, int16_t y, int16_t w, int16_t h);
	void drawRect (int16_t x, int16_t y, int16_t w, int16_t h, Color color){ setColor (color); drawRect (x,y,w,h);};
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color){setColor(color); drawTriangle(x0,y0,x1,y1,x2,y2);};
	void drawCircle(int16_t x0, int16_t y0, int16_t r);
	void drawCircle(int16_t x0, int16_t y0, int16_t r, Color color){setColor(color); drawCircle(x0,y0,r);};
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, int8_t cornername);
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, int8_t cornername, Color color){setColor(color); drawCircleHelper(x0,y0,r,cornername);};
	void drawRoundRect(int16_t x, int16_t y, int16_t w,int16_t h, int16_t r) ;
	void drawRoundRect(int16_t x, int16_t y, int16_t w,int16_t h, int16_t r, Color color){setColor(color); drawRoundRect(x,y,w,h,r) ;};

	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Color color){setColor(color); fillRect(x,y,w,h);};
	void fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
	void fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color){setColor(color); fillTriangle (x0,y0,x1,y1,x2,y2);};
	void fillCircle(int16_t x0, int16_t y0, int16_t r);
	void fillCircle(int16_t x0, int16_t y0, int16_t r, Color color){setColor(color); fillCircle(x0,y0,r);};
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r,uint8_t cornername, int16_t delta) ;
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r,uint8_t cornername, int16_t delta, Color color){setColor(color); fillCircleHelper(x0,y0,r,cornername,delta) ;};
	void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r);
	void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, Color color){setColor(color); fillRoundRect(x,y,w,h,r);};

	void invertDisplay(uint8_t i);

	uint16_t color565(uint32_t color);

	uint16_t rgbColor(uint8_t r, uint8_t g, uint8_t b);
	void putRgbColorPixel(uint8_t r, uint8_t g, uint8_t b);

	void startScrollingRolling();
	void endScrollingRolling (uint8_t Direction);
};

class touch{
	int16_t x, y;
	int16_t TypeTouch;
	uint16_t getX();
	uint16_t getY();
	public:
	touch();
	void InitTypeTouch(int type);
	void readxy();
	uint16_t readx() {return (this->x);};
	uint16_t ready() {return (this->y);};
};


extern tft9341 lcd;
extern touch lcdtouch;

#endif
