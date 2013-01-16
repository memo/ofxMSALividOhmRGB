#pragma once

#include "ofxMidi.h"
#include "ofxMSAInteractiveObject.h"


namespace msa {
    
    class Button : public ofxMSAInteractiveObject {
    protected:
        int midiNoteNumber;
        ofxMidiOut *pmidiOut;
        
    public:
        
        ofColor color;
        
        //--------------------------------------------------------------
        void set(ofxMidiOut &midiOut, int midiNoteNumber, int x, int y, int w, int h) {
            this->pmidiOut = &midiOut;
            this->midiNoteNumber = midiNoteNumber;
            ofRectangle::set(x, y, w, h);
        }
        
        //--------------------------------------------------------------
        virtual void setup() {
            enableAllEvents();
            color.set(0, 0, 0, 0);
        }
        
        //--------------------------------------------------------------
        virtual void draw() {
            ofPushStyle();

            if(color.a>0) {
                ofSetColor(color);
                ofFill();
                ofRect(*this);
            }
            
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
                
            }
            ofPopStyle();
        }
        
        //--------------------------------------------------------------
        virtual void onRollOver(int x, int y) {
            if(ofGetMousePressed()) onPress(x, y, 0);
        }
        
        //--------------------------------------------------------------
        virtual void onRollOut() {
            if(ofGetMousePressed()) onRelease(0, 0, 0);
        }
        
        //--------------------------------------------------------------
        virtual void onPress(int x, int y, int button) {
            pmidiOut->sendNoteOn(1, midiNoteNumber);
        }
        
        //--------------------------------------------------------------
        virtual void onRelease(int x, int y, int button) {
            pmidiOut->sendNoteOff(1, midiNoteNumber);
        }
    };
    
}