let links = [];
class Link {
	constructor(x, y, len, theta){
		this.base = {x, y};
		this.head = {x: len * cos(x), y: len * sin(y)}; 
		this.len = len; 
		this.theta = theta;
	}
	setHead(x = null, y = null){
		this.head.x = x || this.len * cos(this.theta) + this.base.x;
		this.head.y = y || this.len * sin(this.theta) + this.base.y;
	}
	setBase(x, y){
		this.base.x = x;
		this.base.y = y;
	}
	follow(x, y){
		let dy = y - this.base.y;
		let dx = x - this.base.x;
		this.theta = atan2(dy, dx);
		this.setHead(x, y);
		this.setBase(this.head.x - this.len * cos(this.theta), this.head.y - this.len * sin(this.theta));
	
	}
	backTo(x, y){
		let dx = this.base.x - x;
		let dy = this.base.y - y;
		this.setBase(x, y);
		this.setHead(this.head.x - dx, this.head.y - dy);
	}
	draw(){
		stroke("purple")
		strokeWeight(2)
		line(this.base.x, this.base.y, this.head.x, this.head.y);
		strokeWeight(10)
		stroke("green")
		point(this.head.x, this.head.y)
		strokeWeight(6)
		stroke("blue")
		point(this.base.x, this.base.y);
	}


}
let workSpaceRadius = 0;
function setup() {
	createCanvas(700, 700);
	angleMode(DEGREES);
	for(let i = 0; i < 10; i++)
		links.push(new Link(width / 2, height, 30, 180 + 90 +   i * 5))
	for(link of links) workSpaceRadius += link.len;	
}

let p = {x: 0, y: 0};
function updatePoint(x, y){
	p.x = x;
	p.y = y;
}
function draw() {
	background("pink");
	stroke("blue");
	line(0, 0, 100 * cos(270), 100 * sin(270));
	for(let i = 180; i < 360; i++)
		point(width / 2 + workSpaceRadius * cos(i), height + workSpaceRadius * sin(i));
	stroke("purple");
	strokeWeight(2);
	links[links.length - 1].follow(mouseX, mouseY);
	for(let i = links.length - 2; i >= 0; i--){
		links[i].follow(links[i + 1].base.x, links[i + 1].base.y);
	}
	links[0].backTo(width / 2, height);
	for(let i = 1; i < links.length; i++){
		links[i].backTo(links[i - 1].head.x, links[i - 1].head.y);
	}
	for(link of links) link.draw();
}
function mouseClicked(){
	updatePoint(mouseX, mouseY);
	console.clear();
	for(link of links) console.log(link.theta);
}




