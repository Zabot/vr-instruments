#ifndef MIDI_SINK_H
#define MIDI_SINK_H

class MidiSink
{
public:
	virtual void noteOn(unsigned int note, unsigned int vel) = 0;
	virtual void noteOff(unsigned int note) = 0;
};

#endif
