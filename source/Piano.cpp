#include "Piano.h"

void Piano::keyDown(unsigned int key)
{
	midiSink.noteOn(key, 100);
}

void Piano::keyUp(unsigned int key)
{
	midiSink.noteOff(key);
}

