#ifndef SEQ_H
#define SEQ_H
#include "ofMain.h"
#include "ofxGui.h"

class Seq
{
public:

    static vector<Seq*> seqs;
    void setup(const filesystem::path& fileName);
    void play();
    void stop();
    void delSeq();
    void saveSeq();

    static int countSeq;
    int id;
    static int ID;

    int sequence[16]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int delay=180;
    int step=0;
    ofSoundPlayer snd;
    ofxPanel box;
    ofxButton del;
    ofxFloatSlider volume;
    ofxFloatSlider pitch;
    ofxFloatSlider position;
    ofParameter<float> trim;
    ofxToggle step1,step2,step3,step4,step5,step6,step7,setp8,step9,step10,step11,step12,step13,step14,step15,step16;
    vector<ofxToggle> seqTogs = {step1,step2,step3,step4,step5,step6,step7,setp8,step9,step10,step11,step12,step13,step14,step15,step16};
    string sampleFile;
    string seqData;
};

#endif // SEQ_H
