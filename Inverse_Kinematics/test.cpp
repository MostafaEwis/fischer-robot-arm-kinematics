class Point{
public:
  float x, y, z;
  Point() : x(0), y(0), z(0) {}
  Point(float x, float y, float z) : x(x), y(y), z(z) {}
  set(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
  }
};
class Link{
public:

  float theta, len;
  Point base, head;

  Link(float _x, float _y, float _len, float _theta){
    Point base(_x, _y, 0);
    Point head(_len * cos(_theta), _len * sin(_theta), 0);
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

};
class Arm{
public:
  int linksCount = 0;
  Link* links[5];
  float thetas[5];
  void addLink(float x_, float y_, float len, float theta){
    if(linksCount < 10){
        links[linksCount] = new Link(x_, y_, len, theta);
        linksCount++;
    }
  }
  float calculateAngles(Point target){
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
  float* getAngles(){

	return thetas;
  }
};
