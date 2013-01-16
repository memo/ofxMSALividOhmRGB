#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class testApp : public ofBaseApp, public ofxMidiListener {
public:

    void setup();
    void draw();
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
};
