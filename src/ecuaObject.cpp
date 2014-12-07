//
//  ecuaObject.cpp
//  EsoterionCarrotUniverseAlpha
//
//  Created by Borut Kumperscak on 7. 12. 14.
//
//

#include "ecuaObject.h"


ecuaObject::ecuaObject(ofVec3f _p, int _id) {
    setup(_p, _id);
    
}

ecuaObject::~ecuaObject() {
    
}

void ecuaObject::setup(ofVec3f _p, int _id) {


    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 128 );
    material.setEmissiveColor(ofColor(128, 0, 0, 255));
    // the light highlight of the material //
    material.setDiffuseColor(ofColor(128, 0, 0, 255));
    //    material.setSpecularColor(ofColor(128, 0, 0, 128));

    objWarmth = 100;
    objColor.setHsb(objWarmth, 255, 255);
    objSize = 100;
    objSharpness = 100;
    objOscillation = 1.0;
    objAmplitude = 0.01;
    pos = _p;
    id = _id;
}

void ecuaObject::update() {
    objColor.setHsb(objWarmth, 255, 255);
    material.setDiffuseColor(objColor);
    material.setEmissiveColor(objColor);
    sphere.setResolution(objSharpness);
    float curSize = objSize + (objSize * objAmplitude * cos(ofGetElapsedTimef()*objOscillation));
    sphere.setRadius(curSize);
    
}

void ecuaObject::draw() {
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    
    material.begin();

    // Sphere //
    sphere.setPosition(pos);
    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0, 1.0, 0.0);
    
    sphere.draw();

    material.end();
    
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

void ecuaObject::seParam(int _param, float _val) {
    switch (_param) {
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
}




