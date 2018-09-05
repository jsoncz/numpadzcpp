#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "loop.h"
#include "seq.h"
#include "ofxSoundObjects.h"
#include "waveformDraw.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();

        void resetVol();
        void resetPitch();
        void stopAll();
        void startAll();
        void muteAll();
        void loadProject();
        void saveProject();
        void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void loadPack();


        ofParameter<string> soundpack;
        ofxGuiGroup volumes;
        ofxButton volTog;
        ofxFloatSlider vol1;
        ofxFloatSlider vol2;
        ofxFloatSlider vol3;
        ofxFloatSlider vol4;
        ofxFloatSlider vol5;
        ofxFloatSlider vol6;
        ofxFloatSlider vol7;
        ofxFloatSlider vol8;
        ofxFloatSlider vol9;
        ofxButton pitTog;
        ofxFloatSlider pit1;
        ofxFloatSlider pit2;
        ofxFloatSlider pit3;
        ofxFloatSlider pit4;
        ofxFloatSlider pit5;
        ofxFloatSlider pit6;
        ofxFloatSlider pit7;
        ofxFloatSlider pit8;
        ofxFloatSlider pit9;

        float * fftSmooth =  new float [8192];
        int bands = 32;

        float minPitch = 0.10;
        float defaultPitch = 1.00;
        float maxPitch = 4.00;
        bool loop = false;
        bool sequence = false;
        vector<ofxFloatSlider> lPList;
        vector<ofxFloatSlider> volList;

        vector<string> packlist;
        int listSize;
        int selPack = 0;

        ofSoundStream stream;
        ofxSoundOutput output;
        ofxSoundPlayerObject player;
         ofxSoundPlayerObject player2;
        vector<ofMesh> waveforms;
          waveformDraw wave;

        ofSoundPlayer snd1,snd2,snd3,snd4,snd5,snd6,snd7,snd8,snd9;
        vector<ofSoundPlayer> sounds;

        ofSoundPlayer snd;
        ofxButton button;
        ofxFloatSlider volume;
        ofxPanel menu;
        ofParameterGroup params;
        ofParameter<bool> bTrimTog;
        ofxButton  stopTog;
        ofxButton  startTog;
        ofxButton muteTog;

        ofxFloatSlider masterPitch;
        ofxFloatSlider bpm;
        ofxButton loadPrj;
        ofxButton savePrj;



    };
