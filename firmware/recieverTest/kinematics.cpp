#include "kinematics.h"

Kinematics::Kinematics(int min, int max, double ratio) : 
m_min(min), m_max(max), m_ratio(ratio)
{
  m_mid = (min + max)/2;
  m_speed[0] = 0;
  m_speed_target[0];
  m_boost = m_max/m_ratio;
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
  m_speed_target[0] = mult*(m_y + m_x);
  m_speed_target[1] = mult*(m_y - m_x);

  // Set approach rate
  int diff0 = abs(m_speed_target[0] - m_speed[0]);
  int diff1 = abs(m_speed_target[1] - m_speed[1]);

  double approach0 = constrain(abs(m_boost/diff0), MIN_APPROACH_RATE,1000);
  double approach1 = constrain(abs(m_boost/diff1), MIN_APPROACH_RATE,1000);

  // Scale speeds based on thrust
  mult = m_thrust/(double)m_max;
  
  for(int i = 0; i < 2; i++){
    if(abs(m_speed_target[i] - m_speed[i]) < approach0){
      m_speed[i] = m_speed_target[i];
    } else if(m_speed_target[i] > m_speed[i] && m_speed[i] >= 0){
      m_speed[i] += approach0;
    } else if(m_speed_target[i] > m_speed[i] && m_speed[i] < 0){
      m_speed[i] = m_speed_target[i];
    } else if(m_speed_target[i] < m_speed[i] && m_speed[i] <= 0){
      m_speed[i] -= approach0;
    } else if(m_speed_target[i] < m_speed[i] && m_speed[i] > 0){
      m_speed[i] = m_speed_target[i];
    }

    m_speed[i] *= mult;
  }

}

void Kinematics::getState(int &s1, int &s2){
  s1 = m_speed[0];
  s2 = m_speed[1];
}

void Kinematics::printState(){
  Serial.print("x: ");
  Serial.print(m_x);
  Serial.print(" y: ");
  Serial.print(m_y);
  Serial.print(" t1: ");
  Serial.print(m_speed_target[0]);
  Serial.print(" t2: ");
  Serial.print(m_speed_target[1]);
  Serial.print(" s1: ");
  Serial.print(m_speed[0]);
  Serial.print(" s2: ");
  Serial.print(m_speed[1]);
  
  Serial.println();
}

