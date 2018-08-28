#ifndef LOOP_H
#define LOOP_H
#include "ofMain.h"
#include "ofxGui.h"


class Loop{
public:

    void setup(const filesystem::path& fileName);
    void play();
    void stop();
    void delLoop();

    static int count;
    int id;
    static int ID;
    static vector<Loop*> loops;
    ofSoundPlayer snd;
    ofxPanel box;
    ofxButton button;
    ofxFloatSlider volume;
    ofxFloatSlider pitch;

  };




#endif // LOOP_H
