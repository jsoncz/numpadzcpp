#include "loop.h"
#include <iostream>
#include <fstream>

vector<Loop*>loops = {};

//void Loop::saveLoop(){
//          ofstream ofs;
//          ofFileDialogResult result = ofSystemSaveDialog("loop.loop", "Save Loop Settings As:");
//          if(!result.bSuccess){

//          }
//          if(result.bSuccess) {
//              cout << "this is file:" << result.filePath << endl;
//          }
//            cout << "the fucking file name is: " << result.filePath << endl;
//            ofs.open(result.filePath);

//          this->Loop::sampleFile.erase(
//              remove( this->Loop::sampleFile.begin(), this->Loop::sampleFile.end(), '\"' ),
//              this->Loop::sampleFile.end()
//              );
//          ofs << this->sampleFile << "\n" << this->volume << "\n" << this->pitch << "\n" << this->trim;
//          ofs.close();
//    }


void Loop::delLoop(){

    snd.stop();
    snd.unload();

    cout << "this id:" << this->id <<endl;
    vector <Loop*>::iterator it;
    for ( it = loops.begin(); it != loops.end(); )
       if((*it)->id == this->id ){
          delete * it;
          it = loops.erase(it);
          count--;
       }
       else {
          ++it;
       }
}

void Loop::setup(const filesystem::path& fileName){
     // cout << int(count) << endl;
    if (count != 12){
        ++count;
        id = ID++;
        snd.load(fileName);
        snd.setLoop(true);
        snd.setMultiPlay(true);
        sampleFile = ofToString(fileName);
        this->sampleFile.erase(
            remove( this->sampleFile.begin(), this->sampleFile.end(), '\"' ),
            this->sampleFile.end()
            );
        box.setup("loop:" +sampleFile.erase(0,4));
        sampleFile = ofToString(fileName);
        if (count == 1){
             box.setPosition(250,20);
        }
        if (count == 2){
             box.setPosition(250,170);
        }
        if (count == 3){
             box.setPosition(250,320);
        }
        if (count == 4){
             box.setPosition(250,470);
        }
        if (count == 5){
             box.setPosition(500,20);
        }
        if (count == 6){
             box.setPosition(500,170);
        }
        if (count == 7){
             box.setPosition(500,320);
        }
        if (count == 8){
             box.setPosition(500,470);
        }
        if (count == 9){
             box.setPosition(750,20);
        }
        if (count == 10){
            box.setPosition(750,170);
        }
        if (count == 11){
            box.setPosition(750,320);
        }
        if (count == 12){
            box.setPosition(750,470);
        }
     //ofxDatGui* loopGui = new ofxDatGui(400,75*count);
        box.add(del.setup("delete"));
        box.add(mute.set("Mute", false));

//        box.add(save.setup("save"));
        box.add(volume.setup("volume ", 0.8, 0, 1));
        box.add(pitch.setup("pitch",1, 0.1, 3));
        box.add(trim.set("trim", 1,0,1));
        box.add(position.setup("position",0,0,1));

        effects.add(numSlices.set("Shuffler", 0, 0, 4));




        effects.setName("FX");
        box.add(effects);

        del.addListener(this, &Loop::delLoop);

//        save.addListener(this, &Loop::saveLoop);


    }
}


void Loop::play(){
    snd.play();

}

void Loop::stop(){
    snd.stop();
}
