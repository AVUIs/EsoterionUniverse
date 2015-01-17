
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
    saved = false;
}


ECUUniverse::~ECUUniverse() {
    clearUniverse();
}

void ECUUniverse::update() {
    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        (*it)->update();
    }
    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        
        ofVec3f screenPos = cam.worldToScreen((*it)->pos);
        ofPoint screenPos2 = ofPoint(screenPos.x, screenPos.y); //in 2D
        ofRectangle screenRect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
        
        if (screenRect.inside(screenPos.x, screenPos.y)) {
            (*it)->distToCam = (*it)->pos.distance(this->pos);
            ofVec2f screenCenter(ofGetWidth()>>1, ofGetHeight()>>1);
            (*it)->distToCenter = screenCenter.distance(screenPos2);
            
        }
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

    ofSetHexColor(0xffffff);
    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        
        ofVec3f screenPos = cam.worldToScreen((*it)->pos);
        ofDrawBitmapString("dtc = " + ofToString(((*it)->distToCam)) + ", " + ofToString((*it)->distToCenter),  screenPos.x, screenPos.y);
        
//        ofDrawCircle(a.x, a.y, 20);
        
    }
}

void ECUUniverse::save() {
    ofFileDialogResult fileSaveResult;
    fileSaveResult = ofSystemSaveDialog("universe-" + ofGetTimestampString() + ".xml","Save Universe");
    if (fileSaveResult.bSuccess) {
        saveUniverse(ofToDataPath(fileSaveResult.getPath()));
    }
}

void ECUUniverse::saveUniverse(string path) {
    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        int tagNum = xml.addTag("OBJECT");
        cout << tagNum << endl;
        cout << (*it)->id << " " << (*it)->pos.x << " " << (*it)->pos.y << endl;
        xml.setValue("OBJECT:ID", (*it)->id, tagNum);
        xml.setValue("OBJECT:X", (*it)->pos.x, tagNum);
        xml.setValue("OBJECT:Y", (*it)->pos.y, tagNum);
        xml.setValue("OBJECT:Z", (*it)->pos.z, tagNum);
        for (int i =0; i<6;i++) {
            xml.setValue("OBJECT:PARAM" + ofToString(i), (*it)->getParam(i), tagNum);
        }
    }
    xml.saveFile(path);
    saved = true;
}

void ECUUniverse::load() {
    ofFileDialogResult fileLoadResult;
    fileLoadResult = ofSystemLoadDialog("Load Universe", false, ofToDataPath(""));
    if (fileLoadResult.bSuccess) {
        loadUniverse(ofToDataPath(fileLoadResult.getPath()));
    }
}

void ECUUniverse::loadUniverse(string path) {
    clearUniverse();
    xml.loadFile(path);
    for (int i=0; i < xml.getNumTags("OBJECT"); i++) {    //KX XML list = 1-based!!
        cout << "LOADING object " << xml.getValue("OBJECT:ID", 0, i) << " coords " << xml.getValue("OBJECT:X", 0, i) << " " << xml.getValue("OBJECT:Y", 0, i) << " " << xml.getValue("OBJECT:Z", 0, i) << " param1 " << xml.getValue("OBJECT:PARAM1", 0, i) << endl;
        ECUBaseObject *obj = new ecuaObject(ofVec3f((double)xml.getValue("OBJECT:X", 0.0, i), (double)xml.getValue("OBJECT:Y", 0.0, i), (double)xml.getValue("OBJECT:Z", 0.0, i)));
        this->addObject(obj);
        obj->id = xml.getValue("OBJECT:ID", 0, i);
        for (int j =0; j<6;j++) {
            obj->setParam(j, (double)xml.getValue("OBJECT:PARAM" + ofToString(j), 0.0, i));
        }
    }
}

int ECUUniverse::addObject(ECUBaseObject *object) {
//    int id = objects.size();
//    objects[1] = object;
//     objects.insert(pair<int,ECUBaseObject*>(id, object));
    object->universeRef = this;
    object->id = objects.size();
    objects.push_back(object);
    saved = false;
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

void ECUUniverse::clearUniverse() {
    //    for(map<int, ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
    //        delete it->second;
    //    }
    for (vector<ECUBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        //        (*it)->draw();
        delete *it;
    }
    objects.clear();    //Borut: have to do this or we have a ghost object that crashes update() when loading universe
    
    cout << "destructing" << endl;
    
}

