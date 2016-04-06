/*    
 * EdisonBle.c
 * This is a deo for using edsion bluetooth
 *   
 * Copyright (c) 2015 seeed technology inc.  
 * Author      : Jiankai.li  
 * Create Time:  Apr 2016
 * Change Log : 
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <Wire.h>
#include <Intel_Edison_BT_SPP.h>

#define RelayPin 3
#define ButtonPin 4
uint8_t LightFlag = false;
Intel_Edison_BT_SPP spp = Intel_Edison_BT_SPP();

void setup() {
  Serial.begin(115200);
  Serial.println("Intel Edison BT SPP test!");
  
  spp.open();

  pinMode(RelayPin,OUTPUT);
  TurnOffLight();
  
  pinMode(ButtonPin,INPUT);
  attachInterrupt(ButtonPin,ButtonPressed,FALLING);
}

void loop() {

  ssize_t size = spp.read();
  Serial.println("Read some data");
  if (size != -1) {
        String Mystring;
        Mystring = spp.getBuf();
        Mystring.toUpperCase();
        Serial.println(Mystring);
        if(Mystring == "ON"){
            Serial.println("Turn on Light");
            TurnOnLight();
            LightFlag = true;
        }
        else if(Mystring == "OFF"){
            Serial.println("Turn off Light");
            TurnOffLight();
            LightFlag = false;
        } else {
            Serial.println("Others");
        }
    
  } else {
    // Well, some error here 
    delay(200);
  }
  
}

void TurnOnLight()
{
    digitalWrite(RelayPin,HIGH);
}

void TurnOffLight()
{
    digitalWrite(RelayPin,LOW);
}


void ButtonPressed()
{
    Serial.println("Button Pressed");
    if(LightFlag == true){
        TurnOffLight();
        LightFlag = false;
    } else{
        TurnOnLight();
        LightFlag = true;
    }
}