#include "ofApp.h"

int Loop::count = 0;
int Loop::ID = 0;
vector<Loop*>Loop::loops = {};

//class SetSoundValues;
// SetSoundValues setval;

void ofApp::loadPack(){
    ifstream fin; //declare a file stream
    fin.open( ofToDataPath("wav/packlist.txt").c_str() ); //open packlist
    // vector<string> packlist; //declare a vector of strings
    listSize = 0;
    while(!fin.eof()) //while there is stilil text
    {
        string str; //declare a string for storage
        getline(fin, str); //get a line from the file, put it in the string
        packlist.push_back(str); //push the string onto a vector of strings
        listSize++;
    }

    for (int i = 0; i < 9; i++){
        std::string j = to_string(i+1);

        sounds[i].load("wav/"+packlist[selPack]+"/000"+j+".wav");
        sounds[i].setLoop(true);
        sounds[i].setMultiPlay(true);
    }
    ofSetColor(25);
    soundpack = packlist[selPack];

}
//--------------------------------------------------------------
void ofApp::setup(){



    ofSetWindowTitle("NumPadZ");
    ofxGuiSetFont("Helmet.ttf",9, true, true);
    ofSetColor(255,255,255,100);
    ofDrawRectangle(100,ofGetHeight()/2,5*128,200);
    ofBackground(54, 54, 54);
     for (int i = 0; i < 8192; i++){
          fftSmooth[i] = 0;
      }
//    ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::BOTTOM_LEFT );
//    gui->addHeader("NumPadz");


    sounds = {snd1,snd2,snd3,snd4,snd5,snd6,snd7,snd8,snd9};
    loadPack();
    volTog.addListener(this, &ofApp::resetVol);
    pitTog.addListener(this, &ofApp::resetPitch);
    loadLoopBtn.addListener(this, &ofApp::loadLoop);

    volumes.setup("Sampler:");
    volumes.add(soundpack);
    volumes.add(vol1.setup("Snd 1 Vol", 0.8, 0, 1));
    volumes.add(pit1.setup("Snd 1 Pitch", defaultPitch, minPitch, maxPitch));
    volumes.add(vol2.setup("Snd 2 Vol", 0.8, 0, 1));
    volumes.add(pit2.setup("Snd 2 Pitch", defaultPitch, minPitch, maxPitch));
    volumes.add(vol3.setup("Snd 3 Vol", 0.8, 0, 1));
    volumes.add(pit3.setup("Snd 3 Pitch", defaultPitch, minPitch, maxPitch));
    volumes.add(vol4.setup("Snd 4 Vol", 0.8, 0, 1));
    volumes.add(pit4.setup("Snd 4 Pitch", defaultPitch, minPitch, maxPitch));
    volumes.add(vol5.setup("Snd 5 Vol", 0.8, 0, 1));
    volumes.add(pit5.setup("Snd 5 Pitch", defaultPitch, minPitch, maxPitch));
    volumes.add(vol6.setup("Snd 6 Vol", 0.8, 0, 1));
    volumes.add(pit6.setup("Snd 6 Pitch", defaultPitch, minPitch, maxPitch));
    volumes.add(vol7.setup("Snd 7 Vol", 0.8, 0, 1));
    volumes.add(pit7.setup("Snd 7 Pitch", defaultPitch, minPitch, maxPitch));
    volumes.add(vol8.setup("Snd 8 Vol", 0.8, 0, 1));
    volumes.add(pit8.setup("Snd 8 Pitch", defaultPitch, minPitch, maxPitch));
    volumes.add(vol9.setup("Snd 9 Vol", 0.8, 0, 1));
    volumes.add(pit9.setup("Snd 9 Pitch", defaultPitch, minPitch, maxPitch));
    volumes.add(volTog.setup("Reset Volumes"));
    volumes.add(pitTog.setup("Reset Pitches"));

    menu.setup("Menu");
    menu.setPosition(700,100);
    menu.add(loadLoopBtn.setup("load loop"));


}


void ofApp::loadLoop(){
//    if (!loadDialog.isThreadRunning())   {
//        loadDialog.startThread();
//    }

    ofFileDialogResult result = ofSystemLoadDialog("Load .loop setting file");
    if(result.bSuccess) {
        string path = result.getPath();
        if (path.substr(path.find_last_of(".")+1) == "loop") {
            if(Loop::count != 10){
                ifstream input(path);
                string wav;
                float vol,pit, trim;
                input >> wav >> vol >> pit >> trim;

                Loop* newLoop = new Loop();
                Loop::loops.push_back(newLoop);
                newLoop->setup(wav);
                newLoop->snd.setVolume(vol);
                newLoop->volume = vol;
                newLoop->pitch = pit;
                newLoop->trim = trim;

                newLoop->play();
            } else {cout << "invalid file - must be a .loop file"<< endl;}
        }
    }
 }

