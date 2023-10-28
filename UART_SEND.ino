#include "MyUart.h"
#define _SENDER_


#define SEND_LEN  100
#define baudrate 14400
#define stopBit 1
#define parity P_NONE
#define dataSize 8
char arr[SEND_LEN] = {' ', 'a', 'z', 'z', 'z', 'z', 'z', 'z', 'b', ' '};
char* chuoi = "Hello World 2022";
char* vanBan = "This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version his library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.\n";
//char x = 'a';//97
MyUart sender;

void setup() {
  sender.begin(baudrate,stopBit,parity,dataSize);
  //Serial.begin(baudrate);
  //sender.begin(baudrate);
  delay(100);

 // for(int i = 0; i < SEND_LEN; i++)
 // {
  //    arr[i] = '0' + i;
   //   while(arr[i] > 'Z') arr[i] -= 42;
 // }
}

void loop() {
#ifdef _SENDER_
 // sender.writeByte(x);
 // sender.writeBytes(arr, SEND_LEN);
 // sender.writeString("   NGuyen do Lan\n");
// sender.writeString(chuoi);
  sender.writeString(vanBan);
 // if(x == 'z') x = 'a';
 // x++;
  delay(1000);
// Serial.println(x);
#else
  char a = sender.readByte();
  Serial.println(a);

  int len = sender.readLine(arr);
  Serial.println(arr);
#endif
}
