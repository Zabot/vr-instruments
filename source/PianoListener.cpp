#include <iostream>
#include <string.h>
#include "Leap.h"
#include <math.h>
#include "PianoListener.h"
#include <vector>

using namespace Leap;
using namespace std;

void PianoListener::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void PianoListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
	//controller.enableGesture(Gesture::TYPE_CIRCLE);
	//controller.enableGesture(Gesture::TYPE_KEY_TAP);
	//controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	//controller.enableGesture(Gesture::TYPE_SWIPE);
}

void PianoListener::onDisconnect(const Controller& controller) {
	// Note: not dispatched when running in a debugger.
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
					piano.keyDown(theKey + 64);
				}
			}
		}
	}

	for (auto n = keysDown.begin(); n < keysDown.end(); n++) {

		if (!isInVector(*n, keysThisFrame)) {
			cout << "Key " << *n << " is now up" << endl;
			piano.keyUp(theKey + *n);
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

/** Get gestures
const GestureList gestures = frame.gestures();
for (int g = 0; g < gestures.count(); ++g) {
Gesture gesture = gestures[g];

switch (gesture.type()) {
case Gesture::TYPE_CIRCLE:
{
CircleGesture circle = gesture;
std::string clockwiseness;

if (circle.pointable().direction().angleTo(circle.normal()) <= PI / 2) {
clockwiseness = "clockwise";
}
else {
clockwiseness = "counterclockwise";
}

// Calculate angle swept since last frame
float sweptAngle = 0;
if (circle.state() != Gesture::STATE_START) {
CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
}
std::cout << std::string(2, ' ')
<< "Circle id: " << gesture.id()
<< ", state: " << stateNames[gesture.state()]
<< ", progress: " << circle.progress()
<< ", radius: " << circle.radius()
<< ", angle " << sweptAngle * RAD_TO_DEG
<< ", " << clockwiseness << std::endl;
break;
}
case Gesture::TYPE_SWIPE:
{
SwipeGesture swipe = gesture;
std::cout << std::string(2, ' ')
<< "Swipe id: " << gesture.id()
<< ", state: " << stateNames[gesture.state()]
<< ", direction: " << swipe.direction()
<< ", speed: " << swipe.speed() << std::endl;
break;
}
case Gesture::TYPE_KEY_TAP:
{
KeyTapGesture tap = gesture;
std::cout << std::string(2, ' ')
<< "Key Tap id: " << gesture.id()
<< ", state: " << stateNames[gesture.state()]
<< ", position: " << tap.position()
<< ", direction: " << tap.direction() << std::endl;
break;
}
case Gesture::TYPE_SCREEN_TAP:
{
ScreenTapGesture screentap = gesture;
std::cout << std::string(2, ' ')
<< "Screen Tap id: " << gesture.id()
<< ", state: " << stateNames[gesture.state()]
<< ", position: " << screentap.position()
<< ", direction: " << screentap.direction() << std::endl;
break;
}
default:
std::cout << std::string(2, ' ') << "Unknown gesture type." << std::endl;
break;
}
}

if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
std::cout << std::endl;
}
*/

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
