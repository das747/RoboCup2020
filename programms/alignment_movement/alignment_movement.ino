#include <Wire.h>
#include <MPU6050.h>


const float time_step = 0.1, gyro_treshold = 0.5;
const byte latch_pin = 8, clock_pin = 9, data_pin = 7; 
const byte MOTOR_ENABLES[] = {13, 12, 10, 11}; 
const int MOTOR_ANGLES[] = {30, 330, 210, 150};
byte motors_state = 0;
double angle = 0;
unsigned long timer = 0;

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  
  for(byte i=0;i<4;i++){
    pinMode(MOTOR_ENABLES[i], OUTPUT);
  }
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, LSBFIRST, motors_state);
  digitalWrite(latch_pin, HIGH);
}

void loop() {
  timer = millis();
  
  Vector gyro = mpu.readNormalizeGyro();
  if (abs(gyro.ZAxis) > gyro_treshold){
    angle += gyro.ZAxis * time_step;
  }

  set_direction(90, 250);

  delay(time_step * 1000 - (millis() - timer));
}

byte set_motor(byte motor, long pwm){
  pwm = constrain(pwm, -255, 255);
  bitWrite(motors_state, motor * 2, pwm > 0);
  bitWrite(motors_state, motor * 2 + 1, pwm < 0); 
//  Serial.println(motors_state, BIN);
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, LSBFIRST, motors_state);
  digitalWrite(latch_pin, HIGH);
  analogWrite(MOTOR_ENABLES[motor], abs(pwm));
}


bool set_direction(int dir, long pwm){
  for(byte i=0; i<4; i++){
    set_motor(i, pwm * cos(float(dir - MOTOR_ANGLES[i]) / 180 * PI) + (-angle * 10 * (abs(angle) > 2)));
  }
}
