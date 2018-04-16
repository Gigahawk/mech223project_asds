#include "ESCDriver.h"

ESCDriver::ESCDriver(int esc1, int esc2, int min, int max):
m_min(min), m_max(max)
{
  m_mot_pin[0] = esc1;
  m_mot_pin[1] = esc2;
}

void ESCDriver::attach(){
  for(int i = 0; i < 2; i++){
    m_mot[i].attach(m_mot_pin[i]);
  }
}


void ESCDriver::updateState(int s1, int s2){
  m_throttle[0] = s1;
  m_throttle[1] = s2;

  updateMot();
}

void ESCDriver::updateMot(){
  for(int i = 0; i < 2; i++){
    double throttle = map(m_throttle[i], m_min, m_max, ESC_MIN, ESC_MAX);

    m_mot[i].write(throttle);
  }
}

