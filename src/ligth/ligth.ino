#include <DS3231M.h>
#include <Wire.h>
DS3231M_Class DS3231M;

int ledPin = 13;
int mainLight = 2;
int nightLight = 3;

void setup() {
  pinMode(ledPin, OUTPUT); 
  pinMode(mainLight, OUTPUT); 
  pinMode(nightLight, OUTPUT); 
  digitalWrite(ledPin, LOW);
  digitalWrite(mainLight, HIGH);
  digitalWrite(nightLight, LOW);

  Serial.begin(9600);
  while (!DS3231M.begin()) { // Initialize RTC communications
    Serial.println("Unable to find DS3231M. Checking again in 3 seconds.");
    delay(3000);
  } // of loop until device is located
DS3231M.adjust(DateTime (__DATE__,__TIME__));       // Use compile date/time
} // of setup

void loop() {
  DateTime now = DS3231M.now();
  Serial.println("");
  Serial.print("Year:   ");Serial.println(now.year());
  Serial.print("Month:  ");Serial.println(now.month());
  Serial.print("Day:    ");Serial.println(now.day());
  Serial.print("Hour:   ");Serial.println(now.hour());
  Serial.print("Minute: ");Serial.println(now.minute());
  Serial.print("Second: ");Serial.println(now.second());
  
  

  if (now.hour() >= 23 || now.hour() < 8)
    {
      digitalWrite(nightLight, HIGH);
      digitalWrite(mainLight, LOW);
      Serial.print(" night");
    }
    else
    {
      digitalWrite(nightLight, LOW);
      digitalWrite(mainLight, HIGH);
      Serial.print(" day");
    }
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5000);             // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(5000);             // wait for a second
}