void ofApp::resetVol(){
    for (int i = 0; i < 9; i++){
       vol1 = 0.8;vol2 = 0.8;vol3 = 0.8;vol4 = 0.8;vol5 = 0.8;vol6 = 0.8;vol7 = 0.8;vol8 = 0.8;vol9 = 0.8;
    }
}

void ofApp::resetPitch(){
    pit1 = 1; pit2 = 1; pit3 = 1; pit4 = 1; pit5 = 1; pit6 = 1; pit7 = 1; pit8 = 1; pit9 = 1;
}


//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
      float * value = ofSoundGetSpectrum(bands);
      for (int i = 0; i < bands; i++){
          fftSmooth[i] *= 0.9f;
          if (fftSmooth[i] < value[i]){
              fftSmooth[i] = value[i];
          }
      }

}

//--------------------------------------------------------------
void ofApp::draw(){
    menu.draw();
    volumes.draw();
    //set volume to what is on the slider...
    snd1.setVolume(vol1);
    snd2.setVolume(vol2);
    snd3.setVolume(vol3);
    snd4.setVolume(vol4);
    snd5.setVolume(vol5);
    snd6.setVolume(vol6);
    snd7.setVolume(vol7);
    snd8.setVolume(vol8);
    snd9.setVolume(vol9);
    //im just trying to be a good boy and add comments
    snd1.setSpeed(pit1);
    snd2.setSpeed(pit2);
    snd3.setSpeed(pit3);
    snd4.setSpeed(pit4);
    snd5.setSpeed(pit5);
    snd6.setSpeed(pit6);
    snd7.setSpeed(pit7);
    snd8.setSpeed(pit8);
    snd9.setSpeed(pit9);

    //draw Loop::loops if they exist


    // draw the fft resutls:
    ofSetColor(255,255,255,255);
    float time = ofGetElapsedTimef();
    float width = (float)(3*128) / bands;
    for (int i = 0;i < bands; i++){
        ofSetColor(180 + 50 * sin(i * 0.09 + time),
                   180 + 60 * sin(i * 0.051 * time),
                   180 + 50 * sin(i * 0.032 + time));
        // (we use negative height here, because we want to flip them
        // because the top corner is 0,0)
        ofDrawRectangle(50+i*width,ofGetHeight()-50,width,-(fftSmooth[i] * 100));
    }
//attempt to multi thread the latter loop of loops....
//    if(setval.isThreadRunning()==false){
//        setval.startThread();
//    }

   for (auto i : Loop::loops){

    i->box.draw();
    i->snd.setVolume(i->volume);
    i->snd.setSpeed(i->pitch);
    i->position = i->snd.getPosition();
      if(i->snd.getPosition()-i->trim >= i->trim){
          i->snd.setPosition(0.0f);
      }

  }
}

