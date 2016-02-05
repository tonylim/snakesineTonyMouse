#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	CGDisplayHideCursor(kCGDirectMainDisplay);
    //ofToggleFullscreen();
	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
    ofEnableAlphaBlending();
	ofBackground(0, 0, 0);
	
    number=0;
    
    //    piano.loadSound("EnglishSuite5.mp3");
    //    piano.play();
    
    
    //Sound input
	
	soundStream.listDevices();
	
	//if you want to set a different device id
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 256;
	
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
	for (int i=1; i<RECT_NUM;i++) {
        myRectangle[i].scl.x = 0 ;
        myRectangle[i].scl.y = 0 ;
        myRectangle[i].pos.x = ofGetWidth()/2;
        myRectangle[i].pos.y = ofGetHeight()/2;
        
    }
    
    
}

//--------------------------------------------------------------
void testApp::update(){
	
    
    //first rectangle//
    
    
    
    
    myRectangle[0].scl.x = 20+ scaledVol * 590.0f ;
    myRectangle[0].scl.y = 1+ scaledVol ;
    myRectangle[0].catchUpSpeed = scaledVol*.5  ;
    myRectangle[0].xenoToPoint(mouseX, mouseY);
    
    for (int i=1; i<RECT_NUM;i++) {
        
        
        myRectangle[i].scl.x = 20+ scaledVol * 200.0f ;
        myRectangle[i].scl.y = myRectangle[i-1].scl.y-0.01 ;
        myRectangle[i].catchUpSpeed = 0.4 ;
        myRectangle[i].xenoToPoint(myRectangle[i-1].pos.x, myRectangle[i-1].pos.y);
    }
    
    
    //lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
    
	
    
}

//--------------------------------------------------------------
void testApp::draw(){
	
    
    
    
    for (int i=0; i<RECT_NUM;i++) {
        ofSetColor(198-i, 246-i, 55);
        // ofSetColor(ofMap(i, 0, 99, 255, 50),ofMap(i, 0, 99, 200, 100));  ///??
        myRectangle[i].draw();
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}

