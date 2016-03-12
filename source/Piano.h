#ifndef PIANO_H
#define PIANO_H

#include "MidiSink.h"

class Piano
{
public:
	Piano(MidiSink &output);
	void keyDown(unsigned int key, unsigned int vel = 127);
	void keyUp(unsigned int key);

private:
	MidiSink& sink;
};

#endif
