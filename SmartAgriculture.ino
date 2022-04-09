#define BLYNK_TEMPLATE_ID "TMPLVZePk3Xf"
#define BLYNK_DEVICE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "2ke6VDxWRgbQP5ZGAkAA80ecspFFvR7B"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>

#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "NSUT-Campus";  // type your wifi name
char pass[] = "";  // type your wifi password

BlynkTimer timer;

#define DHTPIN 4 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
int sensor=0;
int output=0;

//#define pirPin 5                // Input for HC-S501
int pirValue;                   // Place to store read PIR Value
int pinValue;                   //Variable to read virtual pin

int pir_sensor =  D1; 
int relaypin = D6;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);

  sensor=analogRead(A0);
  output=(145-map(sensor,0,1023,0,100)); //in place 145 there is 100(it change with the change in sensor)
  Serial.print(output);
  Blynk.virtualWrite(V2,output);

  
  int pir = digitalRead(pir_sensor);
    if(pir) 
     { 
       Serial.println("Motion detected");
       Blynk.notify("Motion detected");
     } 
  Blynk.virtualWrite(V3,pir);

  delay(1000);
  
}


void setup()
{   
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
      

  timer.setInterval(100L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();

    
}
