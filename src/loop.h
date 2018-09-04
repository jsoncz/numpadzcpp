#ifndef LOOP_H
#define LOOP_H
#include "ofMain.h"
#include "ofxGui.h"

class Loop{

friend class SetSoundValues;
friend class ofApp;

public:

    static vector<Loop*> loops;
    void setup(const filesystem::path& fileName);
    void play();
    void stop();
    void delLoop();
    void saveLoop();

    static int count;
    int id;
    static int ID;

    ofSoundPlayer snd;
    ofxPanel box;
    ofxButton del;
//    ofxButton save;
    ofParameterGroup effects;

    ofParameter<bool> mute;
    ofParameter<bool> shuffle;
    ofxFloatSlider volume;
    ofxFloatSlider pitch;
    ofxFloatSlider position;
    ofParameter<float> trim;
    ofParameter<int> numSlices;
    string sampleFile;
    string loopData;
    bool wasDragged;
  };

#endif // LOOP_H
