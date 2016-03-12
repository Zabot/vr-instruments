#ifndef ALSA_H
#define ALSA_H

#include "MidiSink.h"

#include <portmidi.h>


class ALSA : public MidiSink
{
public:
	ALSA();
	~ALSA();
	void noteOn(unsigned int key, unsigned int vel) override;
	void noteOff(unsigned int key) override;

private:
	PortMidiStream* stream;
};

#endif
