#include "ofApp.h"

//#include "ECURabbitObject.h"
#include "ecuaObject.h"

ofVec3f p;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
//    mesh.load("lofi-bunny.ply");
    
//    cout << cam.getTarget().getPosition() << endl;
    curObj = 0;
    universe = new ECUUniverse();
    universe->addObject(new ecuaObject(ofVec3f(0, 0, -1000), curObj));
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
    
    //    cout << cam.getPosition() << endl;
//    cam.setPosition(p.x, p.y, p.z);
    
    
    
    ofSetColor(255);
    
    ofEnableDepthTest();
    ofEnableLighting();
    pointLight2.enable();
    
    universe->draw();
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    control.draw();
    
//    ofVec3f t = ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-mouseY*10);
//    ofDrawCircle(t.x, t.y, t.z);
    
//    cam.begin();
//    cam.end();
    
//    ofPushMatrix();
//    ofTranslate(500, 0);
//    ofSetColor(ofColor::gray);
//    mesh.drawWireframe();
//    
//    ofPopMatrix();
//    
//    mesh.drawWireframe();
//    glPointSize(2);
//    ofSetColor(ofColor::white);
//    mesh.drawVertices();
    
    
    
//    cam.end();
    
//    int n = mesh.getNumVertices();
//    float nearestDistance = 0;
//    ofVec2f nearestVertex;
//    int nearestIndex = 0;
//    ofVec2f mouse(mouseX, mouseY);
//    for(int i = 0; i < n; i++) {
//        ofVec3f cur = cam.worldToScreen(mesh.getVertex(i));
//        float distance = cur.distance(mouse);
//        if(i == 0 || distance < nearestDistance) {
//            nearestDistance = distance;
//            nearestVertex = cur;
//            nearestIndex = i;
//        }
//    }
//    
//    ofSetColor(ofColor::gray);
//    ofLine(nearestVertex, mouse);
//    
//    ofNoFill();
//    ofSetColor(ofColor::yellow);
//    ofSetLineWidth(2);
//    ofCircle(nearestVertex, 4);
//    ofSetLineWidth(1);
//    
//    ofVec2f offset(10, -10);
//    ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + offset);
}

bool zDown = false;

#define KEY(k, f) if(key == (k)) { (f); }

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    KEY('z', zDown = true)
    
    KEY('a', universe->addObject(new ecuaObject(ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-1000), curObj++)))
    
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
    
//    return;
//    universe->cam.rotateAround(mouseX-mouseRange, ofVec3f(0, 1, 0), ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-1000));
    
    
//    ofCamera *c = &universe->cam;
//    ofVec3f t = ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-1000);
//    cout << "t = " << t << endl;
////    ofDrawCircle(t.x, t.y, t.z);
//    
//    ofQuaternion curRot = ofQuaternion(0, c->getXAxis(), mouseX-mouseRange, c->getYAxis(), 0, c->getZAxis());
////    setPosition((prevPosition-target.getGlobalPosition())*curRot +target.getGlobalPosition());
//    c->setPosition((downPosition-t)*curRot +t);
//    c->setOrientation(downOrientation * curRot);
//
//    
//    cout << "rotating " << mouseX-mouseRange << " deg"<< endl;

    control.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(float x, float y) {
    
//    cout << "mouse dragged " << x << ", " << y << endl;
    
//    if (button == OF_MOUSE_BUTTON_3) {
        if (zDown) {
            universe->pos.z+= -y;
        }
        else {
            universe->pos.x-= x;
            universe->pos.y+= y;
        }
//    }
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouseRange = mouseX;
    downPosition = universe->cam.getPosition(); // ofCamera::getGlobalPosition();
    cout << "cam pos = " << downPosition << endl;
    downOrientation = universe->cam.getOrientationQuat(); // ofCamera::getGlobalOrientation();
    
    control.mousePressed(x, y, button);
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