void ofApp::keyPressed(int key){
    loop = false;
    if (key == OF_KEY_RETURN){
        loop = true;

    }
    if (key == OF_KEY_BACKSPACE){
        if (Loop::loops.empty()){
        // do nothing
            cout << "can't delete a loop if no loops are playing" << endl;
        } else {
            Loop::loops.back()->snd.stop();
            Loop::loops.back()->snd.unload();
            Loop::loops.pop_back();
            Loop::count--;
        }



    }

    switch (key) {
    //shift soundpack up
    case '+':
    if (selPack < listSize-1){
        selPack++;
        loadPack();
    }
    break;
    //shift soundpack down
    case '-':
    if (selPack > 0){
        selPack--;
        loadPack();
    }
    break;
    //Remove second to last looping item
    case '=':

    break;
    //stop all sounds
    case '0':


        for (auto i : sounds){
            i.stop();
        }

        for (auto &i : Loop::loops){
            i->snd.stop();
            Loop::count = 0;
            Loop::loops = {};
        }



        resetVol();
    break;

    case '1':
    if (!snd1.isPlaying()){
        snd1.play();
    }
    break;

    case '2':
    if (!snd2.isPlaying()){
        snd2.play();
    }
    break;

    case '3':
    if (!snd3.isPlaying()){
        snd3.play();
    }
    break;

    case '4':
    if (!snd4.isPlaying()){
        snd4.play();
    }
    break;

    case '5':
    if (!snd5.isPlaying()){
        snd5.play();
    }
    break;

    case '6':
    if (!snd6.isPlaying()){
        snd6.play();
    }
    break;
    case '7':
    if (!snd7.isPlaying()){
        snd7.play();
    }
    break;

    case '8':
    if (!snd8.isPlaying()){
        snd8.play();
    }
    break;

    case '9':
    if (!snd9.isPlaying()){
        snd9.play();
    }
    break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){


    //if the loop function is triggered, we will load a new copy of the current sound to snd01, and play it from the same point
    //it's currently playing from...then we stop the original, now we store the new looping sound in a loop array of it's own...
    //this is so the loop will still play when you change sound pack...
    switch (key) {
           case '1':
           //if the loop function is triggered, we will load a new copy of the current sound to snd01, and play it from the same point
           //it's currently playing from...then we stop the original, now we store the new looping sound in a loop array of it's own...
           //this is so the loop will still play when you change sound pack...
           if(loop == true && Loop::count != 10){

                      Loop* newLoop = new Loop();
                      Loop::loops.push_back(newLoop);
                      newLoop->setup("wav/"+packlist[selPack]+"/0001.wav");
                      newLoop->snd.setPositionMS(snd1.getPositionMS());
                      newLoop->snd.setVolume(vol1);
                      newLoop->volume = snd1.getVolume();
                      newLoop->pitch = snd1.getSpeed();

                      newLoop->play();

//                //we're moving the sound to the looper panel now, updating the pitch and volume from the original sound.
//                snd01.setSpeed(pit1);
//                lp1 = snd1.getSpeed();
//                snd01.setVolume(vol1);
//                loop1 = snd1.getVolume();
           }

           snd1.stop();
           break;
           case '2':
           if(loop == true && Loop::count != 10){
               Loop* newLoop = new Loop();
               Loop::loops.push_back(newLoop);
               newLoop->setup("wav/"+packlist[selPack]+"/0002.wav");
               newLoop->snd.setPositionMS(snd2.getPositionMS());
               newLoop->snd.setVolume(vol2);
               newLoop->volume = snd2.getVolume();
              newLoop->pitch = snd2.getSpeed();
               newLoop->play();


           }
           snd2.stop();
           break;
           case '3':
           if(loop == true && Loop::count != 10){
               Loop* newLoop = new Loop();
               Loop::loops.push_back(newLoop);
               newLoop->setup("wav/"+packlist[selPack]+"/0003.wav");
               newLoop->snd.setPositionMS(snd3.getPositionMS());
               newLoop->snd.setVolume(vol3);
               newLoop->volume = snd3.getVolume();
               newLoop->pitch = snd3.getSpeed();
               newLoop->play();
           }
           snd3.stop();
           break;
           case '4':
           if(loop == true && Loop::count != 10){
               Loop* newLoop = new Loop();
               Loop::loops.push_back(newLoop);
               newLoop->setup("wav/"+packlist[selPack]+"/0004.wav");
               newLoop->snd.setPositionMS(snd4.getPositionMS());
               newLoop->snd.setVolume(vol4);
               newLoop->volume = snd4.getVolume();
               newLoop->pitch = snd4.getSpeed();
               newLoop->play();
            }
           snd4.stop();
           break;
           case '5':
           if(loop == true && Loop::count != 10){
               Loop* newLoop = new Loop();
               Loop::loops.push_back(newLoop);
               newLoop->setup("wav/"+packlist[selPack]+"/0005.wav");
               newLoop->snd.setPositionMS(snd5.getPositionMS());
               newLoop->snd.setVolume(vol5);
               newLoop->volume = snd5.getVolume();
               newLoop->pitch = snd5.getSpeed();
               newLoop->play();
           }
           snd5.stop();
           break;
           case '6':
           if(loop == true && Loop::count != 10){
               Loop* newLoop = new Loop();
               Loop::loops.push_back(newLoop);
               newLoop->setup("wav/"+packlist[selPack]+"/0006.wav");
               newLoop->snd.setPositionMS(snd6.getPositionMS());
               newLoop->snd.setVolume(vol6);
               newLoop->volume = snd6.getVolume();
               newLoop->pitch = snd6.getSpeed();;
               newLoop->play();
           }
           snd6.stop();
           break;
           case '7':
           if(loop == true && Loop::count != 10){
               Loop* newLoop = new Loop();
               Loop::loops.push_back(newLoop);
               newLoop->setup("wav/"+packlist[selPack]+"/0007.wav");
               newLoop->snd.setPositionMS(snd7.getPositionMS());
               newLoop->snd.setVolume(vol7);
               newLoop->volume = snd7.getVolume();
               newLoop->pitch = snd7.getSpeed();
               newLoop->play();
           }
           snd7.stop();
           break;
           case '8':
           if(loop == true && Loop::count != 10){
               Loop* newLoop = new Loop();
               Loop::loops.push_back(newLoop);
               newLoop->setup("wav/"+packlist[selPack]+"/0008.wav");
               newLoop->snd.setPositionMS(snd8.getPositionMS());
               newLoop->snd.setVolume(vol8);
               newLoop->volume = snd8.getVolume();
               newLoop->pitch = snd8.getSpeed();
               newLoop->play();
           }
           snd8.stop();
           break;
           case '9':
           if(loop == true && Loop::count != 10){
               Loop* newLoop = new Loop();
               Loop::loops.push_back(newLoop);
               newLoop->setup("wav/"+packlist[selPack]+"/0009.wav");
               newLoop->snd.setPositionMS(snd9.getPositionMS());
               newLoop->snd.setVolume(vol9);
               newLoop->volume = snd9.getVolume();
               newLoop->pitch = snd9.getSpeed();;
               newLoop->play();
           }

           snd9.stop();
           break;

        }

}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
