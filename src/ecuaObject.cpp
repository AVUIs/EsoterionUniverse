//
//  ecuaObject.cpp
//  EsoterionCarrotUniverseAlpha
//
//  Created by Borut Kumperscak on 7. 12. 14.
//
//

#include "ecuaObject.h"
#include "ofxOsc.h"

static ofxOscSender *sender = NULL;        //KX each obj same sender

ecuaObject::ecuaObject(ofVec3f _p) {
    setup(_p);
    if (sender==NULL) {
        sender = new ofxOscSender();
        sender->setup(HOST, PORT);
    }
}

ecuaObject::~ecuaObject() {
    if (sender!=NULL) {
        delete sender;
        sender = NULL;
    }
}

void ecuaObject::setup(ofVec3f _p, int _id) {

    objWarmth = 100;
    objColor.setHsb(objWarmth, 255, 255);
    objSize = 100;
    objSharpness = 100;
    objOscillation = 1.0;
    objAmplitude = 0.02;
    pos = _p;
    id = _id;
}

void ecuaObject::update() {
  
    if (sender!=NULL) {
        float curSize = objSize + (objSize * objAmplitude * cos(ofGetElapsedTimef()*objOscillation));
        ofxOscMessage m;
        
        m.setAddress("ecu");
        m.addIntArg(id);
        m.addFloatArg(objWarmth);
        m.addFloatArg(objSize);
        m.addFloatArg(objSharpness);
        m.addFloatArg(distToCenter);
        m.addFloatArg(distToCam);
        sender->sendMessage(m);
        
//        m.setAddress("/object/id");
//        m.addIntArg(id);
//        sender->sendMessage(m);
//        m.clear();
//        m.setAddress("/object/warmth");
//        m.addFloatArg(ofMap(objWarmth, 0, 128, 0.0, 1.0, true));
//        sender->sendMessage(m);
//        m.clear();
//        m.setAddress("/object/size");
//        m.addFloatArg(ofMap(objSize, 10, 300, 0.0, 1.0, true));
//        sender->sendMessage(m);
//        m.clear();
//        m.setAddress("/object/sharpness");
//        m.addFloatArg(ofMap(objSharpness, 2, 42, 0.0, 0.1, true));
//        sender->sendMessage(m);
//
//        m.clear();
//        m.setAddress("/object/distanceToCenter");
//        m.addFloatArg(distToCenter);
//        sender->sendMessage(m);
//        
//        m.clear();
//        m.setAddress("/object/distanceToCam");
//        m.addFloatArg(distToCam);
//        sender->sendMessage(m);
    }
}

void ecuaObject::draw() {
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);

//    ofPushMatrix();
  //  ofRotate(spinX, 1.0, 0.0, 0.0);
   // ofRotate(spinY, 0.0, 1.0, 0.0);
    objColor.setHsb(objWarmth, 255, 255);
    ofFill();
    ofSetSphereResolution(objSharpness);
    ofSetColor(objColor);
    float curSize = objSize + (objSize * objAmplitude * cos(ofGetElapsedTimef()*objOscillation));
    ofDrawSphere(pos, curSize);
//    ofPopMatrix();
}

void ecuaObject::setWarmth(float _warmth) {
    objWarmth = _warmth;
}

void ecuaObject::setSize(int _size) {
    objSize = _size;
}

void ecuaObject::setSharpness(int _sharpness) {
    objSharpness = _sharpness;
}

void ecuaObject::setOscillation(float _oscillation) {
    objOscillation = _oscillation;
}

void ecuaObject::setParam(int _param, float _val) {
/*    switch (_param) {
        case 0:
        objWarmth = ofMap(_val, 0.0, 1.0, 0, 128, true);
        break;
        case 1:
        objSize = ofMap(_val, 0.0, 1.0, 10, 300, true);
        break;
        case 2:
        objSharpness = ofMap(_val, 0.0, 1.0, 2, 42, true);
        break;
        case 3:
        objOscillation = ofMap(_val, 0.0, 1.0, 0, 100.0, true);
        break;
        default:
        break;
    }
*/
    switch (_param) {
        case 0:
        objWarmth = ofMap(_val, 0.3, 1.0, 0, 128, true);
        break;
        case 1:
        objSize = ofMap(_val, 0.3, 1.0, 10, 300, true);
        break;
        case 2:
        objSharpness = ofMap(_val, 0.3, 1.0, 2, 42, true);
        break;
        case 3:
        objOscillation = ofMap(_val, 0.3, 1.0, 0, 100.0, true);
        break;
        default:
        break;
    }
}

float ecuaObject::getParam(int _param) {
    switch (_param) {
        case 0:
            return ofMap(objWarmth, 0, 128, 0.0, 1.0, true);
        case 1:
            return ofMap(objSize, 10, 300, 0.0, 1.0, true);
        case 2:
            return ofMap(objSharpness, 2, 42, 0.0, 1.0, true);
        case 3:
            return ofMap(objOscillation, 0, 100.0, 0.0, 1.0, true);
        default:
            return 0;
    }

}


