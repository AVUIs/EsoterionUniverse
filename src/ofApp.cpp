#include "ofApp.h"

//#include "ECURabbitObject.h"
#include "ecuaObject.h"

ofVec3f p;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
//    mesh.load("lofi-bunny.ply");
    
//    cout << cam.getTarget().getPosition() << endl;
    universe = new ECUUniverse();
    universe->addObject(new ecuaObject(ofVec3f(0, 0, -1000)));
    //    cam.disableMouseInput();
    
    //    cam.set
    
    ofSetSmoothLighting(true);
    pointLight2.setDiffuseColor( ofFloatColor(.3, .3, .3));
    pointLight2.setSpecularColor(ofFloatColor(10, 10, 10));
    pointLight2.setPosition(120, 80, 500);


//    ofAddListener(ofEvent::mousePressed, &control, control::mousePressed)
//    ofAddListener(ofEvents().mouseDragged , &control, &ctrls::mouseDragged);
//    ofAddListener(ofEvents().mousePressed, &control, &ctrls::mousePressed);
//    ofAddListener(ofEvents().mouseReleased, &control, &ctrls::mouseReleased);
//    ofAddListener(ofEvents().mouseScrolled, &control, &ctrls::mouseScrolled);

//    ofRegisterMouseEvents(control);
    

}

void ofApp::exit() {
    delete universe;
}

//--------------------------------------------------------------
void ofApp::update(){
    universe->update();
    control.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(64), ofColor(0));

    ofSetColor(255);
    
    ofEnableDepthTest();
    ofEnableLighting();
    pointLight2.enable();
    
    universe->draw();
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    if(creatingObject) {
        control.draw();
    }
}

bool zDown = false;

#define KEY(k, f) if(key == (k)) { (f); }

void ofApp::createObject() {
    
    if(creatingObject) {
        //we are now going to turn off, this means that we need to place the object in
        ECUBaseObject *obj = new ecuaObject(ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-1000));
        for (int i = 0; i < control.amnt; i++) {
            obj->setParam(i, control.fadersPos[i]);
        }
        universe->addObject(obj);
    }

    creatingObject = !creatingObject;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    KEY('z', zDown = true)
    
    KEY('a', createObject())
    
    cout << "current pos = " << universe->pos << endl;
    cout << "there are " << universe->objects.size() << " objects" << endl;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    zDown = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    control.mouseMoved(x, y);
}

ofVec3f downPosition;
ofQuaternion downOrientation;

float mouseRange = 0;

void ofApp::mouseDragged(int x, int y, int button) {

    control.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(float x, float y) {
    if (zDown) {
        universe->pos.z+= -y;
    }
    else {
        universe->pos.x-= x;
        universe->pos.y+= y;
    }
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouseRange = mouseX;
    downPosition = universe->cam.getPosition(); // ofCamera::getGlobalPosition();
    cout << "cam pos = " << downPosition << endl;
    downOrientation = universe->cam.getOrientationQuat(); // ofCamera::getGlobalOrientation();
    
    control.mousePressed(x, y, button);
    
//    universe
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    control.mouseReleased(x, y, button);
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
