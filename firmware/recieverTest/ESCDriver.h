#ifndef ESCDRIVER_H
#define ESCDRIVEr_H

// Range of ESCs
#define ESC_MIN 33 
#define ESC_MAX 155

#include <Servo.h>
#include <Arduino.h>
#include <math.h>

class ESCDriver
{
  public:
    ESCDriver(int esc1, int esc2, int min, int max);

    void updateState(int s1, int s2);

    void printState();

    void attach();
    
  private:
    int m_min,m_max;
    int m_throttle[2];
    int m_mot_pin[2];
    Servo m_mot[2];
    
    void updateMot();
};

#endif //ESCDRIVER_H

