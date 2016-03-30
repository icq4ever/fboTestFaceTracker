#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	
	camWidth = 1280;
	camHeight = 800;
	cam.initGrabber(camWidth, camHeight);
	tracker.setup();
	
	camImg.allocate(camWidth, camHeight, OF_IMAGE_COLOR);			// ofImage camImg    - full size (for testing)
	copiedImg.allocate(camWidth/2, camHeight/2, OF_IMAGE_COLOR);	// ofImage copiedImg - half size
	fbo.allocate(camWidth/2, camHeight/2);							// ofFbo fbo         - half size
}

void ofApp::update() {
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	cam.update();
	if(cam.isFrameNew()) {
		camImg = cam.getPixels();					// dump cam -> camImg
		
		// fill FBO
		fbo.begin();
		cam.draw(0,	0, camWidth/2, camHeight/2);	// draw half size 
		fbo.end();
		
		fbo.readToPixels(pix);
		copiedImg.setFromPixels(pix);
		copiedImg.update();					// need to this ??
		
//		tracker.update(toCv(cam));			// tracking with ofVideoGrabber.. work.
//		tracker.update(toCv(camImg));		// tracking with ofImage..  work.
		tracker.update(toCv(copiedImg));	// OpenCV Error: Assertion failed (ssize.area() > 0) in resize,
	}
}

void ofApp::draw() {
    ofSetColor(255);
	cam.draw(0, 0);
	ofSetLineWidth(2);
	tracker.draw();
    ofPolyline noseBase = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
    ofSetColor(ofColor::red);
    noseBase.draw();
    ofDrawCircle(noseBase.getCentroid2D(), 8 * tracker.getScale());
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}
