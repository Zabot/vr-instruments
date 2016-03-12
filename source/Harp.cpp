#include "Harp.h"

#include "MidiSink.h"

using namespace std;

Harp::Harp(MidiSink &sink)
	:sink(sink)
{
}

void Harp::pluck(unsigned int string)
{
	sink.noteOn(string, 64);
	sink.noteOff(string);
}
