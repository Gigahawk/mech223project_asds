#include "kinematics.h"

Kinematics::Kinematics(int min, int max, double ratio) : 
m_min(min), m_max(max), m_ratio(ratio)
{
  m_mid = (min + max)/2;
  m_mot[0] = 0;
  m_mot_curr[0];
  m_boost = m_max/m_ratio;
//  m_mot0.attach(mot0pin);
}

void Kinematics::attach(int mot0, int mot1){
  m_mot0.attach(mot0);
  m_mot1.attach(mot1);
}

void Kinematics::updateState(int x, int y, int thrust)
{
  double theta, mult;

  m_thrust = thrust;
  m_x = x - m_mid;
  m_y = y - m_mid;
  m_x = abs(m_x) < 100 ? 0 : m_x;
  m_y = abs(m_y) < 100 ? 0 : m_y;

  theta = (abs(m_x) < 100 && abs(m_y) < 100)? 0 : abs(atan(m_y/(double)m_x));
  mult = map(sin(2*theta)*1000.0,0,1000,1000,1/m_ratio*1000)/1000.0;
//  Serial.println(mult);
  m_mot[0] = mult*(m_y + m_x);
  m_mot[1] = mult*(m_y - m_x);
  
//  constrain(map(m_x - m_y,-500,500,160,30),33,155);
//  Serial.println(m_mot[0]);
//  constrain(map(m_x + m_y,-500,500,160,30),33,155); // Flip motor wires i guess

  updateMot();
//  m_mot0.write(map(m_mot[0],-1666,1666,33,155));
//  m_mot1.write(map(m_mot[1],-1666,1666,33,155));
}

void Kinematics::updateMot()
{
  int mot0, mot1;
  int diff0 = abs(m_mot[0] - m_mot_curr[0]);
  int diff1 = abs(m_mot[1] - m_mot_curr[1]);

  double approach0 = abs(m_boost/diff0);
  double approach1 = abs(m_boost/diff1);
//  Serial.println(approach0);

  if(abs(m_mot[0] - m_mot_curr[0]) < approach0){
    m_mot_curr[0] = m_mot[0];
  } else if(m_mot[0] > m_mot_curr[0] && m_mot_curr[0] >= 0){
    m_mot_curr[0] += approach0;
  } else if(m_mot[0] > m_mot_curr[0] && m_mot_curr[0] < 0){
    m_mot_curr[0] = m_mot[0];
  } else if(m_mot[0] < m_mot_curr[0] && m_mot_curr[0] <= 0){
    m_mot_curr[0] -= approach0;
  } else {
    m_mot_curr[0] = m_mot[0];
  }

  if(abs(m_mot[1] - m_mot_curr[1]) < approach1){
    m_mot_curr[1] = m_mot[1];
  } else if(m_mot[1] > m_mot_curr[1] && m_mot_curr[1] >= 0){
    m_mot_curr[1] += approach1;
  } else if(m_mot[1] > m_mot_curr[1] && m_mot_curr[1] < 0){
    m_mot_curr[1] = m_mot[1];
  } else if(m_mot[1] < m_mot_curr[1] && m_mot_curr[1] <= 0){
    m_mot_curr[1] -= approach1;
  } else {
    m_mot_curr[1] = m_mot[1];
  }
  double mult = m_thrust/(double)m_max;
  
  m_mot0.write(map(m_mot_curr[0]*mult,-m_boost,m_boost,33,155));
  m_mot1.write(map(m_mot_curr[1]*mult,-m_boost,m_boost,33,155));
  Serial.print(m_mot[0]);
  Serial.print("\t");
  Serial.print(m_mot_curr[0]);
  Serial.print("\t");
  Serial.print(approach0);
  Serial.println();
}

void Kinematics::printState(){
  Serial.print("x: ");
  Serial.print(m_x);
  Serial.print(" y: ");
  Serial.print(m_y);
  Serial.print(" mot0: ");
  Serial.print(m_mot[0]);
  Serial.print(" mot1: ");
  Serial.print(m_mot[1]);
  Serial.print(" cmot0: ");
  Serial.print(m_mot_curr[0]);
  Serial.print(" cmot1: ");
  Serial.print(m_mot_curr[1]);
  
  Serial.println();
}

