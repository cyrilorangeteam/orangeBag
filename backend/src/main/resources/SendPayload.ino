/*
* Copyright (C) 2017 Orange
*
* This software is distributed under the terms and conditions of the 'Apache-2.0'
* license which can be found in the file 'LICENSE.txt' in this package distribution
* or at 'http://www.apache.org/licenses/LICENSE-2.0'.
*/

/* Orange LoRa Explorer Kit
*
* Version:     1.0-SNAPSHOT
* Created:     2017-02-15 by Karim BAALI
* Modified:    2017-04-21 by Halim BENDIABDALLAH
*			         2017-05-09 by Karim BAALI
*              2017-10-27 by Karim BAALI
*/

#include <OrangeForRN2483.h>

#define debugSerial SerialUSB

#define DHTPIN A8;     // what pin we're connected to
#define DHTPIN A0;

#define DHTPIN A1;

// The following keys are for structure purpose only. You must define YOUR OWN.
const uint8_t appEUI[8] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
const uint8_t appKey[16] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

bool first = true;
bool res = false;
bool activated = false;
int currentVal = 1;
const int buttonPort = 4;
int buttonRead;
bool joinNetwork()
{

  debugSerial.println("Join Request");
  OrangeForRN2483.setDataRate(DATA_RATE_3); // Set DataRate to SF11/125Khz
  return OrangeForRN2483.joinNetwork(appEUI, appKey);
}

void setup() {
  debugSerial.begin(57600);
  pinMode(A0, OUTPUT);
  pinMode(buttonPort, INPUT);
  while ((!debugSerial) && (millis() < 10000)) ;
  OrangeForRN2483.init();
  res = joinNetwork();
}

void loop() {

if(activated){
      uint8_t lightValue = analogRead(A8);
      if(lightValue>150){
          debugSerial.println("light is high");
          digitalWrite(A0, HIGH);
          delay(2000);
          digitalWrite(A0, LOW);
      }


    if(res)
    {
      OrangeForRN2483.enableAdr();
      const uint8_t size = 4;
      uint8_t port = 5;
      uint8_t data[size] = { lightValue }; // Hello
      LpwaOrangeEncoder.flush();
      LpwaOrangeEncoder.addUInt(lightValue);
      int8_t len;
      uint8_t* frame = LpwaOrangeEncoder.getFramePayload(&len);

      debugSerial.println(currentVal);
      debugSerial.println(lightValue);
      if((currentVal-lightValue) > 10){
              debugSerial.println("More than 10 ");
              bool sent = OrangeForRN2483.sendMessage(frame, len, port);
              if(sent){
                delay(5000);
                currentVal = lightValue;
                }

      }
      if ((lightValue-currentVal) > 10){
              debugSerial.println("More than 10 ");
              bool sent = OrangeForRN2483.sendMessage(frame, len, port);
              if(sent){
                delay(5000);
                currentVal = lightValue;
                }
      }
      }

      else {debugSerial.println("Join Failed");}

      } else {
        debugSerial.println("Not Activated");
      }


        delay(1000);

   buttonRead = digitalRead(buttonPort);
    if(buttonRead == 1){
          debugSerial.println("button read : ");
          debugSerial.println(buttonRead);
      if(activated){
          activated = false;
      } else activated = true;
    }

      }

