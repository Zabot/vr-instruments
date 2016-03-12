#include <iostream>
#include <string.h>
#include "Leap.h"
#include <math.h>
#include "PianoListener.h"
#include <vector>

using namespace Leap;
using namespace std;

PianoListener::PianoListener(Piano &piano) : piano(piano)
{
}

void PianoListener::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void PianoListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
}

void PianoListener::onDisconnect(const Controller& controller) {
	std::cout << "Disconnected" << std::endl;
}

void PianoListener::onExit(const Controller& controller) {
	std::cout << "Exited" << std::endl;
}

void PianoListener::onFrame(const Controller& controller) {
	// Get the most recent frame and report some basic information
	const Frame frame = controller.frame();
	const FingerList fingers = frame.fingers();
	std::vector<int> keysThisFrame;
	for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
		const Finger finger = *fl;
		const Vector position = finger.tipPosition();
		const Vector velocity = finger.tipVelocity();

		unsigned int numOfKeys = 8;
		unsigned int maxKeyboardLength = 270;
		if (finger.type() != finger.TYPE_THUMB) {
			if (position.y < 150 && abs(position.x) < 150 && (abs(position.z - 40) < 40)) {
				unsigned int keyWidth = maxKeyboardLength / numOfKeys;
				unsigned int theKey = (position.x + 150) / keyWidth;
				
				keysThisFrame.push_back(theKey);
				if (!isInVector(theKey, keysDown)) {
					keysDown.push_back(theKey);
					cout << "Key " << theKey << " is pressed down" << endl;
					piano.keyDown(theKey + 96);
				}
			}
		}
	}

	for (auto n = keysDown.begin(); n < keysDown.end(); n++) {

		if (!isInVector(*n, keysThisFrame)) {
			cout << "Key " << *n << " is now up" << endl;
			piano.keyUp(96 + *n);
		}

	}
	keysDown.clear();
	for (int n : keysThisFrame)
	{
		keysDown.push_back(n);
	}
}


bool PianoListener::isInVector(int k,vector<int> &v) {
	for (const int n : v) {
		if (n == k)return true;
	}
	return false;
}

void PianoListener::onFocusGained(const Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void PianoListener::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void PianoListener::onDeviceChange(const Controller& controller) {
	std::cout << "Device Changed" << std::endl;
	const DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "id: " << devices[i].toString() << std::endl;
		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

void PianoListener::onServiceConnect(const Controller& controller) {
	std::cout << "Service Connected" << std::endl;
}

void PianoListener::onServiceDisconnect(const Controller& controller) {
	std::cout << "Service Disconnected" << std::endl;
}
