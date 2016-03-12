#ifndef HARP_H
#define HAPR_H

class MidiSink;

class Harp
{
public:
	Harp(MidiSink &sink);
	void pluck(unsigned int string);

private:
	MidiSink &sink;
};

#endif
