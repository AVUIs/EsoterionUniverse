//
//  ECUUniverse.h
//  esoterionUniverse
//
//  Created by Will Gallia on 06/12/2014.
//
//

#pragma once

#include "ofMain.h"

#include "ECUBaseObject.h"
#include "ecuaObject.h"
#include "ofxXmlSettings.h"

class ECUUniverse {
public:
    ECUUniverse();
    ~ECUUniverse();
    void clearUniverse();
    
    void update();      //KX sends OSC
    void draw();
    int addObject(ECUBaseObject *object);
    void save();
    void load();
    void saveUniverse(string path);
    void loadUniverse(string path);
    ECUBaseObject* findEditObject(float x, float y);
    
    
    ofCamera cam;
//    map<int, ECUBaseObject*> objects;
    vector<ECUBaseObject*> objects;
    ofVec3f pos, la;

    ofxXmlSettings xml;
    bool saved;
};

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
