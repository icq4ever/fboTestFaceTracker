#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	
	ofFbo fbo;
	ofPixels pix;
	ofImage camImg;
	ofImage copiedImg;
	
	ofxFaceTracker tracker;
	
	int camWidth;
	int camHeight;
};
