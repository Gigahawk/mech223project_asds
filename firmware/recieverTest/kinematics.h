#ifndef KINEMATICS_H
#define KINEMATICS_H

// I don't think these are used right now
//#define MOTOR_MAX_VAL 1000
//#define TOTAL_MAX_VAL 1600
//#define MAX_ACCEL 1


#define MIN_APPROACH_RATE 10 //Lower this to 1 or 0 if the escs brown out
 

#include <math.h>
#include <Arduino.h>

class Kinematics
{      
  public:
    
    Kinematics(int min, int max, double ratio);

    void updateState(int x, int y, int thrust);

    void getState(int &s1, int &s2);

    void printState();

  private:
    
    int m_x,m_y,m_thrust;
    double m_ratio;
    int m_boost;
    int m_min,m_max,m_mid;
    int m_speed[2];
    int m_speed_target[2];

    void Kinematics::updateMot();
        
};
#endif //KINEMATICS_H
