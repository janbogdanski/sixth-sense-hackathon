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
  
  delay(delayTime);

  analogWrite(pin1, outValue1);
  analogWrite(pin2, outValue2);
  analogWrite(pin3, outValue3);
  analogWrite(pin4, outValue4);
  analogWrite(pin5, outValue5);
  analogWrite(pin6, outValue6);
}

void serialEvent() 
{
  while (Serial.available()) 
  {
    Serial.setTimeout(timeout);
    inValue = (byte)Serial.parseInt();
    
    byte calcPin = calculatePin(inValue);
    byte calcValue = calculateOutValue(inValue);

    switch(calcPin)
    {
      case 0:
        outValue1 = calcValue;
        break;
      case 1:
        outValue2 = calcValue;
        break;
      case 2:
        outValue3 = calcValue;
        break;
      case 3:
        outValue4 = calcValue;
        break;
      case 4:
        outValue5 = calcValue;
        break;
      case 5:
        outValue6 = calcValue;
        break;
      default:
        break;
    }
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

