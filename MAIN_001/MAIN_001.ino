//Fortune Machine Computer 机器电脑
//Yoe Yat System Design 如日系统设计

//fast_body_temperature_meter


/****************************************************************************** 
MLX90614_Set_Emissivity
How to read and set the MLX90614's emissivity coefficient

Emissivity is a relative measure of how efficiently an object
radiates heat. A perfect thermal emitter has a emissivity of
1.0, but most real-world objects range from 0 to 1.

For example, human skin has an emissivity of about 0.98.
Shiny metals have a very low emissivity, for example polished
aluminum has an emissivity of 0.05. Painted aluminum has an
emissivity of 0.45. Here's a good reference:
http://www.thermoworks.com/emissivity_table.html

If you get really wacky values after setting the emissivity,
try cycling power to the MLX90614.

To set the emissivity, change the value of the 
newEmissivity variable above setup(). Allowable values are
between 0.1 and 1.0.

Hardware Hookup (if you're not using the eval board):
MLX90614 ------------- Arduino
  VDD ------------------ 3.3V
  VSS ------------------ GND
  SDA ------------------ SDA (A4 on older boards)
  SCL ------------------ SCL (A5 on older boards)
  
An LED can be attached to pin 8 to monitor for any read errors.

Jim Lindblom @ SparkFun Electronics
October 23, 2015
https://github.com/sparkfun/SparkFun_MLX90614_Arduino_Library

Development environment specifics:
Arduino 1.6.5
SparkFun IR Thermometer Evaluation Board - MLX90614
******************************************************************************/

#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library

#include <SoftwareSerial.h>
#include "pitches.h"

SoftwareSerial mySerial(3, 4); // RX, TX



IRTherm therm; // Create an IRTherm object to interact with throughout

const byte LED_PIN = 13; // Optional LED attached to pin 8 (active low)

float newEmissivity = 0.95;



void setup() 
{
  Serial.begin(9600); // Initialize Serial to log output
  //Serial.println("Press any key to begin");
  //while (!Serial.available()) ;
  
  mySerial.begin(9600);

  therm.begin(); // Initialize thermal IR sensor
  delay(500);
  therm.setUnit(TEMP_C); // Set the library's units to Farenheit

  // Call setEmissivity() to configure the MLX90614's 
  //emissivity compensation:
  //delay(1000);
  therm.setEmissivity(newEmissivity);
  
  //Serial.println("Max: " + String(therm.maximum()));
  //Serial.println("Min: " + String(therm.minimum()));
  //readEmissivity() can be called to read the device's
  // configured emissivity -- it'll return a value between
  // 0.1 and 1.0.
  Serial.println("Emissivity: " + String(therm.readEmissivity()));
  pinMode(LED_BUILTIN, OUTPUT); // LED pin as output
  digitalWrite(LED_BUILTIN, LOW); // LED OFF
}
float lastReading = 0;
bool isGreen = false;
bool isRed = false;
bool isWhite = false;
bool isRecording = false;
float currentRecorded = 0;
float currentReading = 0;

void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH); //LED on
  
  // Call therm.read() to read object and ambient temperatures from the sensor.
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    // Use the object() and ambient() functions to grab the object and ambient
  // temperatures.
  // They'll be floats, calculated out to the unit you set with setUnit().
    //Serial.print("Object: " + String(therm.object(), 2));
    //Serial.write('°'); // Degree Symbol
    //Serial.println("C");
    //Serial.print("Ambient: " + String(therm.ambient(), 2));
    //Serial.write('°'); // Degree Symbol
    //Serial.println("C");
    
    currentReading = therm.object();
    currentReading=currentReading+0.6;
    //Serial.print("\r\n");
    //if (currentReading>35){
    //  Serial.print("Alert\r\n");
    //}

    if (currentReading > 35 and currentReading<37.5){
      isRecording =true;
      if (currentReading>currentRecorded){
        currentRecorded=currentReading;
      }
      
      if (!isGreen and !isRed){
            mySerial.print("t0.bco=2016");
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            tone(8,  NOTE_A5, 200);
            delay(200);

            
            //Serial.print("\r\n");
            isGreen = true;
            isRed = false;
            isWhite = false;
            
      }
    }
    else if (currentReading > 37.5 ){
      isRecording =true;
      if (currentReading>currentRecorded){
        currentRecorded=currentReading;
      }
      if (!isRed){
            mySerial.print("t0.bco=63488");
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            mySerial.print("t0.txt=\"" + String(currentRecorded, 1)+"°C\"");
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            //Serial.print("\r\n");
            
            isGreen = false;
            isRed = true;
            isWhite = false;     
            delay(10);     
            tone(8,  NOTE_A5, 200);
            delay(250);  
            tone(8,  NOTE_A5, 200);
            delay(250);  
            tone(8,  NOTE_A5, 200);
            delay(250);  
            tone(8,  NOTE_A5, 200);
            delay(250);  
            tone(8,  NOTE_A5, 200);
            delay(250);  
            tone(8,  NOTE_A5, 200);
            delay(250);  
      }
    }else{
      if (!isWhite){
            delay(300);
            mySerial.print("t0.bco=65535");
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            mySerial.print("qr0.txt=\"" + String(currentRecorded, 1)+"°C\"");
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            mySerial.write(0xFF);
            
            isGreen = false;
            isRed = false;
            isWhite = true;
            
            isRecording =false;
            
            currentRecorded = 0;              
      }
    }
    //Serial.println();
    if (isRecording){
        //Serial.print("t0.txt=\"" + String(currentRecorded, 1)+"°C\"");
        //Serial.write(0xFF);
        //Serial.write(0xFF);
        //Serial.write(0xFF);
        mySerial.print("t0.txt=\"" + String(currentRecorded, 1)+"°C\"");
        mySerial.write(0xFF);
        mySerial.write(0xFF);
        mySerial.write(0xFF);
  
    }else{
//        Serial.print("t0.txt=\"" + String(currentReading, 1)+"°C\"");
//        Serial.write(0xFF);
//        Serial.write(0xFF);
//        Serial.write(0xFF);
        mySerial.print("t0.txt=\"" + String(currentReading, 1)+"°C\"");
        mySerial.write(0xFF);
        mySerial.write(0xFF);
        mySerial.write(0xFF);
    }

    lastReading = currentReading;
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
}
