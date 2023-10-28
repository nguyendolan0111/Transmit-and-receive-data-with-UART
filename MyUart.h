#ifndef MYUART_H_
#define MYUART_H_
#include <Arduino.h>
#include <avr/io.h>

#define TX_PIN    PD6    //Chan 4
#define RX_PIN    PIND7  //chan 5

#define TX_OUTPUT (DDRD |= (1<<TX_PIN))
#define RX_INPUT (DDRD &= ~(1<<RX_PIN))
// x=LOW=FALSE=0     x=HIGH=1=TRUE
#define setupTX(x) (PORTD = ((x) ? (PORTD | 1<<TX_PIN) : (PORTD & (~(1<<TX_PIN)))))
#define readRX()    ((PIND & (1 << RX_PIN)) ? HIGH:LOW )


enum _StopBits
{
  S_ONE,
  S_TWO
};

enum _Parity
{
   P_NONE,
   P_ODD,
   P_EVEN
};

class MyUart
{
public:
  MyUart();

  void begin(int baudrate);
  void begin(int baudrate, int stopBit, int parity, int dataSize);
 
  void writeByte(char a);
  void writeString(char *str);
  void writeLine(char *str);
  void writeBytes(char* str, int len);

  char readByte();
  int readLine(char*);

private:
  unsigned int mCycle;
  int mBaudrate, mStopbit, mParity, mDataSize;

  void updateCycle();
};

#endif //MYUART_H_
