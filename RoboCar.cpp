
//Motor Pin definitions. A = Right, B = Left
#define PIN_Motor_PWMA 5 //right motor PWM
#define PIN_Motor_PWMB 6 //left Motor PWM
#define PIN_Motor_BIN_1 8 //Write Motor Speed
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3

MeasureDistance::RoboCar(){
    digitalWrite(TRIG,LOW); //set Trigger to low
    delayMicroseconds(20); //delaying to ensure trig is low.
    digitalWrite(TRIG, HIGH); //Set to high
    delayMicroseconds(10); // 10 send 10-microsecond oulse.
    digitalWrite(TRIG, LOW); //set to low.
    delayMicroseconds(2);

    //calculating distance using speed of sound. Divide by 2 because sensor measures time of wave there and back
    return (pulseIn(ECHO,HIGH)*0.034)/2; 

}