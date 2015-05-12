/*
 * LwipNetInterface.cpp
 *
 *  Created on: 29 avr. 2015
 *      Author: root
 */

#include "LwipNetInterface.h"
#include "signal.h"
#include "lwip/debug.h"
#include "lwip/api.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" err_t tapif_init(struct netif *netif);
#endif

#define AF_INET_V    AF_INET

LwipNetInterface::LwipNetInterface(ip_addr_t ipaddr, ip_addr_t netmask,
		ip_addr_t gateway, u8_t *hwaddr) {

	// Init the IPs
	IPADDR2_COPY(&this->ipaddr, &ipaddr);
	IPADDR2_COPY(&this->netmask, &netmask);
	IPADDR2_COPY(&this->gateway, &gateway);

	memcpy(this->netif.hwaddr, hwaddr, 6);

	this->syncSem = NULL;
}

LwipNetInterface::~LwipNetInterface() {

}

void LwipNetInterface::ipStackInitDone(void *pData) {

	LwipNetInterface* lwipInterface;

	lwipInterface = (LwipNetInterface*) pData;

	LWIP_PLATFORM_DIAG(("TCP/IP stack init done\n"));

	LWIP_PLATFORM_DIAG(("netif= %p\n", &lwipInterface->netif));

	netif_set_default(
			netif_add(&lwipInterface->netif, &lwipInterface->ipaddr,
					&lwipInterface->netmask, &lwipInterface->gateway, NULL,
					tapif_init, tcpip_input));

	LWIP_PLATFORM_DIAG(("Signaling semaphore\n"));
	sys_sem_signal(&lwipInterface->syncSem);

}

void LwipNetInterface::initInterface(void) {

	LWIP_PLATFORM_DIAG(("Interface initialization\n"));

	if (sys_sem_new(&this->syncSem, 0) != ERR_OK) {
		LWIP_ASSERT("failed to create semaphore", 0);
	}
	tcpip_init(this->ipStackInitDone, this);
	sys_sem_wait(&this->syncSem);
	sys_sem_free(&this->syncSem);
}

void LwipNetInterface::build_addr(SOCKADDR_IN_T* addr, const char* peer,
		word16 port, int udp) {
	int useLookup = 0;
	(void) useLookup;
	(void) udp;

	memset(addr, 0, sizeof(SOCKADDR_IN_T));

	/* peer could be in human readable form */
	if (isalnum((int)peer[0])) {

		if (0 <= netconn_gethostbyname(peer, (ip_addr_t*)&addr->sin_addr)) {
			useLookup = 1;
		}
		else
			LWIP_ASSERT("no entry for host", 0);
	}

	addr->sin_family = AF_INET_V;
	addr->sin_port = htons(port);
	if (peer == INADDR_ANY)
		addr->sin_addr.s_addr = INADDR_ANY;
	else {
		if (!useLookup)
			addr->sin_addr.s_addr = inet_addr(peer);
	}
}

void LwipNetInterface::tcpConnect(int* sockfd, const char* ip, word16 port,
		int udp) {
	SOCKADDR_IN_T addr;
	build_addr(&addr, ip, port, udp);
	tcpSocket(sockfd, udp);

	if (!udp) {
		if (connect(*sockfd, (const struct sockaddr* )&addr, sizeof(addr))
				!= 0) {
			LWIP_ASSERT("tcp connect failed",0);
		}
	}
}

void LwipNetInterface::tcpSocket(int* sockfd, int udp) {
	if (udp)
		*sockfd = socket(AF_INET_V, SOCK_DGRAM, 0);
	else
		*sockfd = socket(AF_INET_V, SOCK_STREAM, 0);

//	if (*sockfd < 0)
//		LWIP_ASSERT("socket failed\n");

	signal(SIGPIPE, SIG_IGN);

	if (!udp) {
		int on = 1;
		socklen_t len = sizeof(on);
		int res = setsockopt(*sockfd, IPPROTO_TCP, TCP_NODELAY, &on, len);
	}
}
