//#include <Blynk.h>
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
const int buttonPin = 6;     // the number of the pushbutton pin
int buttonState = 0;      
// let's create a boolean variable to save the direction of our rotation
boolean moveClockwise = true;
char auth[] = "3036ca303403434497f1fd84659ca559";
int steps = 1024;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth);
  //Serial.println("Ready to start moving!");
}

void loop() {
  Blynk.run();
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH)
    {
      // a full rotation (4096 mini-steps)
      // we'll go step-by-step using the step() function
      // 1024 to open it 90 d
      for (int s=0; s<steps; s++){
        // this will loop 4096 times
        // 4096 steps = full rotation using default values
        // let's move one "step" (of the 4096 per full rotation)
        stepper.step(moveClockwise);
        /* the direction is based on moveClockwise boolean:
         * true for clockwise, false for counter-clockwise
         * -- you could also say stepper.stepCW(); or stepper.stepCCW();
         */
        // now let's get the current step position of motor
        int nStep = stepper.getStep();
        // and if it's divisible by 64... 
        if (nStep%64==0){ 
          // let's print the position to the console
          Serial.print("current step position: "); Serial.print(nStep);
          Serial.println();
          
        }//end if
      }//end for
        
      // now we've moved 4096 steps
      // let's wait one second
      delay(1000) ;
      // and switch directions before starting loop() again
      moveClockwise = !moveClockwise;
      // to close 
      for (int s=0; s<steps; s++){
      // this will loop 4096 times
      // 4096 steps = full rotation using default values
      /* Note:
      * you could alternatively use 4076 steps... 
      * if you think your 28BYJ-48 stepper's internal gear ratio is 63.68395:1 (measured) rather than 64:1 (advertised)
      * for more info, see: http://forum.arduino.cc/index.php?topic=71964.15)
      */
      // let's move one "step" (of the 4096 per full rotation)
      stepper.step(moveClockwise=false);
      /* the direction is based on moveClockwise boolean:
       * true for clockwise, false for counter-clockwise
       * -- you could also say stepper.stepCW(); or stepper.stepCCW();
       */
       // now let's get the current step position of motor
       int nStep = stepper.getStep();
       // and if it's divisible by 64...
       if (nStep%64==0){ 
          // let's print the position to the console
          Serial.print("current step position: "); Serial.print(nStep);
          Serial.println();
         
          }// end if
        }//end for close
  }// end if button
}// end loop
