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

class ECUUniverse {
public:
    ECUUniverse();
    ~ECUUniverse();
    
    void update();      //KX send OSC
    void draw();
    int addObject(ECUBaseObject *object);
    
    
    ofCamera cam;
//    map<int, ECUBaseObject*> objects;
    vector<ECUBaseObject*> objects;
    ofVec3f pos;

    
};