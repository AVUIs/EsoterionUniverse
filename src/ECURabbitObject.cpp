//
//  ECURabbitObject.cpp
//  esoterionUniverse
//
//  Created by Will Gallia on 06/12/2014.
//
//

#include "ECURabbitObject.h"

//only load the mesh file once


ECURabbitObject::ECURabbitObject(ofVec3f p) {
    
    pos = p;
    if (!fileLoaded) {
        mesh.load("lofi-bunny.ply");
    }
}

ECURabbitObject::~ECURabbitObject() {
    
}


void ECURabbitObject::draw() {
    
    ofPushMatrix();
    ofTranslate(pos);
    ofSetColor(ofColor::gray);
  
    mesh.drawWireframe();
    glPointSize(2);
    ofSetColor(ofColor::white);
    mesh.drawVertices();
    
    ofPopMatrix();
    

}