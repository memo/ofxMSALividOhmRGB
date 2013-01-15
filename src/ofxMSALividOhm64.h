#pragma once


namespace msa {
    
    class LividOhm64 {
    public:
        struct {
            int tap = 87;  // bpm button in top right
            int function[6] = { 69, 70, 71, 77, 78, 79 }; // 6 function / transport buttons in top right
            int track[8] = { 65, 73, 66, 74, 67, 75, 68, 76 };    // 8 track buttons (mute/solo)
            int transform[2] = { 64, 72 };   // two buttons either side of the crossfader
            
            // the 8x8 grid of buttons:
            // [x, y] in the range [0, 0] - [7, 7]
            // [0, 0] being top left
            int clip(int x, int y) {return x*8 + y;}
        } button;
        
        struct {
            int volume[8] = { 23, 22, 15, 14, 5, 7, 6, 4 };  // volume faders
            int knob[8] = { 17, 16, 9, 8, 19, 18, 11, 10 };    // all knobs
            int pan[8] = { 21, 20, 13, 12, 3, 1, 0, 2 };     // pan knobs
            int crossFader = 24;
        } analog;
        
        
//        
//        void loadSettings(string filename = "ohmrgb-default.lmd") {
//            ofLogVerbose() << "msa::midi::OhmRGB - " << filename;
//            ofBuffer buf(ofBufferFromFile(filename));
//            
//            // process all lines
//            while(!buf.isLastLine()) {
//                
//                // split first part of line off
//                vector<string> s = ofSplitString(buf.getNextLine(), "240 0 1 97 7 ");
//                
//                if(s.size() == 2) {
//                    // split at spaces
//                    vector<string> ps = ofSplitString(s[1], " ");
//                    
//                    // convert all strings to ints
//                    vector<int> pi;
//                    for(int i=0; i<ps.size(); i++) pi.push_back(atoi(ps[i].c_str()));
//                    
//                    int NN = pi[0];
//                    
//                    switch(NN) {
//                            // Map Single LED Indicator
//                        case 9:
//                        {
//                            int LL = pi[1];
//                            int HH = pi[2];
//                            int CR = pi[3];
//                            
//                            // note
//                            if(HH == 0) {
//                                
//                            } else
//                                // CC
//                                if(HH == 1) {
//                                    
//                                }
//                            
//                        }
//                            break;
//                            
//                            // Map Analog Inputs
//                        case 10:
//                            for(int i=0; i<25; i++) {
//                                int t = i;
//                                controls[t].number = pi[i*2+1];
//                                controls[t].status = pi[i*2+2] ? MIDI_CONTROL_CHANGE : MIDI_NOTE_ON;
//                                printf("  analog input %i to %i\n", t, controls[t].number);
//                            }
//                            break;
//                            
//                            // Map Buttons
//                        case 11:
//                            for(int i=0; i<88; i++) {
//                                int t = i+25;
//                                controls[t].number = pi[i*2+1];
//                                controls[t].status = pi[i*2+2] ? MIDI_CONTROL_CHANGE : MIDI_NOTE_ON;
//                                printf("  map input %i to %i\n", t, controls[t].number);
//                            }
//                            break;
//                            
//                    }
//                    
//                } else {
//                    ofLogWarning() << "line is invalid: " << s[0];
//                }
//            }
//        }
        
    };

}