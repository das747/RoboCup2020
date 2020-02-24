const byte latch_pin = 8, clock_pin = 9, data_pin = 7; 
const byte MOTOR_ENABLES[] = {13, 12, 10, 11};
byte motors_state = 0;

void setup() {
  for(byte i=0;i<4;i++){
    pinMode(MOTOR_ENABLES[i], OUTPUT);
  }
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  byte state = 170;
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, LSBFIRST, state);
  digitalWrite(latch_pin, HIGH);
}

void loop() {
  for(byte i=0; i<254; i++){
    analogWrite(13, i);
    delay(100);
  }
  for(byte i=254; i>0; i--){
    analogWrite(13, i);
    delay(100);
  }
}

byte set_motor(byte state, byte motor, byte pwm){
  state
  shiftOut(data_pin, clock_pin, MSBFIRST, state);
  return state;
}
