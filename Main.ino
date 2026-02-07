#include <Servo.h>
#include <string.h>
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




 int time = 0;
void setup() {
 Serial.begin(9600);
 pinMode(TRIG, OUTPUT);
 pinMode(ECHO, INPUT);
 Serial.println("Starting Program in 3 seconds");
 delay(3000);//3 second delay

}


void loop() {


}


/*
 * Uses Ultrasonic sensor to measure distance.
 * 
 * returns an int value representing the distance of an object infront of the sensor in CM. 
 */
float measureDistance()
{
  //Making sure trigger is disabled to avoid echos.
    float sum = 0;
  const int samples = 5;
  for (int i = 0; i < samples; i++) {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(20);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    long duration = pulseIn(ECHO, HIGH, 25000);
    if (duration > 0) sum += (duration * 0.0343) / 2;
    delay(10);
  }
  return sum / samples;
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
void spinRight(int speed){
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, LOW);
  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, speed);
  analogWrite(PIN_Motor_PWMB, speed);
}

/*
 * Function turns the robot car to the right. Spins right left wheel backward, right wheels forward.
 */
void spinLeft(int speed){
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, speed);
  analogWrite(PIN_Motor_PWMB, speed);
}

void turnLeft(int speed){
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, speed);
  analogWrite(PIN_Motor_PWMB, 0);
}

void turnRight(int speed){
    digitalWrite(PIN_Motor_STBY, HIGH);
    digitalWrite(PIN_Motor_AIN_1, HIGH);
    digitalWrite(PIN_Motor_BIN_1, HIGH);
    analogWrite(PIN_Motor_PWMA, 0);
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