/*
 eMAG Hackathon 2016
 We Think Future
 6th Sense
 */

//input value from COM port
byte inValue = 0;

//output pin numbers
int pin1 = 3;
int pin2 = 5;
int pin3 = 6;
int pin4 = 9;
int pin5 = 10;
int pin6 = 11;

//values set to output
int outValue1 = 0;
int outValue2 = 0;
int outValue3 = 0;
int outValue4 = 0;
int outValue5 = 0;
int outValue6 = 0;

long delayTime = 10;
long timeout = 10000000;
long serialSpeed = 9600;

void setup() 
{
  Serial.begin(serialSpeed);
}

void loop()
{
  delay(delayTime);
 
  analogWrite(pin1, 0);
  analogWrite(pin2, 0);
  analogWrite(pin3, 0);
  analogWrite(pin4, 0);
  analogWrite(pin5, 0);
  analogWrite(pin6, 0);
}

void serialEvent() 
{
  while (Serial.available()) 
  {
    Serial.setTimeout(timeout);
    inValue = (byte)Serial.parseInt();
    
    byte calcPin = calculatePin(inValue);
    byte calcValue = calculateOutValue(inValue);
  }
}

byte calculateOutValue(byte input)
{
  /*
   * get five least-significant bits of incoming byte
   * it will become value for output on Arduino
   */
  bitClear(input, 7);
  bitClear(input, 6);
  bitClear(input, 5);

  return input;
}

int calculatePin(byte input)
{
  /*
   * get three most-significant bits of incoming byte
   * it will become pin number for sending output on Arduino
   */  
  int pinNumber = input >> 5;
  
  return pinNumber;
}

