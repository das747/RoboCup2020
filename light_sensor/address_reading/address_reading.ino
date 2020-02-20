const byte LIGHT_PIN = A0;
const byte ADDRESS_PINS[] = {49, 48, 5, 6, 4};
 
void setup() {
  Serial.begin(9600);
  for(byte i=0; i<5; i++){
    pinMode(ADDRESS_PINS[i], OUTPUT);
  }
 
}



void loop() {
  Serial.println(read_address(0));
//  byte sensor = 0;
//  for(int i=0; i<8; i++){
//    Serial.print(read_address(sensor * 8 + i));
//  }
//  Serial.println();
  delay(100);
}

int read_address(byte address){
  for(byte i=0; i<5; i++){
    bool addr_bit = address % byte(pow(2, 5 - i)) / pow(2, 4 - i); 
    digitalWrite(ADDRESS_PINS[i], addr_bit);
  }
  return(analogRead(LIGHT_PIN));
}
