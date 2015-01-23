

#include "ofApp.h"
#include "ecuaObject.h"

ofVec3f p;

ofShader shader;

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetVerticalSync(true);
    ofSetFrameRate(25);
    universe = new ECUUniverse();
    
    ofSetSmoothLighting(true);
    pointLight2.setDiffuseColor( ofFloatColor(.3, .3, .3));
    pointLight2.setSpecularColor(ofFloatColor(10, 10, 10));
    pointLight2.setPosition(120, 80, 500);


    currentEditingObj = NULL;
    
    showHelp = false;
    
    shader.load("main");
    
    universe->loadUniverse("/Users/whg/Desktop/universe-2015-01-20-00-05-08-005.xml");
}

void ofApp::exit() {
    delete universe;
}

//--------------------------------------------------------------
void ofApp::update(){
    universe->update();
    if(control.getActive()==false){
        currentEditingObj = NULL;
    }
    if(currentEditingObj != NULL ) {
            control.update(universe->cam.worldToScreen((currentEditingObj)->pos));
        for (int i = 0; i < control.amnt; i++) {
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    ofShowCursor();
    ofBackgroundGradient(ofColor(200), ofColor(0));
    
    ofSetColor(255);
    
    shader.begin();
//    ofEnableDepthTest();
//    ofEnableLighting();
//    pointLight2.enable();
    

    universe->draw();

    
//    ofDisableLighting();
//    ofDisableDepthTest();
    shader.end();
    if(currentEditingObj != NULL) {
        control.drawP();
    }
    
    if (universe->objects.size()==0 || showHelp) {
        ofSetColor(255);
        ofDrawBitmapString("KEY\n\nA = Add objects\nS = Save universe\nL = Load universe\nTwo-finger mouse drag = move arround\nZ + mouse drag = Hold to move in Z direction\nH = Show this help", ofGetWidth()/2 - 100, 30);
    }
    
    ofSetColor(255,0,0);
    ofDrawBitmapString(universe->saved?"SAVED":"NOT SAVED", 10, 10);
}

bool zDown = false;

#define KEY(k, f) if(key == (k)) { (f); }

void ofApp::createObject() {
    
    if(currentEditingObj != NULL) {
        //we are now going to turn off, this means that we need to place the object in
        currentEditingObj = NULL;
    }

    else {

        ECUBaseObject *obj = new ecuaObject(ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-1000));
        currentEditingObj = obj;
        universe->addObject(obj);
        for (int i = 0; i < control.amnt; i++) {
            control.fadersPos[i] = currentEditingObj->getParam(i);
        }
    }
    
//    creatingObject = !creatingObject;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key=='s' || key =='l') currentEditingObj=NULL;
    
    KEY('z', zDown = true)
    
    KEY('a', createObject())

    KEY('s', universe->save());

    KEY('l', universe->load());

    KEY('h', showHelp =!showHelp);

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
    if (currentEditingObj!=NULL) {
        control.mouseDragged(x, y, button);
        
        for (int i = 0; i < control.amnt; i++) {
            currentEditingObj->setParam(i, control.fadersPos[i]);
            universe->saved = false;
            //if we found an object, set the of the control to the object so there is no jump
            
        }
    }
    
    ofCamera *c = &universe->cam;
//    ofVec3f t = ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z+mouseY*10);
    ofVec3f t = ofVec3f(0, 0, mouseY*10);
    ofDrawCircle(t.x, t.y, t.z);
    
    ofVec3f la = ofVec3f(downPosition);
    la.z-= 200;
    
    int deg = ofGetFrameNum() % 360;
    float m = 200;
    float xr = cos(DEG_TO_RAD*deg)*m;
    float yr = sin(DEG_TO_RAD*deg)*m;
    universe->pos.x = la.x + xr;
    universe->pos.z = la.z + yr;
    universe->la = ofVec3f(la);
//    universe->cam.setPosition(<#float px#>, <#float py#>, <#float pz#>)
//    universe->cam.rotateAround(mouseX-mouseRange, ofVec3f(0, 1, 0), ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-1000));
//    ofQuaternion curRot = ofQuaternion(0, c->getXAxis(), mouseX-mouseRange, c->getYAxis(), 0, c->getZAxis());
//    setPosition((prevPosition-target.getGlobalPosition())*curRot +target.getGlobalPosition());


//    c->setPosition(t);
   
//    c->lookAt(downPosition);
//    universe->cam.lookAt(la);
//    c->setOrientation(downOrientation * curRot);
//    c->setPosition((downPosition-t)*curRot +t);
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
    
    downPosition = ofVec3f(universe->pos); //universe->cam.getPosition(); // ofCamera::getGlobalPosition();
   // cout << "cam pos = " << downPosition << endl;
    downOrientation = universe->cam.getOrientationQuat(); // ofCamera::getGlobalOrientation();
    
    control.mousePressed(x, y, button);
    
    if(currentEditingObj == NULL) {
        currentEditingObj = universe->findEditObject(x, y);
        
        if (currentEditingObj != NULL) {
            control.setActive(1);
            //if we found an object, set the of the control to the object so there is no jump
            for (int i = 0; i < control.amnt; i++) {
                control.fadersPos[i] = currentEditingObj->getParam(i);
//                cout<<"fadersPOS " <<control.fadersPos[i]<<endl;
//                cout<<"editObj " <<currentEditingObj->getParam(i)<<endl;
//                cout<<"fadersPOS " <<control.fadersPos[i]<<endl;

            }
        }
    }
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
