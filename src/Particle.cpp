#include "Particle.hpp"

void Particle::setup(){
    posV=ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));//position vector
    velV=ofVec2f(0,0); //Velocity vector
    accelV=ofVec2f(0,0); //acceleration vector
    maxSpeed=3;
    
    //set initial value of prePosV
    prevPosV.x = posV.x;
    prevPosV.y = posV.y;

}

void Particle::update(){
        velV+=accelV;
        velV.limit(maxSpeed);
        posV+=velV;
        accelV=ofVec2f(0,0); //reset acceleration to 0
}

void Particle::draw(){
   // ofSetColor(20,10);
    ofSetLineWidth(1);
    ofDrawLine(posV,prevPosV);
    updatePrev();
}

void Particle::updatePrev(){
    prevPosV.x = posV.x;
    prevPosV.y = posV.y;

}

void Particle::edge(){
    if (posV.x>ofGetWidth() ) {
         posV.x = 0;
         updatePrev();
       }
       if (posV.x < 0) {
           posV.x = ofGetWidth();
           updatePrev();
       }
       if (posV.y>ofGetHeight()) {
         posV.y = 0;
         updatePrev();
       }
       if (posV.y < 0) {
        posV.y = ofGetHeight();
         updatePrev();
       }
}

//assign particle to a grid and apply the force inside that grid
void Particle::follow(vector<ofVec2f> vectors, float scale, float cols){
    float x = glm::floor(posV.x/scale);
    float y = glm::floor(posV.y/scale);
    float index = x+y*cols;
    accelV+=vectors[index];
}
