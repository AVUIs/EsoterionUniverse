#include "ctrls.h"

ctrls::ctrls() {
    setup();
}

//--------------------------------------------------------------
void ctrls::setup(){
    
    spacer = TWO_PI / amnt;

    for(int i= 0; i< amnt; i++){
        fadersPos.push_back(1);
        isTouched.push_back(false);
        xMax.push_back( size*scale * sin(i*spacer));//i*spacer; //
        yMax.push_back( size*scale * cos(i*spacer));
        xMin.push_back( innerCircle * sin(i*spacer)); //xMax-20;//
        yMin.push_back( innerCircle * cos(i*spacer));
        
        xPos.push_back( xMax[i] * 1.f);
        yPos.push_back( yMax[i] * 1.f);
        
        len.push_back(ofDist(xMin[i],yMin[i],xMax[i],yMax[i]));
    }


//    ofAddListener(ofEvents().update, this, &ctrls::update);
//    ofAddListener(ofEvents().mouseDragged , this, &ctrls::mouseDragged);
//    ofAddListener(ofEvents().mousePressed, this, &ctrls::mousePressed);
//    ofAddListener(ofEvents().mouseReleased, this, &ctrls::mouseReleased);
//    ofAddListener(ofEvents().mouseScrolled, this, &ctrls::mouseScrolled);

}

//--------------------------------------------------------------
void ctrls::update(){


}

//--------------------------------------------------------------
void ctrls::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    for (int i = 0; i < amnt; i ++){
        ofSetColor(255,0,0);

        float mouseDist = ofDist(mouseX, mouseY, xPos[i], yPos[i]);
        if(mouseDist < ballSize*2){
            ofFill();
            ofDrawEllipse(xPos[i],yPos[i],ballSize,ballSize);
        }

        if(touchedFader == i){
            ofSetColor(0,0,255,100);
            ofDrawEllipse(xPos[i], yPos[i],ballSize*2, ballSize*2);
            ofDrawLine(xMin[i],yMin[i],xMax[i], yMax[i]);
        }
        
        else{
            ofSetColor(255,0,0,30);
            ofDrawLine(xMin[i],yMin[i],xMax[i], yMax[i]);
        }
        ofNoFill();
        ofSetColor(255,100,100);
        
        ofDrawEllipse(xPos[i], yPos[i], ballSize,ballSize);
        ofSetColor(255,220,0,200);
        ofDrawEllipse(0,0,innerCircle*2,innerCircle*2);

        ofDrawLine(xPos[i],yPos[i],xPos[(i+1)%amnt],yPos[(i+1)%amnt]);
    }
    
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ctrls::keyPressed(int key){

}

//--------------------------------------------------------------
void ctrls::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ctrls::mouseMoved(int x, int y){
    
    mouseX = x-(ofGetWidth()/2);
    mouseY = y-(ofGetHeight()/2);
    
}

//--------------------------------------------------------------
void ctrls::mouseDragged(int x, int y, int button){
    mouseX = x-(ofGetWidth()/2);
    mouseY = y-(ofGetHeight()/2);
    
    for(int i = 0; i < amnt;i++){
        if(touchedFader == i){
            
            float zeroDist = ofDist(mouseX,mouseY,0,0);
            if(dragged && zeroDist > innerCircle){
  //              cout<<ofDist(mouseX,mouseY,xMin[i],yMin[i])+innerCircle<<endl;
                
                float val = ofMap(   ofDist(mouseX,mouseY,xMin[i],yMin[i])+innerCircle   , 0, len[i], 0, 1);
                
                val = ofClamp(val,0,1);
//                cout<<len[i]<<"  "<<val<<endl;
                
                xPos[i] = val * xMax[i];
                yPos[i] = val * yMax[i];
                
                fadersPos[i] = val;
                
            }
        }
    }
}

//--------------------------------------------------------------
void ctrls::mousePressed(int x, int y, int button){
    dragged = true;
    downX=x;
    downY=y;
    
    for(int i = 0; i<amnt; i++){
        float mouseDist = ofDist(mouseX, mouseY, xPos[i], yPos[i]);

        if( mouseDist < ballSize*2){
            
            float zeroDist = ofDist(mouseX,mouseY,0,0);
            
            if(dragged && zeroDist > innerCircle){
                touchedFader = i;                }
        }

    }

}

//--------------------------------------------------------------
void ctrls::mouseReleased(int x, int y, int button){
    dragged = false;
    touchedFader = -1;
}

//--------------------------------------------------------------
void ctrls::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ctrls::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ctrls::dragEvent(ofDragInfo dragInfo){
    
}