#pragma once

#include "ofMain.h"

class Particle{

    public:
        void setup();
        void update();
        void draw();
        void edge();
        void applyForce(ofVec2f forceV);
        void follow(vector<ofVec2f> vectors,float scale, float cols);
        void updatePrev();
    ofVec2f posV;
    ofVec2f velV,accelV;
    ofVec2f prevPosV;
    float maxSpeed;
    
};
