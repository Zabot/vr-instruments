#include "Guitar.h"

Guitar::Guitar(MidiSink &sink)
	:sink(sink)
{
	frets = new unsigned int[6];
}

Guitar::~Guitar
{
	delete[] frets;
}

void fret(unsigned int string, unsigned int fret)
{
	frets[string] = fret;
}

void strum()
{
	for(unsigned int i = 0; i < 6; i++)
	{
		pick(i);
	}
}

void pick(unsigned int string)
{
	sink.noteOn(getnote(string, frets[string]), 64);
	sink.noteOff(getnote(string, frets[string]);
}

unsigned int getNote(unsigned int string, unsigned int fret)
{
	
}
