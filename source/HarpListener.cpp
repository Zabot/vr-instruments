#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "Leap.h"
#include <math.h>
#include "HarpListener.h"
#include <vector>

using namespace Leap;
using namespace std;

void HarpListener::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void HarpListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
	//controller.enableGesture(Gesture::TYPE_CIRCLE);
	//controller.enableGesture(Gesture::TYPE_KEY_TAP);
	//controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	//controller.enableGesture(Gesture::TYPE_SWIPE);
}

void HarpListener::onDisconnect(const Controller& controller) {
	// Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}

void HarpListener::onExit(const Controller& controller) {
	std::cout << "Exited" << std::endl;
}

void HarpListener::onFrame(const Controller& controller) {
	const Frame frame = controller.frame();

	const FingerList fingers = frame.fingers();
	std::vector<int> keysThisFrame;
	for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
		const Finger finger = *fl;
		/*		std::cout << std::string(4, ' ')
		<< " finger, id: " << finger.id()
		<< "tip position:" << finger.tipPosition()
		<< "tip velocity:" << finger.tipVelocity() << std::endl;
		*/
		const Vector position = finger.tipPosition();
		const Vector velocity = finger.tipVelocity();
		// ( position.x )
		unsigned int numOfStrings = 20;
		unsigned int maxHarpLength = 200;
		if (finger.type() != finger.TYPE_THUMB) {
			if (position.y > 100 && abs(position.z) < 100 && (abs(position.x)< 25)) {
				unsigned int stringSpace = maxHarpLength / numOfStrings;
				unsigned int theKey = (position.z + 150) / stringSpace;

				keysThisFrame.push_back(theKey);
				if (!isInVector(theKey, keysDown)) {
					keysDown.push_back(theKey);
					cout << "Key " << theKey << " is pressed down" << endl;//	piano.keyDown(theKey, finger.tipVelocity.y);
				}


				//cout << "KEY" << theKey << "  " << finger.type() << "Velocity:" << finger.tipVelocity().y << endl;
			}
		}
	}

	for (auto n = keysDown.begin(); n < keysDown.end(); n++) {

		if (!isInVector(*n, keysThisFrame)) {
			//keysDown.erase(std::remove(keysDown.begin(), keysDown.end(), *n), keysDown.end());
			cout << "Key " << *n << " is now up" << endl;
			Harp.keyUp(n-5);
		}

	}
	keysDown.clear();
	for (int n : keysThisFrame)
	{
		keysDown.push_back(n);
	}
	//for (int n : keysDown)cout << n << " ";
	//cout << endl;
	//cout << "Key" << theKey << endl;
}


bool HarpListener::isInVector(int k, vector<int> &v) {
	for (const int n : v) {
		if (n == k)return true;
	}
	return false;
}

void HarpListener::onFocusGained(const Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void HarpListener::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void HarpListener::onDeviceChange(const Controller& controller) {
	std::cout << "Device Changed" << std::endl;
	const DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "id: " << devices[i].toString() << std::endl;
		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

void HarpListener::onServiceConnect(const Controller& controller) {
	std::cout << "Service Connected" << std::endl;
}

void HarpListener::onServiceDisconnect(const Controller& controller) {
	std::cout << "Service Disconnected" << std::endl;
}