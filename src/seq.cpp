#include "seq.h"


void Seq::setup(const filesystem::path& fileName){
    if (countSeq != 4){
        ++countSeq;
        id = ID++;
        snd.load(fileName);
        snd.setLoop(true);
        snd.setMultiPlay(true);
        sampleFile = ofToString(fileName);
        this->sampleFile.erase(
            remove( this->sampleFile.begin(), this->sampleFile.end(), '\"' ),
            this->sampleFile.end()
            );
        box.setup("Seq:" +sampleFile.erase(0,4));
        box.setPosition(800,100*countSeq);
        for (int i = 0; i < 16; i++){
          //ADD MATRIX/SEQUENCER CODE.....
        }
    }
}

void Seq::delSeq(){

    snd.stop();
    snd.unload();

    cout << "this id:" << this->id <<endl;
    vector <Seq*>::iterator it;
    for ( it = seqs.begin(); it != seqs.end(); )
       if((*it)->id == this->id ){
          delete * it;
          it = seqs.erase(it);
          countSeq--;
       }
       else {
          ++it;
       }
}
void Seq::play(){
    snd.play();

}

void Seq::stop(){
    snd.stop();
}
