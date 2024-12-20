//
// Created by Joo on 12/12/2024.
//
#include "point.h"
#include "link.h"

Link::Link(float _x, float _y, float _len, float _theta){
    Point base(_x, _y, 0);
    Point head(_len * cos(_theta), _len * sin(_theta), 0);
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

