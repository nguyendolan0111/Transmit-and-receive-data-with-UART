#include "MyUart.h"

MyUart::MyUart()
{
  mCycle = 0;
  mBaudrate = 9600;
  mStopbit = 1;
  mParity = P_NONE;
  mDataSize = 8; 
}

void MyUart::begin(int baudrate)
{
  mBaudrate = baudrate;
  mStopbit = 1;
  mParity = P_NONE;
  mDataSize = 8;

  updateCycle();
}

void MyUart::begin(int baudrate, int stopBit, int parity, int dataSize)
{
  mCycle = 0;
  mBaudrate = baudrate;
  mStopbit = stopBit;
  mParity = parity;
  mDataSize = dataSize;
  updateCycle();
}

void MyUart::updateCycle()
{
  mCycle = 1.0/mBaudrate * 1000 * 1000; // s->us
  setupTX(HIGH);
  TX_OUTPUT;
}

void MyUart::writeByte(char a)
{
  int i, b, par = 0;

  /* Send start bit */
  setupTX(LOW);
  delayMicroseconds(mCycle);

  /* Send one byte */
  for(i=0; i < mDataSize; i++)
  {
    b = a & 0x01;//0000.0001
    par += b;
    setupTX(b);
    a >>= 1;
    delayMicroseconds(mCycle);
  }

  /* Setup parity */
  if(mParity == P_EVEN)
  {
    if(par%2 == 0)
    {
      setupTX(LOW);
    }
    else
    {
      setupTX(HIGH);
    }
    delayMicroseconds(mCycle);
  }
  else if(mParity == P_ODD)
  {
    if(par%2 == 0)
    {
      setupTX(HIGH);
    }
    else
    {
      setupTX(LOW);
    }
    delayMicroseconds(mCycle); 
  }
  else
  {
     //Parity NONE
  }
   
  /* Send stop bit */
  setupTX(HIGH); 
  if(mStopbit == S_TWO)
  {
    delayMicroseconds(mCycle*2); 
  }
  else
  {
    delayMicroseconds(mCycle);
  }
}

void MyUart::writeString(char *str)
{
    for(int i = 0; i < strlen(str); i++)
    {
      writeByte(str[i]);
    }
}

void MyUart::writeLine(char *str)
{
    writeString(str);
    writeByte("\n");
}

void MyUart::writeBytes(char* str, int len)
{
    if(str == NULL) return;
    for(int i = 0; i < len; i++)
    {
      writeByte(str[i]);
    }
}

char MyUart::readByte()
{
  char byteIn = 0;
  uint8_t i, res;
  
  /* Waiting for START bit */
  while(readRX() == HIGH){
    //delayMicroseconds(mCycle/5);
  }
  
  /* Read one byte */
  delayMicroseconds(mCycle + mCycle/2);
  for(i=0;i<8;i++)
  {
    res = readRX();
    res = res << i;
    byteIn = byteIn | res;
    delayMicroseconds(mCycle);
  }

  /* Read parity bit */
  
  /* Read Stop bit */
  if(mStopbit == S_TWO)
  {
    res = readRX();
    delayMicroseconds(mCycle);
    res += readRX();
    //delayMicroseconds(mCycle);
  }
  else
  {
    res = readRX();
    //delayMicroseconds(mCycle);
  }
  
  if(res == 0)
    return 0;
  return byteIn;
}
int MyUart::readLine(char *output)
{
  int len = 0;
  char c = '\0';
  while(c != "\n"){
     c = readByte();
     output[len] = c;
     len++;
  }
  output[len++] = '\n';
  return len;
}
