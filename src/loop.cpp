#include "loop.h"
#include <iostream>
#include <fstream>

vector<Loop*>loops = {};

void Loop::saveLoop(){
          ofstream ofs;
          ofFileDialogResult result = ofSystemSaveDialog("loop.loop", "Save Loop Settings As:");
          if(!result.bSuccess){

          }
          if(result.bSuccess) {
              cout << "this is file:" << result.filePath << endl;
          }
            cout << "the fucking file name is: " << result.filePath << endl;
            ofs.open(result.filePath);

          this->Loop::sampleFile.erase(
              remove( this->Loop::sampleFile.begin(), this->Loop::sampleFile.end(), '\"' ),
              this->Loop::sampleFile.end()
              );
          ofs << this->sampleFile << "\n" << this->volume << "\n" << this->pitch << "\n" << this->trim;
          ofs.close();
    }


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
    if (count < 11){
        ++count;
        id = ID++;
        cout << id << endl;
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
        if (count < 6){
            box.setPosition(400,110*count);
        }
        if (count >= 6){
            box.setPosition(610,110*(count-5));
        }
     //ofxDatGui* loopGui = new ofxDatGui(400,75*count);
        box.add(del.setup("delete"));
        box.add(save.setup("save"));
        box.add(volume.setup("volume ", 0.8, 0, 1));
        box.add(pitch.setup("pitch",1, 0.1, 3));
        box.add(trim.setup("trim", 1,0,1));
        box.add(position.setup("position",0,0,1));
        del.addListener(this, &Loop::delLoop);
        save.addListener(this, &Loop::saveLoop);

    }
}


void Loop::play(){
    snd.play();

}

void Loop::stop(){
    snd.stop();
}
