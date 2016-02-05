#ifndef _TEST_APP
#define _TEST_APP
#define RECT_NUM 150  // how to change???

#include "ofMain.h"
#include "rectangle.h"



class testApp : public ofBaseApp{
	
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioIn(float * input, int bufferSize, int nChannels);
	
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
 
    float startTime;
    
    
    rectangle myRectangle[RECT_NUM];
    
    ofSoundStream soundStream;
    
    // music
    ofSoundPlayer piano;
    
    int number;
    
};

#endif	

