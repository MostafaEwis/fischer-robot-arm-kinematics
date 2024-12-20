#include <Servo.h>
#include "fischer/arm.h"
#include "fischer/point.h"
#include "fischer/link.h"

Arm fischer();
Servo* servos[5];
void setup() {
 	Serial.begin(9600);
	fischer.addLink(new Link(0, 0, 12, 90));
	servos[0] = new Servo().attach(3);
	servos[0] = new Servo().attach(5);
	servos[0] = new Servo().attach(6);
}
void loop() {
	fischer.calculateAngles(new Point(20, 20));			
	for(int i = 0; i < fischer.linksCount; i++)
		servos[i].write(map(fischer.getAngels()[i], -M_PI / 2, M_PI / 2, 0, 180)); 

}
