#include <Arduino.h>
//#include <Servo.h>
#include <VarSpeedServo.h>          // Download Here: https://github.com/netlabtoolkit/VarSpeedServo
#include "DFRobotDFPlayerMini.h"    // Download Here: https://github.com/DFRobot/DFRobotDFPlayerMini

#define LED_MODE   1

VarSpeedServo myservo;
#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))   // Using a soft serial port
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/10, /*tx =*/11);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif
DFRobotDFPlayerMini myDFPlayer;

const int ledPin = 3;
const int buttonPin = 4;
const int servoPin = 8;
//const int speakerPin = 6;

int servoPos        = 100;    // Current servo position
int servoStep       = 1;    // How many degrees to move each step
bool servoShouldMove = false;

// Variables will change:
int ledState = LOW;         // the current state of the output pin
int ledFadeValue = 0;
int ledFadeStep = 5;
int ledFadeInterval = 60;   //milliseconds
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastLedFadeTime = 0;

int BassTab[]={1911,1702,1516,1431,1275,1136,1012};//bass 1~7
bool makeSound = false;
int upOrDown = 0;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
    //pinMode(speakerPin, OUTPUT);
    digitalWrite(ledPin, ledState);
    myservo.attach(servoPin);

    FPSerial.begin(9600);
    if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
      while(true){
        delay(0); // Code to compatible with ESP8266 watch dog.
      }
    }
    Serial.println(F("DFPlayer Mini online."));

    myDFPlayer.volume(10);  //Set volume value. From 0 to 30

}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
  }

  if (reading != buttonState) {
    buttonState = reading;
    
    if (buttonState == LOW) {  //button is pressed
        ledState = !ledState;
        ledFadeValue = 0;
        lastLedFadeTime = millis();
        servoShouldMove = true;
    }  
  }

  if (servoShouldMove) {
    servoPos += servoStep;
    if (servoPos >= 100) {
        servoPos = 50;
        servoStep = -servoStep; // change direction
        servoShouldMove = false;
        upOrDown = 1;
        makeSound = true;
    }
    else if (servoPos <= 50) {
        servoPos = 100;
        servoStep = -servoStep; // change direction
        servoShouldMove = false;
        upOrDown = 0;
        makeSound = true;
    }
  }
  
  
  myservo.write(servoPos, 15);
  digitalWrite(ledPin, ledState);

  if (makeSound){
    if(upOrDown == 1){
      delay(1500);
      myDFPlayer.play(1);  //Play the first mp3
    }
    /*else if (upOrDown == 0) {
      delay(2500);
      myDFPlayer.play(2);
    }*/
    makeSound = false;
  }
  
}

/*void sound(uint8_t note_index)
{
    for(int i=0;i<100;i++)
    {
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(BassTab[note_index]);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(BassTab[note_index]);
    }
}*/
