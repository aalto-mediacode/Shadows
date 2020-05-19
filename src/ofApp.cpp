
#include "ofApp.h"
using namespace ofxCv;
using namespace cv;
//--------------------------------------------------------------
void ofApp::setup(){
    
    kinect.open();
    ofxKinectV2::Settings ksettings;
    ksettings.enableRGB = true;
    ksettings.enableIR = true;
    ksettings.enableDepth = true;
    ksettings.enableRGBRegistration = true;
    ksettings.enableDepthRegistration = true;
    ksettings.config.MinDepth = 0.5;
    ksettings.config.MaxDepth = 8.0;
    
    depth.allocate(512,424, OF_PIXELS_RGB);
    fbo.allocate(512,424,GL_RGBA);
    
    fbo.begin();
    ofClear(0,0,0,0);
    fbo.end();
    
    
    gui.setup();
    gui.add(threshold.set("Threshold", 28, 0, 255));
    gui.add(min.set("min",1350, 0,10000));
    gui.add(max.set("max", 100000,100,100000));
    gui.add(nearThreshold.set("nearThreshold",230, 0,1000));
    gui.add(farThreshold.set("farThreshold", 70,0,1000));
    
    learn=true;
    
    
    //setup for particle system
    ofSetCircleResolution(100);
    ofBackground(255);
    ofSetBackgroundAuto(false);
    
    //set up the particle
    for(int i=0; i<10000; i++){
        Particle newParticle;
        newParticle.setup();
        myParticle.push_back(newParticle);
    }
    
    cols = glm::floor(ofGetWidth()/scale);
    rows = glm::floor(ofGetHeight()/scale);
    flowfield.resize(cols*rows); //set size of flowfield
    
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    
    if(kinect.isFrameNew()){
        contourFinder.setMinArea(min);
        contourFinder.setMaxArea(max);
        contourFinder.setThreshold(threshold);
        
        
        depth=kinect.getDepthPixels();
        depthTexture.loadData(kinect.getDepthPixels());
        
        
        //        int numPixels = depth.size();
        //            for(int i = 0; i < numPixels; i++) {
        //                if(depth[i] < nearThreshold && depth[i] > farThreshold) {
        //                    depth[i] = 255;
        //                } else {
        //                    depth[i] = 0;
        //                }
        //            }
        
        
        // imitate() will set up previous and diff
        // so they have the same size and type as depth image
        imitate(previous, depth);
        imitate(diff, depth);
        
        
        if(learn){
            // like ofSetPixels, but more concise and cross-toolkit
            copy(depth, previous);
            learn=false;
        }
        
        
        // take the absolute difference of prev and depth and save it inside diff
        absdiff(depth, previous, diff);
        diff.update();
        
        contourFinder.findContours(diff);
        
        
        
        //Particle system
        //update the particle
        for(int i = 0; i<myParticle.size(); i++){
            myParticle[i].follow(flowfield,scale,cols);
            myParticle[i].update();
            myParticle[i].edge();
        }
    }
    
    
    fbo.begin();
    ofClear(0,0,0,0);
    int n = contourFinder.size();
    for(int i = 0; i < n; i++) {
        // get contour, label, center point, and age of contour
        vector<cv::Point> points = contourFinder.getContour(i);
        
        //draw contour
        ofBeginShape();
        for (int j=0; j<points.size(); j++) {
            ofVertex(points[j].x, points[j].y);
        }
        ofEndShape();
        
    }
    
    fbo.end();
}


//--------------------------------------------------------------
void ofApp::draw(){
    //Particle system
    float time=ofGetElapsedTimef();
    float yoff=0;
    for(int y=0; y<rows;y++){
        float xoff=0;
        for(int x=0;x<cols;x++){
            int index = x+y*cols;
            float angle=ofNoise(xoff,yoff,time)*360; //set angle corresponding to Perlin Noise
            ofVec2f v(0,1); //create a vector
            v.rotate(angle); // set angle of vector
            v.scale(0.4);
            flowfield[index]=v;
            xoff+=inc;
            
        }
        yoff+=inc;
        
    }
    
    //Draw the particle system
    for(int i = 0; i<myParticle.size(); i++){
        ofSetColor(234,197,206,10);
        myParticle[i].draw();
    }
    
    
    
    ofSetColor(169,160,152,50);
    //ofSetColor(255,255);
    ofFill();
    fbo.draw(0,0,ofGetWidth(),ofGetHeight());
    
    // gui.draw();
}

void ofApp::exit(){
    kinect.close();
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
