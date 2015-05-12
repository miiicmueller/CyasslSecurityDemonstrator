/*
 * LwipNetInterface.h
 *
 *  Created on: 29 avr. 2015
 *      Author: root
 */

#ifndef LWIPNETINTERFACE_H_
#define LWIPNETINTERFACE_H_

#include "INetInterface.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
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
#include <ctype.h>
#include <cyassl/ctaocrypt/types.h>

class LwipNetInterface: public INetInterface {
private:
	// All wireless device should have these adresses (IPv4)
	ip_addr_t ipaddr;
	ip_addr_t netmask;
	ip_addr_t gateway;

	struct netif netif;

	// Useful tools
	sys_sem_t syncSem;

public:
	LwipNetInterface(ip_addr_t ipaddr, ip_addr_t netmask, ip_addr_t gateway,
			u8_t *hwaddr);
	virtual ~LwipNetInterface();

	void initInterface(void);
	void tcpConnect(int* sockfd, const char* ip, word16 port, int udp);

private:
	static void ipStackInitDone(void *pData);
	void tcpSocket(int* sockfd, int udp) ;
	void build_addr(SOCKADDR_IN_T* addr, const char* peer,
			word16 port, int udp);

};

#endif /* LWIPNETINTERFACE_H_ */
