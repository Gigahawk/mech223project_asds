#ifndef MOTOR_H
#define MOTOR_H

struct Motor_Struct ;

typedef struct Motor_Struct
{
  int in1;
  int in2;
  int d1;
  int d2;
  int fb;

  Motor_Struct(int _in1, int _in2, int _d1, int _d2, int _fb) : 
  in1(_in1), in2(_in2), d1(_d1), d2(_d2), fb(_fb)
  {
    
  }
} Motor;

#endif //MOTOR_H

