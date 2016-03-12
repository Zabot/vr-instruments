#include "ALSA.h"

#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
	ALSA output;
	for(unsigned int n = 0; n < 3; n++)
	{
		for(unsigned int i = 0; i < 3; i++)
		{
			output.noteOn(72,127);
			output.noteOn(76,127);
			output.noteOn(79,127);
			sleep(1);
			output.noteOff(72);
			output.noteOff(76);
			output.noteOff(79);
			output.noteOn(72,127);
			output.noteOn(76,127);
			output.noteOn(81,127);
			sleep(1);
			output.noteOff(72);
			output.noteOff(76);
			output.noteOff(81);
		}
		output.noteOn(72,127);
		output.noteOn(76,127);
		output.noteOn(79,127);
		sleep(2);
		output.noteOff(72);
		output.noteOff(76);
		output.noteOff(79);
	}
}
