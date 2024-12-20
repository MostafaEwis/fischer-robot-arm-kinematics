#include "arm.h"
#include "link.h"
#include "point.h"
void Arm::addLink(float x_, float y_, float len, float theta){
    if(linksCount < 10){
        links[linksCount] = new Link(x_, y_, len, theta);
        linksCount++;
    }
}

float Arm::calculateAngles(Point target){
    // first calculate the rotation
//    float theta1;
//    if(target.x > 0){
//        theta1 = atan(target.y/target.x);
//        theta1 = theta1 * 180/M_PI;
//        theta1 = map(theta1, -90, 90, 0, 180);
//
//    }else if(target.x < 0){
//        theta1 = atan(target.y/target.x);
//        theta1 = theta1 * 180/M_PI;
//        theta1 = map(theta1, -90, 90, 0, 180) + 180;
//    }else{
//        theta1 = 90;
//    }

    links[linksCount] -> follow(target.x, target.y);
    for(int i = linksCount - 2; i >= 0; i--){
        links[i] -> follow(links[i + 1] -> base.x, links[i + 1] -> base.y);
    }
    links[0] -> backTo(0, 0);
    for(int i = 1; i < linksCount ; i++){
        links[i] -> backTo(links[i - 1] -> head.x, links[i - 1] -> head.y);
    }
    for(int i = 0; i < linksCount; i++){
        thetas[i] = links[i] -> theta;
    }
}

float* Arm::getAngles(){
	return thetas;
}

