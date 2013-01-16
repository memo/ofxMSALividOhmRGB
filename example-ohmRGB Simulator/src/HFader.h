#pragma once

#include "ofxMidi.h"
#include "ofxMSAInteractiveObject.h"


namespace msa {
    
    class HFader : public ofxMSAInteractiveObject {
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
            ofRect(ofLerp(x, x+width, value), y-2, 2, height+4);
            
            ofPopStyle();
        }
        
        //--------------------------------------------------------------
        virtual void onRollOver(int x, int y) {
            if(ofGetMousePressed()) onPress(x, y, 0);
        }
        
        //--------------------------------------------------------------
        virtual void onDragOver(int x, int y, int button) {
            value = ofMap(x, this->x, this->x + width, 0, 1, true);
            pmidiOut->sendControlChange(1, midiCC, value*127);
        }

        //--------------------------------------------------------------
        virtual void onPress(int x, int y, int button) {
            onDragOver(x, y, button);
        }
        
    };
    
}