/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll & Yaw Gyroscope Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>
#include <avr/io.h>
#include <avr/interrupt.h>

MPU6050 mpu;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
volatile float yaw = 0;
volatile long counter = 0;

void setup() 
{
  Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(1);
    // инициализация Timer1
  cli();  // отключить глобальные прерывания
  TCCR3A = 0;   // установить регистры в 0
  TCCR3B = 0;

  OCR3A = 6240; // установка регистра совпадения

  TCCR3B |= (1 << WGM12);  // включить CTC режим 
// Установить биты на коэффициент деления 1024
  TCCR3B |= (1 << CS12);

  TIMSK3 |= (1 << OCIE1A);  // включить прерывание по совпадению таймера 
  sei(); // включить глобальные прерывания
}

void loop()
{
  Serial.println(yaw);
  delay(1000);
}

ISR(TIMER3_COMPA_vect){
  Vector normGyro = mpu.readNormalizeGyro();
  yaw += 6 * 0.01;

}
