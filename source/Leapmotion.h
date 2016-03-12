#ifndef LEAP_MOTION_H
#define LEAP_MOTION_H

#include <iostream>
#include <string>
#include <math.h>
#include "PianoListener.h"


#include <Leap.h>

#include "Piano.h"

using namespace Leap;
using namespace std;

class Leapmotion {

	public:
		Leapmotion(Piano &p);


	private:
		Piano &piano;
		PianoListener listener;
		Controller controller;
};

#endif
