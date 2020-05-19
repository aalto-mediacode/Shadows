#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"
#include "Particle.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxKinectV2 kinect;
    ofTexture texture;
    ofTexture depthTexture;
    
    ofxCv::ContourFinder contourFinder;
    
    ofPixels depth,previous;
    ofImage diff;
    
    ofxPanel gui;
    ofParameter<float> threshold;
    ofParameter<float> min;
    ofParameter<float> max;
    ofParameter<float> nearThreshold;;
    ofParameter<float> farThreshold;
    
    bool learn;
    ofFbo fbo;
    
    
    //Particle system
    vector <Particle> myParticle;
    vector <ofVec2f> flowfield;
    float scale=40;
    float cols, rows;
    float inc = 0.1;
    
    
};
