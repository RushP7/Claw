// Code for the claw for APSC 101: uses code written by Dejan Nedelkovski (for the sonar)
// Author: Rushil Punchhi
// Additional Source(s): Dejan Nedelkovski's SONAR code
//---------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------

// APSC 101-January 2020

// Code for video Arduino 05

//

// VERSION 1

//

// Video located at:   https://www.youtube.com/watch?v=_DDtwvWsmNo

//

// This program uses an ultrasonic distance sensor (sonar)

// and shows its readings on the screen of an attached

// computer, via the Arduino Serial Monitor.

//

// This code uses sample from "Ultrasonic Sensor HC-SR04 and Arduino Tutorial"

// by Dejan Nedelkovski,

// www.HowToMechatronics.com  

// https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

//

// --------------------------------------------------------------------------------------


#define VCC_PIN 13

#define TRIGGER_PIN 12 // sonar trigger pin will be attached to Arduino pin 12

#define ECHO_PIN 11 // sonar echo pint will be attached to Arduino pin 11

#define GROUND_PIN 10 //

#define MAX_DISTANCE 200 // fmaximum distance set to 200 cm

#define CLOSE_THRESH 5 

#define LIFT_THRESH 20

#define OPEN_POS 90

#define CLOSE_POS 170

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

// defines variables

long duration;

int distance;


void CloseClaw(){

  for (pos = OPEN_POS; pos <= CLOSE_POS; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position  }     
  }
}


void OpenClaw(){

  for (pos = CLOSE_POS; pos >= OPEN_POS; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
}


void Measure(){

  digitalWrite(TRIGGER_PIN, LOW);  // Clears the trigPin

  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds

  delayMicroseconds(20);

  digitalWrite(TRIGGER_PIN, LOW);


  duration = pulseIn(ECHO_PIN, HIGH);

  distance= duration*0.034/2;  // Calculating the distance


  // if the distance measurement becomes extremely high, it is likely an error.  

  // Default to a maximum value of MAX_DISTANCE to identify this condition.

  if (distance > MAX_DISTANCE)  

    {distance = MAX_DISTANCE ;}


   

  Serial.print("Distance: ") ;  // Prints the distance on the Serial Monitor

  Serial.println(distance);
}


void setup() {

  Serial. begin(9600);  // set data transmission rate to communicate with computer

  pinMode(ECHO_PIN, INPUT) ;  

  pinMode(TRIGGER_PIN, OUTPUT) ;

  pinMode(GROUND_PIN, OUTPUT);  // tell pin 10 it is going to be an output

  pinMode(VCC_PIN, OUTPUT);  // tell pin 13 it is going to be an output

  digitalWrite(GROUND_PIN,LOW); // tell pin 10 to output LOW (OV, or ground)

  digitalWrite(VCC_PIN, HIGH) ; // tell pin 13 to output HIGH (+5V)
  
  
  myservo.attach(9);
  myservo.write(OPEN_POS);

}


void loop() {
  
 Measure();

 if(distance <= CLOSE_THRESH && distance != 0){
  
  delay(2000);
  
  CloseClaw();
  
  while(distance <= LIFT_THRESH)
    Measure();

  while(distance >= CLOSE_THRESH)
    Measure();

  OpenClaw();

  while(distance <= LIFT_THRESH)
    Measure();
 }
  

}
