#include <Bridge.h>
#include <CheapStepper.h>
#include <BlynkSimpleYun.h>
/*
 * ///////////////////////////////////////////
 * using CheapStepper Arduino library v.0.2.0
 * created by Tyler Henry, 7/2016
 * ///////////////////////////////////////////
 * Modfied by David Gordon,Jonatan Opitek and Mohamad Shiha  
 * for the IoT Project 
 * //////////////////////////////////////////
 * 
 * 
 * ## NOTE !! ## uncomment lins (31,35,38 and 40(inline)) to use it with blynk. ##
 */

CheapStepper stepper;
// here we declare our stepper using default pins:
// arduino pin <--> pins on ULN2003 board:
// 8 <--> IN1
// 9 <--> IN2
// 10 <--> IN3
// 11 <--> IN4

// variable for reading the pushbutton status
const int buttonPin = 6;   // the number of the pushbutton pin
const int appButton = 7;   // the number of the pushbutton on the App
int buttonState = 0;
int appButtonState = 0;      
boolean moveClockwise; // to control the turn direction 
char auth[] = "3036ca303403434497f1fd84659ca559"; // used for the blynk app
int steps = 512; // stepps to open and close the flopper

void setup() {
  pinMode(buttonPin, INPUT);
  //Blynk.begin(auth);
}

void loop() {
  //Blynk.run();
  // read the state of the buttons value:
  buttonState = digitalRead(buttonPin);
  //appButtonState = digitalRead(appButton);
  // if btn is high open and close 
  if (buttonState == HIGH /*|| appButtonState == HIGH*/)
    {
      moveClockwise= false;
      TurnStepper(moveClockwise);
      delay(75) ;
      TurnStepper(!moveClockwise);
  }// end if button is btn high
  delay(100);
}// end loop




void TurnStepper(bool turnDirection){
  for (int s=0; s<steps; s++){
        stepper.step(turnDirection);
      }
}
