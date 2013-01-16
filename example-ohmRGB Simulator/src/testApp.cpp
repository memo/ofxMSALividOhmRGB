#include "testApp.h"

#include "ofxMSALividOhmRGB.h"

#include "Button.h"
#include "VFader.h"
#include "HFader.h"



// for receiving midi data
ofxMidiIn midiIn;

// for sending midi data
ofxMidiOut midiOut;

// contains the midi config data
msa::LividOhm64 ohmRGB;

// contains image of the controller
ofImage image;


// the pixel coordinates of each of the controls on the image
struct  {
    struct Buttons {
        msa::Button tap;  // bpm button in top right
        msa::Button function[6]; // 6 function / transport buttons in top right
        msa::Button track[8];    // 8 track buttons (mute/solo)
        msa::Button transform[2];   // two buttons either side of the crossfader
        msa::Button clip[8][8];       // the 8x8 grid of buttons, first column (x), then row (y)
    } button;
    
    struct Analog {
        msa::VFader volume[8];  // volume faders
        msa::VFader knob[8];    // all knobs
        msa::VFader pan[8];     // pan knobs
        msa::HFader crossFader;
    } analog;
} controls;


//--------------------------------------------------------------
void testApp::setup(){
    // load image
    image.loadImage("600px-Ohm64_MIDI_Defaults.png");
    
    // adjust window size
    ofSetWindowShape(image.getWidth(), image.getHeight());

    
    // init midi
    midiIn.listPorts();
    //midiIn.openPort(0);
    //midiIn.openPort("IAC Pure Data In");	// by name
    midiIn.openVirtualPort("ofxMSALividOhmRGB input");	// open a virtual port
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true);
    
    midiOut.listPorts();
    midiOut.openVirtualPort("ofxMSALividOhmRGB output");
    
    
    
    
    // init all button rectangles on the image
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            controls.button.clip[i][j].set(midiOut, ohmRGB.button.clip(i, j), 172+32.8*i, 4+32.999*j, 25, 25);
        }
    }
    
    for(int i=0; i<4; i++) {
        controls.button.track[i].set(midiOut, ohmRGB.button.track[i], 3+40.6*i, 289, 30, 30);
        controls.button.track[i+4].set(midiOut, ohmRGB.button.track[i+4], 446+40.6*i, 289, 30, 30);
        
        controls.analog.volume[i].set(midiOut, ohmRGB.analog.volume[i], 8+40.6*i, 150, 18, 110);
        controls.analog.volume[i+4].set(midiOut, ohmRGB.analog.volume[i+4], 450+40.6*i, 150, 18, 110);
        for(int j=0; j<3; j++) {
            controls.analog.knob[i+j*4].set(midiOut, ohmRGB.analog.knob[i+j*4], 2+41*i, 2+41*j, 30, 30);
        }
        
        controls.analog.pan[i+4].set(midiOut, ohmRGB.analog.pan[i+4], 444+41*i, 84, 30, 30);
    }
    
    for(int i=0; i<3; i++) {
        for(int j=0; j<2; j++) {
            controls.button.function[i+j*3].set(midiOut, ohmRGB.button.function[i+j*3], 447+41*i, 3+28*j, 27, 17);
        }
    }
    
    controls.analog.crossFader.set(midiOut, ohmRGB.analog.crossFader, 242, 275, 113, 20);
    controls.button.transform[0].set(midiOut, ohmRGB.button.transform[0], 183, 271, 30, 30);
    controls.button.transform[1].set(midiOut, ohmRGB.button.transform[1], 387, 271, 30, 30);
    controls.button.tap.set(midiOut, ohmRGB.button.tap, 565, 3, 33, 34);
    
    
    
    ofBackground(0);
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void testApp::draw() {
    ofSetColor(255);
    image.draw(0, 0);
}

//--------------------------------------------------------------
void testApp::newMidiMessage(ofxMidiMessage& eventArgs) {
    if(eventArgs.status == MIDI_NOTE_ON) {
        
        // find which color it is
        ofColor color = ohmRGB.colors.get(eventArgs.velocity);
        if(color.a > 0) color.a = 128;  // if not black, make semi transparent
        
        // find which note was pressed, could do a reverse hashmap, but wanted to keep this example simple
        for(int i=0; i<8; i++) {
            if(eventArgs.pitch == ohmRGB.button.track[i]) { controls.button.track[i].color = color; return; }
            for(int j=0; j<8; j++) if(eventArgs.pitch == ohmRGB.button.clip(i, j)) { controls.button.clip[i][j].color = color; return; }
        }
        for(int i=0; i<6; i++) {
            if(eventArgs.pitch == ohmRGB.button.function[i]) { controls.button.function[i].color = color; return; }
        }
        for(int i=0; i<2; i++) {
            if(eventArgs.pitch == ohmRGB.button.transform[i]) { controls.button.transform[i].color = color; return; }
        }
        if(eventArgs.pitch == ohmRGB.button.tap) { controls.button.tap.color = color; return; }

    }
}
