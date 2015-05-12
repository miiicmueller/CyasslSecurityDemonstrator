/*
 * PlatformDevice.cpp
 *
 *  Created on: 27 avr. 2015
 *      Author: root
 */

#include "IPlatformDevice.h"
#include "lwip/init.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/tcpip.h"
#include "lwip/netif.h"
#include "lwip/stats.h"
#include "lwip/sockets.h"
#include "netif/tapif.h"
#include "lwip/ip_addr.h"


IPlatformDevice::~IPlatformDevice()
{

}


void IPlatformDevice::setNetInterface(INetInterface* networkInterface)
{
	this->networkInterface = networkInterface;
}

INetInterface* IPlatformDevice::getNetInterface(void)
{
	return this->networkInterface;
}
