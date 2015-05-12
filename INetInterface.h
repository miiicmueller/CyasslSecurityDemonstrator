/*
 * INetInterface.h
 *
 *  Created on: 29 avr. 2015
 *      Author: root
 */

#ifndef INETINTERFACE_H_
#define INETINTERFACE_H_

#include <ctype.h>
#include <cyassl/ctaocrypt/types.h>

typedef struct sockaddr_in SOCKADDR_IN_T;

class INetInterface {
public:
	INetInterface();
	virtual ~INetInterface();

	virtual void initInterface(void) = 0;

	virtual void tcpConnect(int* sockfd, const char* ip, word16 port,
			int udp) = 0;
	virtual void tcpSocket(int* sockfd, int udp) = 0;

	virtual void build_addr(SOCKADDR_IN_T* addr, const char* peer, word16 port,
			int udp) = 0;
};

#endif /* INETINTERFACE_H_ */
