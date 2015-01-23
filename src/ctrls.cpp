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
    //double the amount to use with secondary layer
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
void ctrls::update(ofVec3f screenPosition){
    screenPos = screenPosition;
    
//    for(int i = 0; i < amnt; i++){
////        float val = ofMap(   ofDist(mouseX,mouseY,xMin[i],yMin[i])+innerCircle   , 0, len[i], 0, 1);
////        ofMap(<#float value#>, <#float inputMin#>, <#float inputMax#>, <#float outputMin#>, <#float outputMax#>)
//    
////        val = ofMap (fadersPos[i], 0,1,0,len[i]);
////        ofMap(fadersPos[i], xMin, ofDist(xMax[i],yMax[i],xMin[i],yMin[i])+innerCircle, 0, 1);
//        
//       // float val = ofMap( fadersPos[i], 0, ofDist(xMax[i],xMin[i],xMin[i],yMin[i]));
//
//        xPos[i] = fadersPos[i] * xMax[i]+xMin[i];
//        yPos[i] = fadersPos[i] * yMax[i]+yMin[i];
//    }
    for(int i = (useSecondary?amnt:0); i < amnt+(useSecondary?amnt:0); i++){
    xPos[i] = (xMax[i]-xMin[i])*fadersPos[i]+xMin[i];//(size-innerCircle)*scale * sin(i*spacer)*val;
    yPos[i] = (yMax[i]-yMin[i])*fadersPos[i]+yMin[i];//;(size-innerCircle)*scale * cos(i*spacer)*val;
    }
    
}
bool ctrls::getActive(){
    return active;
}
void ctrls::setActive(bool activ){
    active = activ;
}

//--------------------------------------------------------------
void ctrls::draw(){
/*do we need this at all?
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
*/
}

void ctrls::drawP(){
    
    ofPushMatrix();
    ofTranslate(screenPos);
    ofSetColor(0,0,0);
    if (useTertiary) {
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(0, 0, 0);
        ofDrawEllipse(0,0,innerCircle*2,innerCircle*2);
        ofDrawLine(-innerCircle/2, -innerCircle/2, innerCircle/2, innerCircle/2);
        ofDrawLine(innerCircle/2, -innerCircle/2, -innerCircle/2, innerCircle/2);
        
        
    } else {
        ofSetLineWidth(2);
        ofNoFill();
        ofSetColor(0,0,0,200);
        if (useSecondary) ofSetColor(255,255,255,200);
        ofDrawEllipse(0,0,innerCircle*2,innerCircle*2);

        if (useSecondary) ofSetColor(255,255,255);
        for (int i = (useSecondary?amnt:0); i < amnt+(useSecondary?amnt:0); i ++){
            //ofSetColor(255,0,0);
            
            float mouseDist = ofDist(mouseX, mouseY, xPos[i], yPos[i]);
            if(mouseDist < ballSize*2){
                ofFill();
                ofDrawEllipse(xPos[i],yPos[i],ballSize,ballSize);
            }
            
            if(touchedFader == i){
                ofSetColor(0,0,0,200);
                if (useSecondary) ofSetColor(255,255,255,200);
                ofDrawEllipse(xPos[i], yPos[i],ballSize*2, ballSize*2);
                ofDrawBitmapString(ofToString(fadersPos[touchedFader],2), -17, 5);
                ofDrawLine(xMin[i],yMin[i],xMax[i], yMax[i]);
            }
            
            else{
                ofSetColor(0,0,0,100);
                if (useSecondary) ofSetColor(255,255,255,100);
                ofDrawLine(xMin[i],yMin[i],xMax[i], yMax[i]);
            }
            ofNoFill();
            //ofSetColor(255,100,100);
            
            ofDrawEllipse(xPos[i], yPos[i], ballSize,ballSize);
            ofDrawLine(xPos[i],yPos[i],xPos[(i+1)%amnt+(useSecondary?amnt:0)],yPos[(i+1)%amnt+(useSecondary?amnt:0)]);
        }
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
    
    mouseX = x-screenPos.x;
    mouseY = y-screenPos.y;
    
}

//--------------------------------------------------------------
void ctrls::mouseDragged(int x, int y, int button){
    mouseX = x-screenPos.x;
    mouseY = y-screenPos.y;
    
//    float mouseDownX = mouseX - downX;
//    float mouseDownY = mouseY - downY;
    
    for(int i = (useSecondary?amnt:0); i < amnt+(useSecondary?amnt:0);i++){
        if(touchedFader == i){
            
            float zeroDist = ofDist(mouseX,mouseY,0,0);
            if(dragged && zeroDist > innerCircle){
  //              cout<<ofDist(mouseX,mouseY,xMin[i],yMin[i])+innerCircle<<endl;
                
                float val = ofMap(   ofDist(mouseX,mouseY,xMin[i],yMin[i])   , 0, len[i], -0.05, 1);
                
                val = ofClamp(val,0,1);
//                cout<<len[i]<<"  "<<val<<endl;
                
//                xPos[i] = (xMax[i]-xMin[i])*val+xMin[i];//(size-innerCircle)*scale * sin(i*spacer)*val;
//                yPos[i] = (yMax[i]-yMin[i])*val+yMin[i];//;(size-innerCircle)*scale * cos(i*spacer)*val;
                
                fadersPos[i] = val;
            }
        }
    }
}

//--------------------------------------------------------------
void ctrls::mousePressed(int x, int y, int button){
    dragged = true;
    downX=mouseX;//x-screenPos.x;
    downY=mouseY;//y-screenPos.y;
    
    for(int i = 0; i<amnt; i++){
        float mouseDist = ofDist(mouseX, mouseY, xPos[i+(useSecondary?amnt:0)], yPos[i+(useSecondary?amnt:0)]);

        if( mouseDist < ballSize*2){
            
            float zeroDist = ofDist(mouseX,mouseY,0,0);
            
            if(dragged && zeroDist > innerCircle){
                touchedFader = i+(useSecondary?amnt:0);
                //cout << "TOUCHED FADER: " << touchedFader << endl;
            }
        }

    }
    
    if(ofDist(downX,downY,0,0) < innerCircle){
        active = 0;
    }
}

bool ctrls::deleteObject(int x, int y, int button) {
    downX=mouseX;
    downY=mouseY;
    if(useTertiary && ofDist(downX,downY,0,0) < innerCircle) {
        active = 0;
        return true;
    }
    return false;
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