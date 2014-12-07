
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

void ECUUniverse::draw() {
    

    cam.setPosition(pos);

    
    ofSetColor(255);
    cam.begin();
    
//    for(map<int, ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
//        it->second->draw();
//    }


    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        (*it)->draw();
    }
    
//    for(int i = 0; i < objects.size(); i++) {
//        objects[i]->draw();
//    }
    
    cam.end();

    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        
        ofVec3f a = cam.worldToScreen((*it)->pos);
        
//        ofDrawCircle(a.x, a.y, 20);
        
    }
    

//    ofVec3f a = cam.worldToScreen(ofVec3f(0, 0, 0));

//    ofDrawCircle(a.x, a.y, 20);
//    cout << a.x << ", " << a.y << endl;
    
//    int n = mesh.getNumVertices();
//    float nearestDistance = 0;
//    ofVec2f nearestVertex;
//    int nearestIndex = 0;
//    ofVec2f mouse(mouseX, mouseY);
//    for(int i = 0; i < n; i++) {
//        ofVec3f cur = cam.worldToScreen(mesh.getVertex(i));
//        float distance = cur.distance(mouse);
//        if(i == 0 || distance < nearestDistance) {
//            nearestDistance = distance;
//            nearestVertex = cur;
//            nearestIndex = i;
//        }
//    }
//    
//    ofSetColor(ofColor::gray);
//    ofLine(nearestVertex, mouse);
//    
//    ofNoFill();
//    ofSetColor(ofColor::yellow);
//    ofSetLineWidth(2);
//    ofCircle(nearestVertex, 4);
//    ofSetLineWidth(1);

    
}

int ECUUniverse::addObject(ECUBaseObject *object) {
//    int id = objects.size();
//    objects[1] = object;
//     objects.insert(pair<int,ECUBaseObject*>(id, object));
    object->universeRef = this;
    objects.push_back(object);
}

