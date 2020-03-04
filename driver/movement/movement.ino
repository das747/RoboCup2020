const byte latch_pin = 8, clock_pin = 9, data_pin = 7; 
const byte MOTOR_ENABLES[] = {13, 12, 10, 11};
const int MOTOR_ANGLES[] = {30, 330, 210, 150};
byte motors_state = 0;

void setup() {
  Serial.begin(9600);
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
//  for(byte i=0; i<4; i++){
//    set_motor(i, 255);
//  }
  set_direction(60, 255);
//  set_motor(3, -255);
//  delay(3000);
//  set_motor(3, 255);
//  delay(3000);
//  for(int i=-255; i<256; i++){
//    set_motor(3, i);
//    delay(100);
//  }
//  for(int i=255; i>-256; i--){
//    set_motor(3, i);
//    delay(100);
//  }

}

bool set_motor(byte motor, long pwm){
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
    set_motor(i, pwm * cos(float(dir - MOTOR_ANGLES[i]) / 180 * PI));
  }
}
