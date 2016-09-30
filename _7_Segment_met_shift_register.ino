#include <Arduino.h>

/*
0 T/M 6 op D1 :
448
505
420
432
409
402
386

0 T/M 6 op D2

704
761
676
688
665
658
642

0 T/M 6 op D3

1216
1273
1188
1200
1177
1170
1154

0 T/M 6 op D4

2240
2297
2212
2224
2201
2194
2178

0 T/M 6 op D5

4288
4345
4260
4272
4249
4242
4226

0 T/M 6 op D6

8384
8441
8356
8368
8345
8338
8322

0 T/M 6 op D7

16576
16633
16548
16560
16537
16530
16514

0 T/M 6 op D8

32960
33017
32932
32944
32921
32914
32898

*/

int latchPin = 5; //pin 12 of 595
int dataPin = 3; //pin 14 on the 595
int clockPin = 9; //pin 11 on the 595
int data = 1200;
int delayvar = 0;
  
void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  }

void loop()
{
  digitalWrite(latchPin, LOW);


  shiftOut(dataPin, clockPin, MSBFIRST, 505);
  shiftOut(dataPin, clockPin, MSBFIRST, (505 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);

  delay(delayvar);

    digitalWrite(latchPin, LOW);


  shiftOut(dataPin, clockPin, MSBFIRST, 676);
  shiftOut(dataPin, clockPin, MSBFIRST, (676 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);

  delay(delayvar);

    digitalWrite(latchPin, LOW);


  shiftOut(dataPin, clockPin, MSBFIRST, 1200);
  shiftOut(dataPin, clockPin, MSBFIRST, (1200 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);

  delay(delayvar);

    digitalWrite(latchPin, LOW);


  shiftOut(dataPin, clockPin, MSBFIRST, 2201);
  shiftOut(dataPin, clockPin, MSBFIRST, (2201 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);

  delay(delayvar);

    digitalWrite(latchPin, LOW);


  shiftOut(dataPin, clockPin, MSBFIRST, 4242);
  shiftOut(dataPin, clockPin, MSBFIRST, (4242 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);

  delay(delayvar);

    digitalWrite(latchPin, LOW);


  shiftOut(dataPin, clockPin, MSBFIRST, 8322);
  shiftOut(dataPin, clockPin, MSBFIRST, (8322 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);

  delay(delayvar);

    digitalWrite(latchPin, LOW);


  shiftOut(dataPin, clockPin, MSBFIRST, 16632);
  shiftOut(dataPin, clockPin, MSBFIRST, (16632 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);

  delay(delayvar);

    digitalWrite(latchPin, LOW);


  shiftOut(dataPin, clockPin, MSBFIRST, 32896);
  shiftOut(dataPin, clockPin, MSBFIRST, (32896 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);

  delay(delayvar);
  
}

