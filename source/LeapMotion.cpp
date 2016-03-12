#include "LeapMotion.h"

#include "stdafx.h"
#include "Leapmotion.h"

Leapmotion::Leapmotion(Piano &p):piano(p) {
	controller.addListener(listener);
}

Leapmotion::~Leapmotion() {
	controller.removeListener(listener);
}
