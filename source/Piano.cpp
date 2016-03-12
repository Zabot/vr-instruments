#include "Piano.h"

Piano::Piano(MidiSink &output)
	:sink(output)
{
}

void Piano::keyDown(unsigned int key, unsigned int vel)
{
	sink.noteOn(key, vel);
}

void Piano::keyUp(unsigned int key)
{
	sink.noteOff(key);
}

