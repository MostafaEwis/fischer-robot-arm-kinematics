//
// Created by Joo on 12/12/2024.
//
#include "point.h"
Point::Point() : x(0), y(0), z(0) {}

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

void Point::set(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
