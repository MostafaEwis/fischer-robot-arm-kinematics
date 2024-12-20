/*
  A custom library made by mostafa Ewis to calculate the inverse kinematics 
  for our robotic arm which is called "Bobby Fischer" or simply "Fischer" that plays chess

  the arm has 5 degrees of freedom 
*/


#ifndef link_h
#define link_h
#include "point.h"

class Link{
public:

  float theta, len;
  Point base, head;

  Link(float _x, float _y, float _len, float _theta);

  void setHead();

  void setBase(float x, float y);

  void setHead(float x, float y);

  void follow(float x, float y);

  void backTo(float x, float y);

};




#endif //link_h
