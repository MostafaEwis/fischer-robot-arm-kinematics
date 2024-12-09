#include <Servo.h>
class Point{
public:
	Point(){
		x = 0;
		y = 0;
	}
	Point(float x, float y){
		this -> x = x;
		this -> y = y;
	}
	set(float x, float y){
		this -> x = x;
		this -> y = y;
	}
	int x = 0;
	int y = 0;

};
class Link{
public:
	Link(float _x, float _y, float _len, float _theta){
		Point base(_x, _y);
		Point head(_len * cos(_theta), _len * sin(_theta)); 
		len = _len; 
		theta = _theta;
	}
	
	void updateCords(){
		head.x = len * cos(theta) + base.x;
		head.y = len * sin(theta) + base.y;
	}
	void setBase(float x, float y){
		base.x = x;
		base.y = y;
	}
	void follow(float x, float y){
		float dy = y - base.y;
		float dx = x - base.x;
		theta = atan2(dy, dx);
		theta += M_PI;
		setBase(x, y);
		updateCords();
		swap();
	}
	void swap(){
		float tx = base.x;
		float ty = base.y;
		base.x = head.x;
		base.y = head.y;
		head.x = tx;
		head.y = ty;
	}

	float theta, len;
	Point base, head;
};
int arrSize = 3;
Link* links[3];
Servo sr1;
void setup() {
	sr1.attach(3);
 	Serial.begin(9600);
  // put your setup code here, to run once:
	for(int i = 0; i < arrSize; i++)
		links[i] = new Link(0, 0, 12, 0);

}
Point fp(20, 30);
bool changed = true;
void loop() {
  // put your main code here, to run repeatedly:
	if(changed){
    links[arrSize - 1] -> follow(fp.x, fp.y);
    for(int i = arrSize - 2; i >= 0; i--){
      links[i] -> follow(links[i + 1] -> base.x, links[i + 1] -> base.y);
    }
    links[0] -> setBase(0, 0);
    links[0] -> theta += M_PI;
    links[0] -> updateCords();
    for(int i = 1; i < arrSize; i++){
      links[i] -> setBase(links[i - 1] -> head.x, links[i - 1] -> head.y);
      links[i] -> theta += M_PI;
      links[i] -> updateCords();
    }
    for(int i = 0; i < arrSize; i++){
      Serial.println(links[i] -> theta);
    }
    sr1.write(links[0] -> theta * ( 180 / M_PI));
    changed = false;
  }
  
}
