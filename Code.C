int ledPins[] = {11, 10};
int ledState[] = {6, 6};
int factor = 255 / 6;
int buttonPins[] = {2, 4, 7, 8, 12};
int buttonPressed[] = {0, 0, 0, 0, 0};
int ledPinsSize = sizeof(ledPins) / sizeof(int);
int buttonPinsSize = sizeof(buttonPins) / sizeof(int);
int selection = 0;
int latchPin = 5; //pin 12 of 595
int dataPin = 3; //pin 14 on the 595
int clockPin = 9; //pin 11 on the 595
boolean on = true;

int zero[] = {1, 1, 1, 0, 1, 1, 1};
int one[] = {0, 0, 1, 0, 0, 1, 0};
int two[] = {1, 0, 1, 1, 1, 0, 1};
int three[] = {1, 1, 0, 1, 1, 0, 1};
int four[] = {};
int five[] = {};
int six[] = {};


void setup() {
  for (int i = 0; i < ledPinsSize; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < buttonPinsSize; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void displayLEDS() {
  for (int i = 0; i < ledPinsSize; i++) {
    analogWrite(ledPins[i], ledState[i]*factor);
  }
}

void checkButtons() {
  for (int i = 0; i < buttonPinsSize; i++) {
    int buttonState = digitalRead(buttonPins[i]);
    if (buttonState == LOW) {
      buttonPressed[i] = 1;
    } else {
      if (buttonPressed[i] == 1) {
        clickButton(i);
      }
      buttonPressed[i] = 0;
    }
  }
}

void clickButton(int x) {
  switch (x) {
    case 0:     //turn kookplaat on or off
      Serial.println("on/of");
      if (on) {
        on = false;
        resetPinStates();
      } else {
        on = true;
      }
      Serial.println(on);
      break;
    case 1:     //select right LED
      Serial.println("select right LED");
      if (selection < ledPinsSize - 1) {
        selection++;
      } else {
        selection = 0;
      }
      Serial.println(selection);
      break;
    case 2:     //select left LED
      Serial.println("select left LED");
      if (selection > 0) {
        selection--;
      } else {
        selection = ledPinsSize - 1;
      }
      Serial.println(selection);
      break;
    case 3:     //put LED higher
      Serial.println("put LED higher");
      if (on && ledState[selection] < 6) {
        ledState[selection]++;
      }
      Serial.println(ledState[selection]);
      break;
    case 4:     //put LED lower
      Serial.println("put LED lower");
      if (ledState[selection] > 0) {
        ledState[selection]--;
      }
      Serial.println(ledState[selection]);
      break;
  }
}

void resetPinStates() {
  for (int i = 0; i < ledPinsSize; i++) {
    ledState[i] = 0;
  }
}

void displayNumber(int list[]) {
  int number = 7;
  for (int i = 0; i < 8; i++) {
    digitalWrite(number, list[i]);
    number++;
  }
}

void loop() {
  checkButtons();
  displayLEDS();
  for (i = 0; i < ledPinsSize; i++){
  display(i)
  }
}
void shiftOutNumber(number){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, number);
  shiftOut(dataPin, clockPin, MSBFIRST, (number >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
}

void display(displaynumber){
int calcvar = 0;
    for (i = 0; i <= displaynumber; i++){
    calcvar += 128*Math.pow(2, displaynumber);
    } 
    switch(ledState[displaynumber]{
        case 0
            shiftOutNumber(320+calcvar);
        break;
        case 1
            shiftOutNumber(377+calcvar);
        break;
        case 2
            shiftOutNumber(292+calcvar);
        break;
        case 3
            shiftOutNumber(304+calcvar);
        break;
        case 4
            shiftOutNumber(281+calcvar);
        break;
        case 5
            shiftOutNumber(274+calcvar);
        break;
        case 6
            shiftOutNumber(258+calcvar);
        break;
    }
}
/*void display(displaynumber){
switch(displaynumber){
case 0
switch(ledState[displaynumber]{
case 0
    shiftOutNumber(448);
break;
case 1
    shiftOutNumber(505);
break;
case 2
    shiftOutNumber(420);
break;
case 3
    shiftOutNumber(432);
break;
case 4
    shiftOutNumber(409);
break;
case 5
    shiftOutNumber(402);
break;
case 6
    shiftOutNumber(386);
break;
}
break;
case 1
switch(ledState[displaynumber]{
case 0
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 704);
  shiftOut(dataPin, clockPin, MSBFIRST, (704 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 1
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 761);
  shiftOut(dataPin, clockPin, MSBFIRST, (761 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 2
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 676);
  shiftOut(dataPin, clockPin, MSBFIRST, (676 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 3
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 688);
  shiftOut(dataPin, clockPin, MSBFIRST, (688 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 4
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 665);
  shiftOut(dataPin, clockPin, MSBFIRST, (665 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 5
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 658);
  shiftOut(dataPin, clockPin, MSBFIRST, (658 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 6
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 642);
  shiftOut(dataPin, clockPin, MSBFIRST, (642 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
}
break;
case 2
switch(ledState[displaynumber]{
case 0
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 1216);
  shiftOut(dataPin, clockPin, MSBFIRST, (1216 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 1
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 1273);
  shiftOut(dataPin, clockPin, MSBFIRST, (1273 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 2
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 1188);
  shiftOut(dataPin, clockPin, MSBFIRST, (1188 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 3
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 1200);
  shiftOut(dataPin, clockPin, MSBFIRST, (1200 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 4
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 1177);
  shiftOut(dataPin, clockPin, MSBFIRST, (1177 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 5
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 1170);
  shiftOut(dataPin, clockPin, MSBFIRST, (1170 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 6
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 1154);
  shiftOut(dataPin, clockPin, MSBFIRST, (1154 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
}
break;
case 3
switch(ledState[displaynumber]{
case 0
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 2240);
  shiftOut(dataPin, clockPin, MSBFIRST, (2240 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 1
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 2297);
  shiftOut(dataPin, clockPin, MSBFIRST, (2297 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 2
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 2212);
  shiftOut(dataPin, clockPin, MSBFIRST, (2212 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 3
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 2224);
  shiftOut(dataPin, clockPin, MSBFIRST, (2224 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 4
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 2201);
  shiftOut(dataPin, clockPin, MSBFIRST, (2201 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 5
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 2194);
  shiftOut(dataPin, clockPin, MSBFIRST, (2194 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 6
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 2178);
  shiftOut(dataPin, clockPin, MSBFIRST, (2178 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
}
break;
case 4
switch(ledState[displaynumber]{
case 0
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 4288);
  shiftOut(dataPin, clockPin, MSBFIRST, (4288 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 1
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 4345);
  shiftOut(dataPin, clockPin, MSBFIRST, (4345 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 2
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 4260);
  shiftOut(dataPin, clockPin, MSBFIRST, (4260 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 3
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 4272);
  shiftOut(dataPin, clockPin, MSBFIRST, (4272 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 4
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 4249);
  shiftOut(dataPin, clockPin, MSBFIRST, (4249 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 5
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 4242);
  shiftOut(dataPin, clockPin, MSBFIRST, (4242 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 6
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 4226);
  shiftOut(dataPin, clockPin, MSBFIRST, (4226 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
}
break;
case 5
switch(ledState[displaynumber]{
case 0
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 8384);
  shiftOut(dataPin, clockPin, MSBFIRST, (8384 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 1
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 8441);
  shiftOut(dataPin, clockPin, MSBFIRST, (8441 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 2
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 8356);
  shiftOut(dataPin, clockPin, MSBFIRST, (8356 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 3
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 8368);
  shiftOut(dataPin, clockPin, MSBFIRST, (8368 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 4
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 8345);
  shiftOut(dataPin, clockPin, MSBFIRST, (8345 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 5
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 8338);
  shiftOut(dataPin, clockPin, MSBFIRST, (8338 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 6
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 8322);
  shiftOut(dataPin, clockPin, MSBFIRST, (8322 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
}
break;
case 6
switch(ledState[displaynumber]{
case 0
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 16576);
  shiftOut(dataPin, clockPin, MSBFIRST, (16576 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 1
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 16633);
  shiftOut(dataPin, clockPin, MSBFIRST, (16633 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 2
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 16548);
  shiftOut(dataPin, clockPin, MSBFIRST, (16548 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 3
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 16560);
  shiftOut(dataPin, clockPin, MSBFIRST, (16560 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 4
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 16537);
  shiftOut(dataPin, clockPin, MSBFIRST, (16537 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 5
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 16530);
  shiftOut(dataPin, clockPin, MSBFIRST, (16530 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 6
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 16514);
  shiftOut(dataPin, clockPin, MSBFIRST, (16514 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
}
break;
case 7
switch(ledState[displaynumber]{
case 0
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 32960);
  shiftOut(dataPin, clockPin, MSBFIRST, (32960 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 1
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 33017);
  shiftOut(dataPin, clockPin, MSBFIRST, (33017 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 2
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 32932);
  shiftOut(dataPin, clockPin, MSBFIRST, (32932 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 3
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 32944);
  shiftOut(dataPin, clockPin, MSBFIRST, (32944 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 4
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 32921);
  shiftOut(dataPin, clockPin, MSBFIRST, (32921 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 5
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 32914);
  shiftOut(dataPin, clockPin, MSBFIRST, (32914 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
case 6
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 32898);
  shiftOut(dataPin, clockPin, MSBFIRST, (32898 >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
break;
}
break;
}
}*/