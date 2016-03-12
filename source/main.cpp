#include "ALSA.h"
#include "Piano.h"
#include "PianoListener.h"
#include "LeapMotion.h"

#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
	ALSA output;
	Piano piano(output);
	PianoListener listener(piano);

	LeapMotion leap(listener);

	// Block until user inputs something
	int x;
	cin >> x;
}

