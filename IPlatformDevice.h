/*
 * PlatformDevice.h
 *
 *  Created on: 27 avr. 2015
 *      Author: root
 */

#ifndef PLATFORMDEVICE_H_
#define PLATFORMDEVICE_H_

#include "INetInterface.h"

class IPlatformDevice {
public:
	// Plateform initialization
	virtual ~IPlatformDevice();
	virtual bool initPlatform(void) = 0;

	void setNetInterface(INetInterface* networkInterface);
	INetInterface* getNetInterface(void);


private:
	INetInterface* networkInterface;
};

#endif /* PLATFORMDEVICE_H_ */
