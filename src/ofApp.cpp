

#include "ofApp.h"

//#include "ECURabbitObject.h"
#include "ecuaObject.h"

ofVec3f p;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
//    ofSetEscapeQuitsApp(false);
//    mesh.load("lofi-bunny.ply");
    
//    cout << cam.getTarget().getPosition() << endl;
    universe = new ECUUniverse();
//Borut    universe->addObject(new ecuaObject(ofVec3f(0, 0, -1000)));
    //    cam.disableMouseInput();
    
    //    cam.set
    
    ofSetSmoothLighting(true);
    pointLight2.setDiffuseColor( ofFloatColor(.3, .3, .3));
    pointLight2.setSpecularColor(ofFloatColor(10, 10, 10));
    pointLight2.setPosition(120, 80, 500);


    currentEditingObj = NULL;
    
//    ofAddListener(ofEvent::mousePressed, &control, control::mousePressed)
//    ofAddListener(ofEvents().mouseDragged , &control, &ctrls::mouseDragged);
//    ofAddListener(ofEvents().mousePressed, &control, &ctrls::mousePressed);
//    ofAddListener(ofEvents().mouseReleased, &control, &ctrls::mouseReleased);
//    ofAddListener(ofEvents().mouseScrolled, &control, &ctrls::mouseScrolled);

//    ofRegisterMouseEvents(control);

    showHelp = false;
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
//            cout<<control.fadersPos[i]<<endl;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    ofShowCursor();
    ofBackgroundGradient(ofColor(50), ofColor(0));
    //ofBackground(0, 0, 0);
    
    ofSetColor(255);
    
    ofEnableDepthTest();
    ofEnableLighting();
    pointLight2.enable();
    
    universe->draw();
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    if(currentEditingObj != NULL) {
        control.drawP();
    }
    
    if (universe->objects.size()==0 || showHelp) {
        ofSetColor(255);
        ofDrawBitmapString("KEY\n\nA = Add objects\nS = Save universe\nL = Load universe\nTwo-finger mouse drag = move arround\nZ + mouse drag = Hold to move in Z direction\nClick on object = Show GUI\nCmd-Click = Secondary GUI\nAlt-Click = Tertiary GUI\nH = Show this help", ofGetWidth()/2 - 100, 30);
    }
    
    ofSetColor(255,0,0);
    ofDrawBitmapString(universe->saved?"SAVED":"NOT SAVED", 10, 10);
}

bool zDown = false;


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

#define KEY(k, f) if(key == (k)) { (f); }

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key=='s' || key =='l') currentEditingObj=NULL;
    
    KEY('z', zDown = true)
    
    KEY('a', createObject())

    KEY('s', universe->save());

    KEY('l', universe->load());

    KEY('h', showHelp =!showHelp);

    KEY('d', universe->debug = !universe->debug);
    
    KEY(OF_KEY_COMMAND, control.useSecondary=true);
    KEY(OF_KEY_ALT, control.useTertiary=true);
    //cout << "current pos = " << universe->pos << endl;
    //cout << "there are " << universe->objects.size() << " objects" << endl;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    KEY('z', zDown = false);
    KEY(OF_KEY_COMMAND, control.useSecondary=false);
    KEY(OF_KEY_ALT, control.useTertiary=false);
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
   // cout << "cam pos = " << downPosition << endl;
    downOrientation = universe->cam.getOrientationQuat(); // ofCamera::getGlobalOrientation();
    
    if(currentEditingObj != NULL && control.deleteObject(x, y, button)) {
        universe->deleteObject(currentEditingObj);
        currentEditingObj == NULL;
    } else {
        control.mousePressed(x, y, button);
        if(currentEditingObj == NULL) {
            currentEditingObj = universe->findEditObject(x, y);
            if (currentEditingObj != NULL) {
                control.setActive(1);
                //if we found an object, set the of the control to the object so there is no jump
                for (int i = 0; i < control.amnt; i++) {
                    control.fadersPos[i] = currentEditingObj->getParam(i);
                }
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
