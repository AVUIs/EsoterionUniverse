//
//  ECUBaseObject.h
//  esoterionUniverse
//
//  Created by Will Gallia on 06/12/2014.
//
//

#pragma once

#include "ofMain.h"

class ECUBaseObject {
public:
    ECUBaseObject() {
        
    }
    
    virtual ~ECUBaseObject() {}
    
    virtual void draw() {}
    
    ofVec3f pos;
};