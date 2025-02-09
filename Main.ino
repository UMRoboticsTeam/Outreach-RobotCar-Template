#include <Servo.h>

//Motor Pin definitions. A = Right, B = Left
#define PIN_Motor_PWMA 5 //right motor PWM
#define PIN_Motor_PWMB 6 //left Motor PWM
#define PIN_Motor_BIN_1 8 //Write Motor Speed
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3

//Ultrasonic PIN definitions
#define ECHO 12
#define TRIG 13

//Servo motor pin
#define ULTRA_Serv 10 //servo motor for ultra sensor.

//Pin that receives IR Remote data.
#define IR_RECEIVE_PIN 9

void loop() {


  if (IrReceiver.decode()) {
      if(running){
        driveStop();
        running = false;
      }else{
        combat();
        running = true;
      }
      IrReceiver.resume(); // Enable receiving of the next value
  }
}

void combat(){
  driveForward(255);
}

/*
 * Uses Ultrasonic sensor to measure distance.
 * 
 * returns an int value representing the distance of an object infront of the sensor in CM. 
 */
int measureDistance()
{
  digitalWrite(TRIG,LOW); //set Trigger to low
  delayMicroseconds(20); //delaying to ensure trig is low.
  digitalWrite(TRIG, HIGH); //Set to high
  delayMicroseconds(10); // 10 send 10-microsecond oulse.
  digitalWrite(TRIG, LOW); //set to low.
  delayMicroseconds(2);
  
  //calculating distance using speed of sound. Divide by 2 because sensor measures time of wave there and back
  return (pulseIn(ECHO,HIGH)*0.034)/2; 
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
