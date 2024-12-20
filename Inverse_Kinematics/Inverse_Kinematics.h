/*
  A custom library made by mostafa Ewis to calculate the inverse kinematics 
  for our robotic arm which is called "Bobby Fischer" or simply "Fischer" that plays chess

  the arm has 5 degrees of freedom 
*/


#ifndef Inverse_Kinematics_H
#define Inverse_Kinematics_H

#include <bits/stdc++.h>

class Point{
public:

  Point();
  Point(float x, float y, float z);
  set(float x, float y, float z);

}

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



class arm{
public:
  int number_of_links, temp;
  Link* links[number_of_links];

  arm(int linkcount);

  void defineLink(float x_, float y_, float len, float theta);
  float calculateAngles(Point end_effector);
}

#endif // Inverse_Kinematics_H
