#include "ALSA.h"

#include <iostream>

using namespace std;

ALSA::ALSA()
{
	PmDeviceID id = 0;
	long buffer = 0L;
	long latency = 0L;
	Pm_Initialize();
	Pm_OpenOutput(&stream, id, NULL, buffer, NULL, nullptr, latency);
}

ALSA::~ALSA()
{
	Pm_Close(stream);
	Pm_Terminate();
}

void ALSA::noteOn(unsigned int key, unsigned int vel)
{
	cout << "Start " << key << ":" << vel << endl;

	int channel = 0;
	long message = Pm_Message(0x90 | channel, key, vel);

	Pm_WriteShort(stream, 1L, message);
}

void ALSA::noteOff(unsigned int key)
{

	cout << "End " << key << endl;

	int channel = 0;
	long message = Pm_Message(0x80 | channel, key, 0x00);

	Pm_WriteShort(stream, 0L, message);
}
