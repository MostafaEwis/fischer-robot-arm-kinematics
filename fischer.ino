#include <Servo.h>
#include "./Inverse_kinematics/arm.cpp"
#include "./Inverse_kinematics/link.cpp"
#include "./Inverse_kinematics/point.cpp"

Arm fischer;

Servo* servos[5];

void setup() {
  Serial.begin(9600);
  fischer.addLink(0, 0, 12, 90);
  fischer.addLink(0, 0, 12, 90);
  fischer.addLink(0, 0, 12, 90);
	servos[0] = new Servo();
	servos[1] = new Servo();
	servos[2] = new Servo();
	servos[0]->attach(3);
	servos[1]->attach(5);
	servos[2]->attach(6);
}
Point tar(20, 20, 0);
void loop() {
	fischer.calculateAngles(tar);			
	for(int i = 0; i < fischer.linksCount; i++){
		servos[i]->write(map(fischer.getAngles()[i], -M_PI / 2, M_PI / 2, 0.0f, 180.0f)); 
    Serial.print(i);
    Serial.print(", ");
    Serial.println(map(fischer.getAngles()[i], -M_PI / 2, M_PI / 2, 0.0, 180.0));    
  }
  delay(1000);
}
