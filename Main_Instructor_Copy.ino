#include <Servo.h>
#include <IRremote.hpp>


//Motor Pin definitions. A = Right, B = Left
#define PIN_Motor_PWMA 5 //right motor PWM
#define PIN_Motor_PWMB 6 //left Motor PWM
#define PIN_Motor_BIN_1 8 //Write Motor Speed
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3

//Line tracker pins
#define PIN_ITR20001_L A2
#define PIN_ITR20001_M A1
#define PIN_ITR20001_R A0

//Ultrasonic PIN definitions
#define ECHO 12
#define TRIG 13

//Servo motor pin
#define ULTRA_Serv 10 //servo motor for ultra sensor.

#define IR_RECEIVE_PIN 9


decode_results results;
boolean running = false;
void setup() {
  LineTrackerSetup();
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {

  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
      IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
      if(running){
        driveStop();
        running = false;
      }else{
        running = true;
      }
      IrReceiver.resume(); // Enable receiving of the next value
  }
  if(running){
    combat();
  }
    
}

void combat(){
  if(measureDistance()<62){
    driveForward(255);
  }else{
    driveLeft(100);
  }

}


/*
 * Uses Ultrasonic sensor to measure distance.
 * 
 * returns an int value representing the distance of an object infront of the sensor in CM. 
 */
int measureDistance()
{
  //Making sure trigger is disabled to avoid echos.
  digitalWrite(TRIG,LOW);
  delayMicroseconds(20); //waiting for echos to clear

  //sending 10 microsecond pulse.
  digitalWrite(TRIG, HIGH); 
  delayMicroseconds(10); 

  //disabling trigger
  digitalWrite(TRIG, LOW); 
  delayMicroseconds(2);
  
  //calculating distance using speed of sound. Divide by 2 because sensor measures time of wave there and back
  int distance = (pulseIn(ECHO,HIGH)*0.034)/2;
 
  return distance;
}

/*
 * Sets Motors to drive foward
 */
void driveForward(int speed)
{
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, speed);
  analogWrite(PIN_Motor_PWMB, speed);
}

/*
 * Sets motors to drive in reverse.
 */
void driveReverse(int speed){
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, LOW);
  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, speed);
  analogWrite(PIN_Motor_PWMB, speed);
}


/*
 * Function turns the robot car to the right. Spins right left wheels forward, right wheels backward.
 */
void driveRight(int speed){
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, LOW);
  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, speed);
  analogWrite(PIN_Motor_PWMB, speed);
}

/*
 * Function turns the robot car to the right. Spins right left wheel backward, right wheels forward.
 */
void driveLeft(int speed){
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, speed);
  analogWrite(PIN_Motor_PWMB, speed);
}

/*
 * Stops motors from turning
 */
void driveStop(){
  digitalWrite(PIN_Motor_STBY, LOW);
  analogWrite(PIN_Motor_PWMA, 0);
  analogWrite(PIN_Motor_PWMB, 0);
}

float LineRight(){
  return analogRead(PIN_ITR20001_R);
}

float LineMiddle(){
  return analogRead(PIN_ITR20001_M);
}
float LineLeft(){
  return analogRead(PIN_ITR20001_L);
}


void LineTrackerSetup(){
  pinMode(PIN_ITR20001_R, INPUT);
  pinMode(PIN_ITR20001_M, INPUT);
  pinMode(PIN_ITR20001_L, INPUT);
}