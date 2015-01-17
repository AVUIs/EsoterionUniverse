//
//  ecuaObject.h
//  EsoterionCarrotUniverseAlpha
//
//  Created by Borut Kumperscak on 7. 12. 14.
//
//

#ifndef __EsoterionCarrotUniverseAlpha__ecuaObject__
#define __EsoterionCarrotUniverseAlpha__ecuaObject__

#include "ofMain.h"
#include "ECUBaseObject.h"


#define HOST "192.168.0.2"
//#define HOST "localhost"
#define PORT 12345


class ecuaObject : public ECUBaseObject {
    
public:

    ecuaObject(ofVec3f _p);
    ~ecuaObject();

    void setup(ofVec3f _p, int _id=0);
    void update();
    void draw();
    void setWarmth(float _warmth);
    void setSize(int _size);
    void setSharpness(int _sharpness);
    void setOscillation(float _oscillation);
    
    void setParam(int _param, float _val);
    float getParam(int _param);
//    float getSaveParam(int _param);     //Borut: use this when saving parameters so it corresponds to mappings SetParam() which are a hack because of funky UI

/*
    ofSpherePrimitive sphere;
    ofMaterial material;
*/
    float   objWarmth;
    ofColor objColor;
    int     objSize;
    int     objSharpness;
    float   objOscillation;
    float   objAmplitude;
    
};


#endif /* defined(__EsoterionCarrotUniverseAlpha__ecuaObject__) */
