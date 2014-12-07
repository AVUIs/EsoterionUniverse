//
//  ECUBaseObject.h
//  esoterionUniverse
//
//  Created by Will Gallia on 06/12/2014.
//
//

#pragma once

#include "ofMain.h"

class ECUUniverse;

class ECUBaseObject {
public:
    ECUBaseObject(ECUUniverse *uni=NULL): universeRef(uni) {
        
    }
    
    virtual ~ECUBaseObject() {}
    
    virtual void draw() {}
    
    ofVec3f pos;
    
    ECUUniverse *universeRef;
};