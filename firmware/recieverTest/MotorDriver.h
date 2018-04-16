#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
#include "Motor.h"
#include <Arduino.h>
#include <math.h>

class MotorDriver
{
  public:
    MotorDriver(Motor *m1, Motor *m2, int en, int slew, int max);

    void updateState(int s1, int s2);

    void printState();

    void enable();
    void disable();

    void attach();
    
//    int* getFb();

  private:
    Motor * m_mot[2];

    int m_en, m_slew;
    int m_max;
    int m_throttle[2];
    
    void updateMot();
};

#endif //MOTORDRIVER_H

