
//
//  ECUUniverse.cpp
//  esoterionUniverse
//
//  Created by Will Gallia on 06/12/2014.
//
//

#include "ECUUniverse.h"


ECUUniverse::ECUUniverse() {
    cout << "made cam" << endl;
//    cam.enableMouseInput();
}


ECUUniverse::~ECUUniverse() {
//    for(map<int, ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
//        delete it->second;
//    }
    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
//        (*it)->draw();
        delete *it;
    }
    
    cout << "destructing" << endl;

}

void ECUUniverse::update() {
    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        (*it)->update();
    }
}

void ECUUniverse::draw() {
    

    cam.setPosition(pos);

    
    ofSetColor(255);
    cam.begin();
    


    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        (*it)->draw();
    }
    

    cam.end();

    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        
        ofVec3f screenPos = cam.worldToScreen((*it)->pos);
        ofPoint screenPos2 = ofPoint(screenPos.x, screenPos.y); //in 2D
        ofRectangle screenRect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
        
        if (screenRect.inside(screenPos.x, screenPos.y)) {
            (*it)->distToCam = (*it)->pos.distance(this->pos);
            ofVec2f screenCenter(ofGetWidth()>>1, ofGetHeight()>>1);
            (*it)->distToCenter = screenCenter.distance(screenPos2);
        
            
            ofDrawBitmapString("dtc = " + ofToString(((*it)->distToCam)) + ", " + ofToString((*it)->distToCenter),  screenPos.x, screenPos.y);
        }
        
//        ofDrawCircle(a.x, a.y, 20);
        
    }

    
}

int ECUUniverse::addObject(ECUBaseObject *object) {
//    int id = objects.size();
//    objects[1] = object;
//     objects.insert(pair<int,ECUBaseObject*>(id, object));
    object->universeRef = this;
    object->id = objects.size();
    objects.push_back(object);
}

#define DIST_TO_SELECT 40

ECUBaseObject* ECUUniverse::findEditObject(float x, float y) {
    
    //this is a hackathon, so no fancy search
    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        ofVec3f screenPos = cam.worldToScreen((*it)->pos);
        ofPoint screenPos2 = ofPoint(screenPos.x, screenPos.y); //in 2D
        float d = screenPos.distance(ofVec2f(x, y));
        cout << d << endl;
        if (d  < DIST_TO_SELECT) {
            return *it;
        }
    }
    return NULL;
}