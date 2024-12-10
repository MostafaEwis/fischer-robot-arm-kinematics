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
	
	void setHead(){
		head.x = len * cos(theta) + base.x;
		head.y = len * sin(theta) + base.y;
	}
	void setBase(float x, float y){
		base.x = x;
		base.y = y;
	}
	void setHead(float x, float y){
		head.x = x;
		head.y = y;
	}
	void follow(float x, float y){
		float dy = y - base.y;
		float dx = x - base.x;
		theta = atan2(dy, dx);
		setHead(x, y);
		setBase(head.x - len * cos(theta), head.y - len * sin(theta));
	}
	void backTo(float x, float y){
		float dx = base.x - x;
		float dy = base.y - y;
		setBase(x, y);
		setHead(head.x - dx, head.y - dy);
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
    links[0] -> backTo(0, 0);
    for(int i = 1; i < arrSize; i++){
      links[i] -> backTo(links[i - 1] -> head.x, links[i - 1] -> head.y);
    }
    for(int i = 0; i < arrSize; i++){
      Serial.println(links[i] -> theta);
    }
    sr1.write(links[0] -> theta * ( 180 / M_PI));
    changed = false;
  }
  
}
