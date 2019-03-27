#include <Blynk.h>
#include <Bridge.h>
#include <CheapStepper.h>
#include <BlynkSimpleYun.h>
/*
 * cheapStepper_simple.ino
 * ///////////////////////////////////////////
 * using CheapStepper Arduino library v.0.2.0
 * created by Tyler Henry, 7/2016
 * ///////////////////////////////////////////
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
const int appButton = 7;   // the number of the pushbutton pin
int buttonState = 0;
int appButtonState = 0;      
// let's create a boolean variable to save the direction of our rotation
boolean moveClockwise = true;
char auth[] = "3036ca303403434497f1fd84659ca559";
int steps = 2048;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth);
  //Serial.println("Ready to start moving!");
}

void loop() {
  Blynk.run();
  // read the state of the buttons value:
  buttonState = digitalRead(buttonPin);
  appButtonState = digitalRead(appButton);
  moveClockwise = true;
  // if btn is high open and close 
  if (buttonState == HIGH || appButtonState == HIGH)
    {
      // open CW
      for (int s=0; s<steps; s++){
        stepper.step(moveClockwise);
        int nStep = stepper.getStep();
        if (nStep%64==0){ 
          // let's print the position to the console
          Serial.print("current step position: "); Serial.print(nStep);
          Serial.println();
        }//end if
      }//end for
      // let's wait one second
      delay(500) ;
      // and switch directions before  closing
      moveClockwise = !moveClockwise;
      // close CCW
      for (int s=0; s<steps; s++){
        stepper.step(moveClockwise);
        int nStep = stepper.getStep();
        if (nStep%64==0){ 
          // let's print the position to the console
          Serial.print("current step position: "); Serial.print(nStep);
          Serial.println();
          }// end if 
        }//end for close
  }// end if button is btn high
  delay(500);
}// end loop
