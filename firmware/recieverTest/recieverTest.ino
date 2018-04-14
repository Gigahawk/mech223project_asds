// Don't touch these
#define C1MIN 1100
#define C1MAX 1984
#define C2MIN 1088
#define C2MAX 1968
#define C3MIN 1092
#define C3MAX 1964
#define C4MIN 1100
#define C4MAX 1988

#define REMOTEMAXVAL 1050*2
#define MAXVAL 1000*2

#define BMS_PIN A0
#define STATUS_LED 3
#define WARNING_LED 4

// If the escs still brown out try raising the backoff voltage or changing the increment
#define THROTTLE_INCREMENT 0.1
#define BACKOFF_VOLTAGE_LOW 3.5
#define BACKOFF_VOLTAGE_HIGH 3.7


#include "kinematics.h"
#include "vref.h"

byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
unsigned long timer_channel_1, timer_channel_2, timer_channel_3, timer_channel_4, esc_timer, esc_loop_timer;
unsigned long timer_1, timer_2, timer_3, timer_4, current_time;

// 1 (RSH, pin8), 2 (RSV, pin9) , 3 (LSV pin10) , 4 (LSH, pin11)
volatile int receiver_input[4];
bool brownout;
double throttle_multiplier;

// first two arguments range of inputs, last value defines "ratio"
// of output when powering two motors vs 1
// (It's not really a ratio just twiddle the last number till it 
// doesn't brownout at full speed or smth)
Kinematics m_kinematics(0,MAXVAL,1.5);

void setup() {
  throttle_multiplier = 1;
  PCICR  |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
  PCMSK0 |= (1 << PCINT2);
  PCMSK0 |= (1 << PCINT3);
//  PCMSK0 |= (1 << PCINT4);
  Serial.begin(115200);
  pinMode(BMS_PIN, INPUT);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(WARNING_LED, OUTPUT);
  m_kinematics.attach(5,6);
  brownout = false;

}

ISR(PCINT0_vect){
  current_time = micros();
  //Channel 1
  if(PINB & B00000001){
    if(last_channel_1 == 0){
      last_channel_1 = 1;
      timer_1 = current_time;
    }
  }
  else if(last_channel_1 == 1){
    last_channel_1 = 0;
    receiver_input[0] = map(current_time - timer_1,C1MIN,C1MAX,0,REMOTEMAXVAL);
    receiver_input[0] = constrain(receiver_input[0],0,MAXVAL);
  }
  //Channel 2
  if(PINB & B00000010 ){
    if(last_channel_2 == 0){
      last_channel_2 = 1;
      timer_2 = current_time;
    }
  }
  else if(last_channel_2 == 1){
    last_channel_2 = 0;
    receiver_input[1] = map(current_time - timer_2,C2MIN,C2MAX,0,REMOTEMAXVAL);
    receiver_input[1] = constrain(receiver_input[1],0,MAXVAL);
  }
  //Channel 3
  if(PINB & B00000100 ){
    if(last_channel_3 == 0){
      last_channel_3 = 1;
      timer_3 = current_time;
    }
  }
  else if(last_channel_3 == 1){
    last_channel_3 = 0;
    receiver_input[2] = map(current_time - timer_3,C3MIN,C3MAX,0,REMOTEMAXVAL);
    receiver_input[2] = constrain(receiver_input[2],0,MAXVAL);

  }
  //Channel 4
  if(PINB & B00001000 ){
    if(last_channel_4 == 0){
      last_channel_4 = 1;
      timer_4 = current_time;
    }
  }
  else if(last_channel_4 == 1){
    last_channel_4 = 0;
    receiver_input[3] = map(current_time - timer_4,C4MIN,C4MAX,0,REMOTEMAXVAL);
    receiver_input[3] = constrain(receiver_input[3],0,MAXVAL);
  }

//  if(PINB & B00010000 ){
//    throttle_multiplier -= THROTTLE_INCREMENT*4;
//  } else {
//    throttle_multiplier += THROTTLE_INCREMENT;
//  }
//  throttle_multiplier = constrain(throttle_multiplier, 0, 1);
}

void print_signals(){
//  Serial.print("C 1:");
//  Serial.print(receiver_input[0]);
//  Serial.print(" C 2:");
//  Serial.print(receiver_input[1]);
//  Serial.print(" C 3:");
//  Serial.print(receiver_input[2]);
//  Serial.print(" C 4:");
//  Serial.print(receiver_input[3]);
  Serial.print(" t_m: ");
  Serial.print(throttle_multiplier);
  Serial.print(" V: ");
  Serial.print(betterAnalogRead(BMS_PIN));
  Serial.print(" b: ");
  Serial.print(brownout);
  Serial.println();
}

float betterAnalogRead(int pin){
  int in0 = analogRead(pin);
  float val0 = in0 * 5.0 / 1024.0;

  // read correct supply voltage

  float supply = readVcc() / 1000.0;
  float val0Corrected = supply / 5 * val0;
  return val0Corrected;
}

void checkVoltage(){
  float batteryPack = betterAnalogRead(BMS_PIN);
  int brightness = constrain(map(batteryPack*1000,BACKOFF_VOLTAGE_LOW*1000,5*1000,0,255),0,255);
  analogWrite(STATUS_LED,brightness);
  
  if(!brownout && batteryPack < BACKOFF_VOLTAGE_LOW){
    digitalWrite(WARNING_LED,HIGH);
    brownout = true;
  } else if(brownout && batteryPack > BACKOFF_VOLTAGE_HIGH){
    digitalWrite(WARNING_LED,LOW);
    brownout = false;
  }

  if(brownout){
    throttle_multiplier = constrain(throttle_multiplier - THROTTLE_INCREMENT*2,0,1);
  } else {
    throttle_multiplier = constrain(throttle_multiplier + THROTTLE_INCREMENT,0,1);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
//  delay(250);
//  print_signals();
  checkVoltage();
  m_kinematics.updateState(receiver_input[0], receiver_input[1], throttle_multiplier*receiver_input[2]);
//  m_kinematics.printState();
}
