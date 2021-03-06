#pragma once

#include "ofMain.h"

#include "ECUUniverse.h"
#include "ctrls.h"

enum {
    CREATING, CREATED
};

class ECUBaseObject;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
    void mouseScrolled(float x, float y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofLight pointLight2;

    
    void createObject();
    ECUBaseObject *currentEditingObj;
    
    
    ECUUniverse *universe;
    ctrls control;
    bool creatingObject;
    
    ofMesh mesh;
//    ofEasyCam cam;
    int curObj;
    
    bool showHelp;
};
