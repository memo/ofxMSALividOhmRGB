#pragma once

#include "ofxMidi.h"
#include "ofxMSAInteractiveObject.h"


namespace msa {
    
    class VFader : public ofxMSAInteractiveObject {
    protected:
        int midiCC;
        float value;
        ofxMidiOut *pmidiOut;
        
    public:
        
        //--------------------------------------------------------------
        void set(ofxMidiOut &midiOut, int midiCC, int x, int y, int w, int h) {
            this->pmidiOut = &midiOut;
            this->midiCC = midiCC;
            ofRectangle::set(x, y, w, h);
        }
        
        //--------------------------------------------------------------
        virtual void setup() {
            enableAllEvents();
            value = 0;
        }
        
        //--------------------------------------------------------------
        virtual void draw() {
            ofPushStyle();
            if(isMouseOver()) {
                
                // draw fill
                if(ofGetMousePressed()) {
                    ofSetColor(255, 255, 0, 50);
                    ofFill();
                    ofRect(*this);
                }

                // draw frame
                ofSetColor(255, 0, 0);
                ofSetLineWidth(2);
                ofNoFill();
                ofRect(*this);
            } else {
                ofSetColor(0);
            }
            
            // draw fader bit
            ofFill();
            ofRect(x-2, ofLerp(y, y+height, 1-value), width+4, 2);
            
            ofPopStyle();
        }
        
        //--------------------------------------------------------------
        virtual void onRollOver(int x, int y) {
            if(ofGetMousePressed()) onPress(x, y, 0);
        }
        
        //--------------------------------------------------------------
        virtual void onDragOver(int x, int y, int button) {
            value = ofMap(y, this->y, this->y + height, 1, 0, true);
            pmidiOut->sendControlChange(1, midiCC, value*127);
        }

        //--------------------------------------------------------------
        virtual void onPress(int x, int y, int button) {
            onDragOver(x, y, button);
        }
        
    };
    
}