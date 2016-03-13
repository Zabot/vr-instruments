#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "Leap.h"
#include <math.h>
#include "PianoListener.h"
#include <vector>
#include "SignListener.h"

const std::string fingerNames[] = { "Thumb", "Index", "Middle", "Ring", "Pinky" };
const std::string boneNames[] = { "Metacarpal", "Proximal", "Middle", "Distal" };

using namespace Leap;
using namespace std;

void SignListener::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void SignListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
	//controller.enableGesture(Gesture::TYPE_CIRCLE);
	//controller.enableGesture(Gesture::TYPE_KEY_TAP);
	//controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	//controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SignListener::onDisconnect(const Controller& controller) {
	// Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}

void SignListener::onExit(const Controller& controller) {
	std::cout << "Exited" << std::endl;
}

void SignListener::onFrame(const Controller& controller) {
	// Get the most recent frame and report some basic information
	const Frame frame = controller.frame();

	HandList hands = frame.hands();
	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
		// Get the first hand
		const Hand hand = *hl;
		const FingerList fingers = hand.fingers();
		std::vector<int> keysThisFrame;
		unsigned int extendedFingers = 0;
		Finger fingersOnHand[5];

		cout << "Extended Fingers: ";
		for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {	
			const Finger finger = *fl;
			fingersOnHand[finger.type()]=finger;
			if (finger.isExtended()) {
				extendedFingers++;
				cout << fingerNames[finger.type()] << " ";
			}
		}
		cout << extendedFingers << endl;
		if (extendedFingers == 5) cout << "-";
		else if (fingersOnHand[3].isExtended()) {
			if (fingersOnHand[1].isExtended()) {
				if (fingersOnHand[4].isExtended()) cout << "B";
				else cout << "W";
			}
			else cout << "F";
		}
		else if(fingersOnHand[4].isExtended()) {
			if (fingersOnHand[0].isExtended()) cout << "Y";
				else if (fingersOnHand[4].tipVelocity().magnitude() < 125)cout << "I";
				else cout << "J";
		}
		else if (fingersOnHand[0].isExtended()) {
			if (fingersOnHand[1].isExtended())cout << "L";
			else cout << "A";
		}
		else if (fingersOnHand[2].isExtended()) {
			if (fingersOnHand[1].tipPosition().distanceTo(fingersOnHand[2].tipPosition()) < fingersOnHand[1].bone(Bone::TYPE_DISTAL).length()*2) {
				if (abs(fingersOnHand[1].direction().normalized().dot(Vector::left()))>.75) cout << "H"; 
				else if (fingersOnHand[1].direction().cross(fingersOnHand[2].direction()).magnitude() < .2)cout << "U";
					else cout << "R";
			}	
			else if (fingersOnHand[0].tipPosition().distanceTo(fingersOnHand[3].tipPosition()) < fingersOnHand[0].tipPosition().distanceTo(fingersOnHand[1].bone(Bone::TYPE_PROXIMAL).prevJoint()))
					cout << "V";
				else cout << "K";
			}
		else if (fingersOnHand[1].isExtended()) {
			cout << fingersOnHand[1].direction().normalized().cross(fingersOnHand[2].direction().normalized()).magnitude() << endl;
			if (fingersOnHand[1].direction().normalized().cross(fingersOnHand[2].direction().normalized()).magnitude()>.8) cout << "P";
			else {
				const Vector direction = fingersOnHand[1].direction();
				if (abs(direction.z) > abs(direction.x)) {
					if (direction.z < 0) {
						if (fingersOnHand[4].tipVelocity().magnitude() < 125) cout << "D";
						else cout << "Z";
					}
					else cout << "Q";
				}
				else if (direction.x < 0)cout << "G";
			}
		}
		else //////////////MMMMM NNNNNNN TTTTTTT
		{			
		    const float angle1= fingersOnHand[2].bone(Bone::TYPE_DISTAL).direction().angleTo(fingersOnHand[2].bone(Bone::TYPE_INTERMEDIATE).direction());
			const float angle2= fingersOnHand[2].bone(Bone::TYPE_INTERMEDIATE).direction().angleTo(fingersOnHand[2].bone(Bone::TYPE_PROXIMAL).direction());
			if (abs(angle1 - 1.4) < .2&& abs(angle2 - 1.4) < .2) cout << "E";
			else
			{
				const float angle3 = fingersOnHand[1].bone(Bone::TYPE_DISTAL).direction().angleTo(fingersOnHand[1].bone(Bone::TYPE_INTERMEDIATE).direction());
				const float angle4 = fingersOnHand[1].bone(Bone::TYPE_INTERMEDIATE).direction().angleTo(fingersOnHand[1].bone(Bone::TYPE_PROXIMAL).direction());
				cout << angle3 << " " << angle4 << endl;
				if (abs(angle3 - .7) < .2&& abs(angle4 - 1.0) < .2) cout << "X";
				else if (fingersOnHand[0].tipPosition().distanceTo(fingersOnHand[2].bone(Bone::TYPE_DISTAL).prevJoint()) < fingersOnHand[2].bone(Bone::TYPE_DISTAL).length()) cout << "S";
				else if (fingersOnHand[0].tipPosition().distanceTo(fingersOnHand[1].tipPosition()) < 30) cout << "O";
				else if (abs(angle1 - .8) < .4&& abs(angle2 - 1.2) < .3) cout << "C";
			}
			


		/*	const float distance1 = fingersOnHand[1].bone(Bone::TYPE_PROXIMAL).nextJoint().distanceTo(fingersOnHand[2].bone(Bone::TYPE_PROXIMAL).nextJoint());
			const float distance2 = fingersOnHand[2].bone(Bone::TYPE_PROXIMAL).nextJoint().distanceTo(fingersOnHand[3].bone(Bone::TYPE_PROXIMAL).nextJoint());
			const float distance3 = fingersOnHand[3].bone(Bone::TYPE_PROXIMAL).nextJoint().distanceTo(fingersOnHand[4].bone(Bone::TYPE_PROXIMAL).nextJoint());
			if (distance3 > distance1 &&distance3>distance2)cout << "M";
			else if (distance2 > distance1 &&distance2 > distance3)cout << "N";
			else if (distance1 > distance2&&distance1 > distance3)cout << "T";
		*/
		//	else if (fingersOnHand[1].tipPosition().distanceTo(fingersOnHand[0].tipPosition()) < fingersOnHand[1].bone(Bone::TYPE_PROXIMAL).length())/////ABST
		//		cout << "O";



		}
		cout << endl;
	}
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

void SignListener::onFocusGained(const Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void SignListener::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void SignListener::onDeviceChange(const Controller& controller) {
	std::cout << "Device Changed" << std::endl;
	const DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "id: " << devices[i].toString() << std::endl;
		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

void SignListener::onServiceConnect(const Controller& controller) {
	std::cout << "Service Connected" << std::endl;
}

void SignListener::onServiceDisconnect(const Controller& controller) {
	std::cout << "Service Disconnected" << std::endl;
}