#ifndef LOOP_H
#define LOOP_H
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMaxim.h"

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
    ofxButton save;
    ofxButton load;

    ofxFloatSlider volume;
    ofxFloatSlider pitch;
    ofxFloatSlider position;
    ofxFloatSlider trim;
    string sampleFile;
    string loopData;
  };

#endif // LOOP_H
