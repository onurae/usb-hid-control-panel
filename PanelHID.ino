/******************************************************************************************
*                                                                                         *
*    USB HID Control Panel                                                                *
*                                                                                         *
*    Copyright (c) 2021 Onur AKIN <https://github.com/onurae>                             *
*    Licensed under the MIT License.                                                      *
*                                                                                         *
******************************************************************************************/

#include <Joystick.h>

#define switch1 5
#define switch2 6
#define switch3 7
#define switch4 8
#define blueButton 9
#define greenButton 16
#define redButton1 20 // A2
#define redButton2 18 // A0
#define redButton3 14
#define blackButton1 21 // A3
#define blackButton2 19 // A1
#define blackButton3 15

#define encoderCLK 2 // Interrupt pin
#define encoderDT 3
#define encoderSW 4

Joystick_ Joystick;
int lastState[12] = {0,0,0,0, // switches
                     0,0,     // green&blue buttons
                     0,0,0,   // red buttons
                     0,0,0};  // black buttons
int previousDT;
int previousCLK;
int previousSW;
int encoderPos = 0;
int previousEncoderPos = 0;

void setup()
{
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(switch3, INPUT_PULLUP);
  pinMode(switch4, INPUT_PULLUP);
  
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);

  pinMode(redButton1, INPUT_PULLUP);
  pinMode(redButton2, INPUT_PULLUP);
  pinMode(redButton3, INPUT_PULLUP);

  pinMode(blackButton1, INPUT_PULLUP);
  pinMode(blackButton2, INPUT_PULLUP);
  pinMode(blackButton3, INPUT_PULLUP);
  
  pinMode(encoderCLK, INPUT_PULLUP);
  pinMode(encoderDT, INPUT_PULLUP);
  pinMode(encoderSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderCLK), doEncoder, CHANGE);
  previousCLK = digitalRead(encoderCLK);
  previousDT = digitalRead(encoderDT);
  previousSW = digitalRead(encoderSW);

  Joystick.setZAxisRange(-127, 127);
  Joystick.begin();
}

void loop()
{
  int currentState[12] = {digitalRead(switch1),
                          digitalRead(switch2),
                          digitalRead(switch3),
                          digitalRead(switch4),
                          digitalRead(blackButton1),
                          digitalRead(redButton1),
                          digitalRead(blackButton2),
                          digitalRead(redButton2),
                          digitalRead(blackButton3),
                          digitalRead(redButton3),
                          digitalRead(greenButton),
                          digitalRead(blueButton)};
  for (int i = 0; i < 12; i++)
  {
    if (currentState[i] != lastState[i])
    {
      Joystick.setButton(i, !currentState[i]);
      lastState[i] = currentState[i]; 
    }
  }

  // 1 rev: 20 rot.
  int encoderScale = 16;
  if(encoderPos > previousEncoderPos)
  {
    int encoderValue = encoderScale * encoderPos - 1;
    if (encoderValue > 127) 
    {
      encoderPos = previousEncoderPos;
    }
    else
    {
      Joystick.setZAxis(encoderValue);
    }
  }
  if(encoderPos < previousEncoderPos)
  {
    int encoderValue = encoderScale * encoderPos + 1;  
    if (encoderValue < -127) 
    {
      encoderPos = previousEncoderPos;
    }
    else
    {
      Joystick.setZAxis(encoderValue);
    }
  }
  if (digitalRead(encoderSW) == 0)
  {
    encoderPos = 0;
    previousEncoderPos = 0;
    Joystick.setZAxis(0);
  }

  previousEncoderPos = encoderPos;
  
  delay(50);
}

void doEncoder()
{
  int actualCLK = digitalRead(encoderCLK);
  int actualEncoderDT = digitalRead(encoderDT);

  if ((actualCLK == 1) and (previousCLK == 0))
  {
    if (actualEncoderDT == 1)
    encoderPos--;
  }

  if ((actualCLK == 0) and (previousCLK == 1))
  {
    if (actualEncoderDT == 1)
    encoderPos++;
  }

  previousCLK = actualCLK;
}
