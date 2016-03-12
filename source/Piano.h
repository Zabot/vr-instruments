#ifndef PIANO_H
#define PIANO_H

#include "MidiSink.h"

class Piano
{
public:
	void keyDown(unsigned int key);
	void keyUp(unsigned int key);

private:
	MidiSink& midiSink;
};

#endif
