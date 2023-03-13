#include <alsa/asoundlib.h>     /* Interface to the ALSA system */
#include <unistd.h>             /* for sleep() function */


#ifndef midi_h
#define midi_h

class midi{
	public:
		char sounds[3][3] = {
		{(char)0x90, (char)0x3c, (char)0x64},
 		{(char)0x90, (char)0x24, (char)0x64},
 		{(char)0x90, (char)0x26, (char)0x64},
		};
		char silence[3][3] = {
 		{(char)0x90, (char)0x3c, (char)0x0},
 		{(char)0x90, (char)0x24, (char)0x0},
 		{(char)0x90, (char)0x26, (char)0x0},
		};

		 int status;
     int mode = SND_RAWMIDI_SYNC;
     snd_rawmidi_t* midiout = NULL;
     const char* portname = "hw:0,0";
		 /*
     char oneon[3]  = {(char)0x90, (char)0x3c, (char)0x64};
     char twoon[3]  = {(char)0x90, (char)0x24, (char)0x64}; 
     char threeon[3]  = {(char)0x90, (char)0x30, (char)0x64}; 
     char noteoff[3] = {(char)0x90, (char)0x3c, (char)0x64};
*/

	midi();
	~midi();
	void play(int);
	void stop(int);
};

#endif
