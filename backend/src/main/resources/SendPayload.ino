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

#define DHTPIN A8     // what pin we're connected to

// The following keys are for structure purpose only. You must define YOUR OWN. 
const uint8_t appEUI[8] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
const uint8_t appKey[16] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

bool first = true;
bool res = false;  
bool joinNetwork()
{             
  OrangeForRN2483.setDataRate(DATA_RATE_3); // Set DataRate to SF11/125Khz
  return OrangeForRN2483.joinNetwork(appEUI, appKey);
}

void setup() {
  debugSerial.begin(57600); 
  
  while ((!debugSerial) && (millis() < 10000)) ;

  OrangeForRN2483.init();
  
   res = joinNetwork();
}

void loop() {

  {
    debugSerial.println("Join Request");
    if(res)
    {
      debugSerial.println("Join Success");
      OrangeForRN2483.enableAdr();

      uint8_t lightValue = analogRead(A8);
      SerialUSB.println(lightValue);


  const uint8_t size = 4;
  uint8_t port = 5;
  uint8_t data[size] = { lightValue }; // Hello
LpwaOrangeEncoder.flush();
LpwaOrangeEncoder.addUInt(lightValue);




    int8_t len;
    uint8_t* frame = LpwaOrangeEncoder.getFramePayload(&len);
    bool res = OrangeForRN2483.sendMessage(frame, len, port);


    

 // OrangeForRN2483.sendMessage(data, size, port); // send unconfirmed message

      delay(20000);
      }else debugSerial.println("Join Failed");
    debugSerial.println("Program Finished");
  }
}



