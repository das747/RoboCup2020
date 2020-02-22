const byte LIGHT_PIN = A0;
const byte ADDRESS_PINS[] = {4, 6, 5, 27, 26};
int light_error[8] = {};
 
void setup() {
  Serial.begin(9600);
  for(byte i=0; i<5; i++){
    pinMode(ADDRESS_PINS[i], OUTPUT);
  }
  byte sensor = 0;
  delay(1000);
  for(int i=0; i<8; i++){
    light_error[i] = read_address(sensor * 8 + i);
  }
}



void loop() {
//  Serial.println(read_address(0));
//  byte sensor = 0;
//  for(int i=0; i<8; i++){
//    Serial.print(read_address(sensor * 8 + i) - light_error[i]);
//    Serial.print('\t');
//  }
  int result[8] = {};
  byte max_val = read_sensor(0, result);
  Serial.println((String) result[max_val] + '\t' + max_val);
  delay(100);
}

int read_address(byte address){
  for(byte i=0; i<5; i++){
    bool addr_bit = (address >> i) % 2;
//    Serial.print((String) addr_bit + '\t');
    digitalWrite(ADDRESS_PINS[i], addr_bit);
  }
  return(analogRead(LIGHT_PIN));
}

byte read_sensor(byte sensor, int * result){
  byte max_val = 0;
  for(int i=0; i<8; i++){
    result[i] = abs(read_address(sensor * 8 + i) - light_error[i]);
    if (result[max_val] < result[i]) max_val = i;
  }
  return max_val;
}
