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
    universe->addObject(new ecuaObject(ofVec3f(), curObj));
    //    cam.disableMouseInput();
    
    //    cam.set

}

void ofApp::exit() {
    delete universe;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(64), ofColor(0));
    
    //    cout << cam.getPosition() << endl;
//    cam.setPosition(p.x, p.y, p.z);
    
    ofSetColor(255);
    universe->draw();
    
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
    
}

float mouseRange = 0;

void ofApp::mouseDragged(int x, int y, int button) {
    
    universe->cam.rotateAround(mouseX-mouseRange, ofVec3f(0, 1, 0), ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-1000));
    
    
//    ofCamera *c = &universe->cam;
//    ofVec3f prevPosition = c->getPosition(); // ofCamera::getGlobalPosition();
//    ofQuaternion prevOrientation = c->getOrientationQuat(); // ofCamera::getGlobalOrientation();
//    
//    ofVec3f t = ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-1000);
//    
//    ofQuaternion curRot = ofQuaternion(0, c->getXAxis(), (mouseX > ofGetWidth()/2) ? 1 : -1, c->getYAxis(), 0, c->getZAxis());
////    setPosition((prevPosition-target.getGlobalPosition())*curRot +target.getGlobalPosition());
//    c->setPosition((prevPosition-t)*curRot +t);
//    c->setOrientation(prevOrientation * curRot);
//
//    
//    cout << "rotating " << mouseX-mouseRange << " deg"<< endl;
    
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
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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
