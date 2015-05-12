/*
 * EndDevice.h
 *
 *  Created on: 27 avr. 2015
 *      Author: root
 */

#ifndef ENDDEVICE_H_
#define ENDDEVICE_H_

#include "IPlatformDevice.h"
#include "LwipNetInterface.h"
#include "IApplication.h"

class EndDevice: public IPlatformDevice, IApplication {
private:

public:
	EndDevice(ip_addr_t ipaddr, ip_addr_t netmask, ip_addr_t gateway,
			u8_t *hwaddr);
	virtual ~EndDevice();

private:
	bool initPlatform(void);

	void setupApp(void);
	void runApp(void);

};

#endif /* ENDDEVICE_H_ */
