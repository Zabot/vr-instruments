#pragma once
#include "stdafx.h"
#include "piano.h"
#include "Leap.h"
#include <iostream>
#include <string.h>
#include <math.h>

using namespace Leap;
using namespace std;

class Leapmotion {

	public:
		Leapmotion(Piano &p);

	private:
		Piano &piano;

};
