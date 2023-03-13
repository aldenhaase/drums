#include <iostream>
#include "midi.h"


midi::midi(){
    if ((status = snd_rawmidi_open(NULL, &midiout, portname, mode)) < 0) {
      std::cout<<"problem opening MIDI output\n";
      exit(1);
   }

  
     }
midi::~midi(){
     snd_rawmidi_close(midiout);
      midiout = NULL;   

     }
void midi::play(int sound){
       if ((status = snd_rawmidi_write(midiout, sounds[sound], sizeof(sounds[sound]))) < 0) {
      std::cout<<"midi write error"<<'\n';
      exit(1);
   }

      }

void midi::stop(int sound){
    snd_rawmidi_write(midiout,silence[sound], sizeof(sounds[sound]));
      }


///////////////////////////////////////////////////////////////////////////

