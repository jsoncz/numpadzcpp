#include "loop.h"
vector<Loop*>loops = {};

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
    ++count;
     // cout << int(count) << endl;

    if (count < 11){
        id = ID++;
        cout << id << endl;
        snd.load(fileName);
        snd.setLoop(true);
        snd.setMultiPlay(true);

        box.setup("loop" +to_string(loops.size()));

        if (count < 6){
            box.setPosition(400,75*count);
        }
        if (count >= 6){
            box.setPosition(600,75*(count-5));
        }
     //ofxDatGui* loopGui = new ofxDatGui(400,75*count);
        box.add(button.setup("delete"));
        box.add(volume.setup("volume ", 0.8, 0.1, 1));
        box.add(pitch.setup("pitch",1, 0.1, 3));
        button.addListener(this, &Loop::delLoop);
    }
}



void Loop::play(){
    snd.play();

}

//void Loop::draw(){
//    box.draw();

//
void Loop::stop(){
    snd.stop();
}
