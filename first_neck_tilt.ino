#include <Arduino.h>
#include <Servo.h>

Servo myservo;



//1: toggle mode, 2: follow mode
#define LED_MODE   1

const int ledPin = 3;      // the number of the LED pin, D3
const int buttonPin = 4;    // the number of the pushbutton pin, D4
const boolean breathMode = true;  // if or not the led lights as breath mode when it's on
const int servoPin  = 5;
const int speakerPin = 8;

int servoPos        = 0;    // Current servo position
int servoStep       = 1;    // How many degrees to move each step

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

void setup() {
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(speakerPin, OUTPUT);
    digitalWrite(ledPin, ledState);
    myservo.attach(servoPin);
}

void loop() {
    int reading = digitalRead(buttonPin);

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != buttonState) {
            buttonState = reading;

#if LED_MODE == 1
            if (buttonState == LOW) {  //button is pressed
                ledState = !ledState;
                ledFadeValue = 0;
                lastLedFadeTime = millis();
            }
#else
            if (buttonState == LOW) {  //button is pressed
                ledState = HIGH;
                ledFadeValue = 0;
                lastLedFadeTime = millis();
            } else {                   //button is released
                ledState = LOW;
            }
#endif
        }
    }

    // set the LED:
    if (breathMode && ledState != LOW) {
        if (millis() - lastLedFadeTime > ledFadeInterval) {
            lastLedFadeTime = millis();
            analogWrite(ledPin, ledFadeValue);
            ledFadeValue += ledFadeStep;
            if (ledFadeValue > 255){
                ledFadeValue = 255 - ledFadeStep;
                ledFadeStep = -ledFadeStep;
            } else if (ledFadeValue < 0) {
                ledFadeValue = 0;
                ledFadeStep = -ledFadeStep;
            }
            // Move the servo by 'servoStep' degrees
            servoPos += servoStep;

            // Reverse direction if we hit the ends
            if (servoPos >= 90) {
                servoPos = 90;
                servoStep = -servoStep; // change direction
                /*for(int note_index=0;note_index<7;note_index++)
                {
                    sound(note_index);
                }*/
            }
            else if (servoPos <= 20) {
                servoPos = 20;
                servoStep = -servoStep; // change direction
            }

            // Command servo to go to the new position
            myservo.write(servoPos);

        }
    } else {
        digitalWrite(ledPin, ledState);
    }

    lastButtonState = reading;
}

void sound(uint8_t note_index)
{
    for(int i=0;i<100;i++)
    {
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(BassTab[note_index]);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(BassTab[note_index]);
    }
}