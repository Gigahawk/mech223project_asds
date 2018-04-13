#include <SPI.h>
#include <stdlib.h>

#define STATUS_LED 5
#define WARNING_LED 7

#define CUTOFF 3.1
#define SIGNAL 3.05

char buff[10];


void setup() {
//  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(WARNING_LED, OUTPUT);
}

void loop() {

  // read normal Arduino value

  int in0 = analogRead(A0);
  float val0 = in0 * 5.0 / 1024.0;

  // read correct supply voltage

  float supply = readVcc() / 1000.0;
  float val0Corrected = supply / 5 * val0;

  int brightness = map(val0Corrected*1000,CUTOFF*1000,supply*1000,0,255);
  brightness = brightness < 0 ? 0 : brightness;
  
  analogWrite(STATUS_LED,brightness);

  if(val0Corrected < SIGNAL){
    digitalWrite(WARNING_LED,HIGH);
//    Serial.println("Writing WARNING");
//    delay(1000);
  } else {
    digitalWrite(WARNING_LED,LOW);
  }
//
//  Serial.print("in0: ");
//  Serial.print(in0);
//  Serial.print(", val0: ");
//  Serial.print(val0);
//  Serial.print(", supply: ");
//  Serial.print(supply);
//  Serial.print(", corrected: ");
//  Serial.print(val0Corrected);
//  Serial.print(", brightness: ");
//  Serial.println(brightness);
}


long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Calculate Vcc (in mV); 1126400 = 1.1*1024*1000
  return result;
}
