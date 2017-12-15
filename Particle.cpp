#include "Particle.h"

Particle::Particle() {
	location = ofVec3f(0.0, 0.0, 0.0);
	velocity = ofVec3f(0.0, 0.0, 0.0);
	acceleration = ofVec3f(0.0, 0.0, 0.0);
	gravity = ofVec3f(0.0, 0.0, 0.0);
	//min = ofVec3f(-ofGetWidth()/2, -ofGetHeight()/2, 0);
	min = ofVec3f(0,0, 0);
	//max = ofVec3f(ofGetWidth()/2, ofGetHeight()/2, ofGetHeight() / 2);
	max = ofVec3f(ofGetWidth(), ofGetHeight(), ofGetHeight() / 2);
}
void Particle::update() {
	this->acceleration += this->gravity;
	this->velocity += this->acceleration;
	this->velocity *= (1.0 - this->friction);
	this->location += velocity;
	this->acceleration.set(0, 0, 0);
}
void Particle::draw() {
	//ofPushMatrix();
	//ofTranslate(this->location.x, this->location.y, this->location.z);
	//ofEllipse(0, 0, mass * radius * 2, mass * radius * 2);
	ofDrawEllipse(this->location, mass * radius * 2, mass * radius * 2);
	//ofPopMatrix();
}
void Particle::addForce(ofVec3f force) {
	force /= mass;
	this->acceleration += force;
}
void Particle::attract(ofVec2f center, float _mass, float min, float max) {
	float distance = center.distance(location);
	distance = this->constrain(distance, this->min, this->max);
	float strength = G * (mass * _mass) / (distance * distance);
	ofVec3f force = center - this->location;
	force.normalize();
	force *= strength;
	this->addForce(force);	
}
void Particle::bounceOffWalls() {
	if (this->location.x > this->max.x) {
		this->location.x = this->max.x;
		this->velocity.x *= -1;
	}
	if (this->location.x < this->min.x) {
		this->location.x = this->min.x;
		this->velocity.x *= -1;
	}
	if (this->location.y > this->max.y) {
		this->location.y = this->max.y;
		this->velocity.y *= -1;
	}
	if (this->location.y < this->min.y) {
		this->location.y = this->min.y;
		this->velocity.y *= -1;
	}
	if (this->location.z > this->max.z) {
		this->location.z = this->max.z;
		this->velocity.z *= -1;
	}
	if (this->location.z < this->min.z) {
		this->location.z = this->min.z;
		this->velocity.z *= -1;
	}
}
void Particle::throughWalls() {
	if (this->location.x < this->min.x) {
		this->location.x = this->max.x;
	}
	if (this->location.y < this->min.y) {
		this->location.y = this->max.y;
	}
	if (this->location.z < this->min.z) {
		this->location.z = this->max.z;
	}
	if (this->location.x > this->max.x) {
		this->location.x = this->min.x;
	}
	if (this->location.y > this->max.y) {
		this->location.y = this->min.y;
	}
	if (this->location.z > this->max.z) {
		this->location.z = this->min.z;
	}
}
float Particle::constrain(float d, ofVec3f min, ofVec3f max) {
	float f = min.distance(max);
	if (f < d) {
		d = f;
	}
	return d;
}
void Particle::setLocation(float x, float y, float z) {
	this->location.set(x, y, z);
}
void Particle::setGravity(float x, float y, float z) {
	this->gravity.set(x, y, z);
}
void Particle::setFriction(float x) {
	this->friction = x;
}
void Particle::setRadius(float r) {
	this->radius = r;
}