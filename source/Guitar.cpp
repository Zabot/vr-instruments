#include "Guitar.h"

#include "MidiSink.h"

Guitar::Guitar(MidiSink &sink)
	:sink(sink)
{
	frets = new unsigned int[6];
}

Guitar::~Guitar()
{
	delete[] frets;
}

void Guitar::fret(unsigned int string, unsigned int fret)
{
	frets[string] = fret;
}

void Guitar::strum()
{
	for(unsigned int i = 0; i < 6; i++)
	{
		pick(i);
	}
}

void Guitar::pick(unsigned int string)
{
	sink.noteOn(getNote(string, frets[string]), 64);
	sink.noteOff(getNote(string, frets[string]));
}

unsigned int Guitar::getNote(unsigned int string, unsigned int fret)
{
	
}
