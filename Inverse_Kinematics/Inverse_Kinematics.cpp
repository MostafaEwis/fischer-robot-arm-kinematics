//
// Created by Joo on 12/12/2024.
//

#include "Inverse_Kinematics.h"
#include <cmath>

// start of Point Methods
Point::Point() : x(0), y(0), z(0) {}

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

void Point::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
// end of Point Methods

// start of link methods

Link::Link(float _x, float _y, float _len, float _theta){
    Point base(_x, _y);
    Point head(_len * cos(_theta), _len * sin(_theta));
    len = _len;
    theta = _theta;
}

void Link::setHead(){
    head.x = len * cos(theta) + base.x;
    head.y = len * sin(theta) + base.y;
}
void Link::setBase(float x, float y){
    base.x = x;
    base.y = y;
}
void Link::setHead(float x, float y){
    head.x = x;
    head.y = y;
}
void Link::follow(float x, float y){
    float dy = y - base.y;
    float dx = x - base.x;
    theta = atan2(dy, dx);
    setHead(x, y);
    setBase(head.x - len * cos(theta), head.y - len * sin(theta));
}
void Link::backTo(float x, float y){
    float dx = base.x - x;
    float dy = base.y - y;
    setBase(x, y);
    setHead(head.x - dx, head.y - dy);
}

// end of link methods

// start of arm methods
arm::arm(int linkcount){
    number_of_links = linkcount;
    temp = linkcount;
}


void defineLink(float x_, float y_, float len, float theta){
    if(temp > 0){
        links[3-temp] = new link(x_,y_,len,theta);
        temp--;
    }
}

float calculateAngles(Point end_effector){

    // first calculate the rotation
    float theta1;
    if(end_effector.x > 0){
        theta1 = atan(end_effector.y/end_effector.x);
        theta1 = theta1 * 180/M_PI;
        theta1 = map(theta1, -90, 90, 0, 180);

    }else if(end_effector.x < 0){
        theta1 = atan(end_effector.y/end_effector.x);
        theta1 = theta1 * 180/M_PI;
        theta1 = map(theta1, -90, 90, 0, 180) + 180;
    }else{
        theta1 = 90;
    }

    links[number_of_links - 1] -> follow(end_effector.x, end_effector.y);
    for(int i = number_of_links - 2; i >= 0; i--){
        links[i] -> follow(links[i + 1] -> base.x, links[i + 1] -> base.y);
    }
    links[0] -> backTo(0, 0);
    for(int i = 1; i < number_of_links; i++){
        links[i] -> backTo(links[i - 1] -> head.x, links[i - 1] -> head.y);
    }
    float thetas[3];
    for(int i = 0; i < number_of_links; i++){
        thetas[i]=links[i] -> theta;
    }

}

// end of arm methods