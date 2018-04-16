#include "MotorDriver.h"

MotorDriver::MotorDriver(Motor *m1, Motor *m2, int en, int slew, int max)
: m_en(en), m_slew(slew), m_max(max)
{
  m_mot[0] = m1;
  m_mot[1] = m2;
}

void MotorDriver::attach(){
  for(int i = 0; i < 2; i++){
    pinMode(m_mot[i] -> in1,OUTPUT);
    pinMode(m_mot[i] -> in2,OUTPUT);
    pinMode(m_mot[i] -> d1, OUTPUT); // Disables motor when HIGH
    pinMode(m_mot[i] -> d2, OUTPUT); // Disables motor when LOW
    pinMode(m_mot[i] -> fb, INPUT);

    // Only use d2 for PWM control
    digitalWrite(m_mot[i] -> d1,LOW);
  }
  
  pinMode(m_slew,OUTPUT);
  pinMode(m_en,  OUTPUT);
  digitalWrite(m_en, HIGH); // Always have motor driver on
}

void MotorDriver::updateState(int s1, int s2){
  m_throttle[0] = s1;
  m_throttle[1] = s2;

  updateMot();
}

void MotorDriver::enable(){
  digitalWrite(m_en,HIGH);
}

void MotorDriver::disable(){
  digitalWrite(m_en,LOW);
}

void MotorDriver::updateMot(){
  for(int i = 0; i < 2; i++){
    if(m_throttle[i] < 0){
      digitalWrite(m_mot[i] -> in1,HIGH);
      digitalWrite(m_mot[i] -> in2,LOW);
    } else {
      digitalWrite(m_mot[i] -> in1,LOW);
      digitalWrite(m_mot[i] -> in2,HIGH);
    }

    double throttle = abs(m_throttle[i])/(double)m_max * 255;
//
//    Serial.print("Writing ");
//    Serial.print((int)throttle);
//    Serial.print(" to ");
//    Serial.print(m_mot[i] -> d2);
//    Serial.println();

    analogWrite(m_mot[i] -> d2, throttle);
  }
}

void MotorDriver::printState(){
  for(int i = 0; i < 2; i++){
    Serial.print("M");
    Serial.print(i);
    
    Serial.print(" in: (");
    Serial.print(m_mot[i] -> in1);
    Serial.print(",");
    Serial.print(m_mot[i] -> in2);
    Serial.print(") ");

    Serial.print(" d: (");
    Serial.print(m_mot[i] -> d1);
    Serial.print(",");
    Serial.print(m_mot[i] -> d2);
    Serial.print(") ");

    Serial.println();
  }
}


//int* MotorDriver::getFb(int &fb[]){
//  static int fb[2];
//
//  for(int i = 0; i < 2; i++){
//    fb[i] = analogRead(m_mot[i].fb);
//  }
//}

