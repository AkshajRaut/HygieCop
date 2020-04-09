
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

int resval = 0;  // holds the value from the sensor
int respin = A0; // sensor is connected to A0 on NodeMCU
SimpleTimer timer;

char auth[] = "EtDIpLyE02rPbmKYWH0QrZHgAxbvXUqX"; //Authentication code required for connecting to Blynk Servers
char ssid[] = "RUBINAZ"; //WiFi SSID
char pass[] = "meferuby";//WiFi Password
WidgetLCD lcd(V5);

void setup()
{
  
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendData); //Sends data to Blynk app every 1 second
  timer.setInterval(1800000L, notify); //Sends a notification to sanitize hands every 30 minutes
  
}

void sendData()
{
  
  resval = analogRead(respin); //Read data from analog pin and store it to resval variable
  Serial.println(resval);
  Blynk.virtualWrite(V3, resval);
  if (resval<=500)
  {
   lcd.clear();
   lcd.print(0,0, "Level: High"); 
  } 
  else if (resval>500 && resval<=850)
  { 
   lcd.clear();
   lcd.print(0,0, "Level: Medium");
  } 
  else if (resval>850 && resval<=970)
  {
    lcd.clear();
    lcd.print(0,0, "Level: Low");
  }
  else if (resval>970)
  { 
    lcd.clear();
    lcd.print(0,0, "Level: Empty"); 
    Blynk.notify("Empty");
  }
}

void notify()
{
  Blynk.notify("Sanitize Hands");
}
void loop()
{
  
  Blynk.run();
  timer.run();
}
