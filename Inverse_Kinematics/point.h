/*
  A custom library made by mostafa Ewis to calculate the inverse kinematics 
  for our robotic arm which is called "Bobby Fischer" or simply "Fischer" that plays chess

  the arm has 5 degrees of freedom 
*/


#ifndef point_h
#define point_h


class Point{
public:
  Point();
  Point(float x, float y, float z);
  set(float x, float y, float z);
};
#endif
