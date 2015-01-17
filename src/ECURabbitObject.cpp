//
//  ECURabbitObject.cpp
//  esoterionUniverse
//
//  Created by Will Gallia on 06/12/2014.
//
//

#include "ECURabbitObject.h"

#include "ECUUniverse.h"

bool fileLoaded = false;
ofMesh mesh;


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
    
//    ofSetColor(ofColor::gray);  
//    mesh.drawWireframe();
    
    glPointSize(2);
    ofSetColor(ofColor::gray);
    mesh.drawVertices();
    
    ofSetColor(ofColor::white);
    ofDrawBitmapString("pos = " + ofToString(pos), 10, 10);
    float d = pos.distance(universeRef->pos);
    ofDrawBitmapString("dist = " + ofToString(d), 10, 20);
//    ofdrawbi
    
    ofPopMatrix();
    

}