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

#define HOST "localhost"
#define PORT 12345

class ecuaObject : public ECUBaseObject {
    
public:

    ecuaObject(ofVec3f _p, int _id);
    ~ecuaObject();

    void setup(ofVec3f _p, int _id);
    void update(float _distance);
    void draw();
    void setWarmth(float _warmth);
    void setSize(int _size);
    void setSharpness(int _sharpness);
    void setOscillation(float _oscillation);
    
    void seParam(int _param, float _val);
/*
    ofSpherePrimitive sphere;
    ofLight pointLight2;
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
