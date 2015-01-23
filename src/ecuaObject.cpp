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

    objWarmth = ofRandom(255.0);
    objColor.setHsb(objWarmth, 255, 255);
    objSize = ofRandom(100.0, 300.0);
    objSharpness = ofRandom(128.0, 255.0);
    objOscillation = ofRandom(1.0);
    objAmplitude = ofRandom(1.0);
    pos = _p;
    id = _id;
    ball = new ofSpherePrimitive();
    ball->setMode(OF_PRIMITIVE_TRIANGLES_ADJACENCY);
    material.setEmissiveColor( ofFloatColor(1.0, 1.0, 1.0));
}

void ecuaObject::update() {
    curSize = objSize * objAmplitude * cos(ofGetElapsedTimef()*objOscillation);
    
    if (sender!=NULL) {
        ofxOscMessage m;
        
        m.setAddress("ecu");
        m.addIntArg(id);
        m.addFloatArg(getParam(0));
        m.addFloatArg(ofMap((objSize), 10, 300, 0.0, 1.0, true));
        m.addFloatArg(getParam(2));
        m.addFloatArg(distToCenter);
        m.addFloatArg(distToCam);
        m.addFloatArg(objAmplitude);
        m.addFloatArg(objOscillation);
        m.addFloatArg(ofMap((curSize), 10, 300, 0.0, 1.0, true));
        sender->sendMessage(m);        
    }
}

void ecuaObject::draw() {
    objColor.setHsb(objWarmth, 255, 255, objSharpness);
    material.setEmissiveColor(objColor);
    material.setSpecularColor(objColor);
    material.setShininess(25);
    
//    light.setDiffuseColor(objColor);
//    light.setPosition(pos);

    ofFill();
    ofSetColor(objColor);
    ball->setRadius(objSize);
    ball->setResolution(objSize/30);
    ball->setPosition(pos);
    
    //modify mesh with some noise - could do this only once..
    float liquidness = 5;
    float amplitude = 50 * objAmplitude * cos(ofGetElapsedTimef()*objOscillation);
    float speedDampen = 5;
    vector<ofVec3f>& verts = ball->getMesh().getVertices();
    for(unsigned int i = 0; i < verts.size(); i+=2){
        verts[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
    }
    ball->rotate(0.1, 0.0, 1.0, 0.0);
    ofEnableLighting();
//    light.enable();
    material.begin();
    ball->draw();
    material.end();
    ofDisableLighting();
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
    switch (_param) {
        case 0:
        objWarmth = ofMap(_val, 0.0, 1.0, 0, 255, true);
        break;
        case 1:
        objSize = ofMap(_val, 0.0, 1.0, 10, 300, true);
        break;
        case 2:
        objSharpness = ofMap(_val, 0.0, 1.0, 0.0, 255.0, true);
        break;
        case 3:
        objOscillation = ofMap(_val, 0.0, 1.0, 0.0, 1.0, true);
        break;
        case 4:
        objAmplitude = ofMap(_val, 0.0, 1.0, 0.0, 1.0, true);
        break;
        default:
        break;
    }

}


float ecuaObject::getParam(int _param) {
    switch (_param) {
        case 0:
        return ofMap(objWarmth, 0, 255, 0.0, 1.0, true);
        case 1:
        return ofMap(objSize, 10, 300, 0.0, 1.0, true);
        case 2:
        return ofMap(objSharpness, 0.0, 255.0, 0.0, 1.0, true);
        case 3:
        return ofMap(objOscillation, 0.0, 1.0, 0.0, 1.0, true);
        case 4:
        return ofMap(objAmplitude, 0.0, 1.0, 0.0, 1.0, true);
        default:
        return 0;
    }
}

