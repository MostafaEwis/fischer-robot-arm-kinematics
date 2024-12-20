/*
  A custom library made by mostafa Ewis to calculate the inverse kinematics 
  for our robotic arm which is called "Bobby Fischer" or simply "Fischer" that plays chess

  the arm has 5 degrees of freedom 
*/


#ifndef arm_h
#define arm_h

#include "link.h"
#include "point.h"

class Arm{
public:
  int linksCount;
  Link* links[5];
  float thetas[5];
  Arm();
  void defineLink(float x_, float y_, float len, float theta);
  float calculateAngles(Point end_effector);
  float* getAngles();
}

#endif // Inverse_Kinematics_H
