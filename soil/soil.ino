#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFi101.h>
#include <BlynkSimpleMKR1000.h>

// you should get Auth Token in the Blynk App + via email; go to the Project Settings (nut icon)
char auth[] = "x";

// your WiFi credentials.; set password to "" for open networks.
char ssid[] = "x";
char pass[] = "x";

BlynkTimer timer;

#define soilPin A1;
#define soilPower 7;

int moistureLevel = 0; //value for storing moisture value

//Rather than powering the sensor through the 3.3V or 5V pins,
//we'll use a digital pin to power the sensor. This will
//prevent corrosion of the sensor as it sits in the soil.

//This is a function used to get the soil moisture content

int getMoisture()
{
    digitalWrite(soilPower, HIGH); //turn D7 "On"
    delay(10);                     //wait 10 milliseconds
    val = analogRead(soilPin);     //Read the SIG value form sensor
    digitalWrite(soilPower, LOW);  //turn D7 "Off"
    return val;                    //send current moisture value
}

void printStatus()
{
    Serial.print("Soil Moisture = ");
    //get soil moisture value from the function below and print it
    Serial.println(readSoil());
    if (readSoil() < 420)
    {
        Serial.print("Dry soil");
    }
    else
    {
        Serial.print("Wet soil");
    }

    //This 1 second timefrme is used so you can test the sensor and see it change in real-time.
    //For in-plant applications, you will want to take readings much less frequently.
    delay(1000); //take a reading every second
}

void myTimerEvent()
{
  float moistureLevel = getMoisture(); // try not to send >10 values/second
  
  Blynk.virtualWrite(V5, moistureLevel); // send data to app
}

void setup()
{
    Serial.begin(9600); // open serial over USB

    pinMode(soilPower, OUTPUT);   //Set D7 as an OUTPUT
    digitalWrite(soilPower, LOW); //Set to LOW so no power is flowing through the sensor

    Blynk.begin(auth, ssid, pass); // connect to Wifi

    timer.setInterval(1000L, myTimerEvent); // setup a function to be called every second
}

void loop()
{
    // run Blynk software
    Blynk.run();
    timer.run();
}