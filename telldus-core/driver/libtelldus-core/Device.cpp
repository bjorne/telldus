#include "Device.h"
#include "Manager.h"
#include <stdlib.h>

using namespace TelldusCore;
/*
* Constructor
*/
Device::Device(int id, const std::string m, const std::string &name)
	: deviceId(id),
		deviceName(name),
		model(m)
{
}

/*
* Destructor
*/
Device::~Device(void) {
}

std::string Device::getModel() const {
	std::string strModel = model;
	//Strip anything after : if it is found
	size_t pos = strModel.find(":");
	if (pos != std::string::npos) {	
		strModel = strModel.substr(0, pos);
	}

	return strModel;
}

std::string Device::getFullModel() const {
	return model;
}

bool Device::setModel( const std::string &strModel ) {
	Manager *manager = Manager::getInstance();
	if (manager->setDeviceModel( deviceId, strModel )) {
		model = strModel;
		return true;
	}
	return false;
}

bool Device::setParameter(const std::string &strName, const std::string &strValue) {
	if (setDeviceParameter( strName, strValue )) {
		Manager *manager = Manager::getInstance();
		return manager->setDeviceParameter(deviceId, strName, strValue);
	}
	return false;
}

/*
* Turn on, virtual
*/
int Device::turnOn(Controller *){
	return TELLSTICK_ERROR_METHOD_NOT_SUPPORTED;
}

/*
* Turn off, virtual
*/
int Device::turnOff(Controller *){
	return TELLSTICK_ERROR_METHOD_NOT_SUPPORTED;
}

/*
* Bell, virtual
*/
int Device::bell(Controller *){
	return TELLSTICK_ERROR_METHOD_NOT_SUPPORTED;
}

/*
* Dim, virtual
*/
int Device::dim(unsigned char level, Controller *){
	return TELLSTICK_ERROR_METHOD_NOT_SUPPORTED;
}

int Device::learn(Controller *controller) {
	return TELLSTICK_ERROR_METHOD_NOT_SUPPORTED;
}

int Device::methodId( const std::string &methodName ) {
	if (methodName.compare("turnon") == 0) {
		return TELLSTICK_TURNON;
	}
	if (methodName.compare("turnoff") == 0) {
		return TELLSTICK_TURNOFF;
	}
	if (methodName.compare("bell") == 0) {
		return TELLSTICK_BELL;
	}
	if (methodName.compare("dim") == 0) {
		return TELLSTICK_DIM;
	}
	return 0;
}

std::string Device::getName() const {
	return deviceName;
}

bool Device::setName(const std::string & newName) {
	Manager *manager = Manager::getInstance();
	if (manager->setDeviceName(deviceId, newName)) {
		deviceName = newName;
		return true;
	}
	return false;
}

int TelldusCore::Device::maskUnsupportedMethods(int methods, int supportedMethods) {
	// Bell -> On
	if ((methods & TELLSTICK_BELL) && !(supportedMethods & TELLSTICK_BELL)) {
		methods |= TELLSTICK_TURNON;
	}
	//Cut of the rest of the unsupported methods we don't have a fallback for
	return methods & supportedMethods;
}
