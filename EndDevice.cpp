/*
 * EndDevice.cpp
 *
 *  Created on: 27 avr. 2015
 *      Author: root
 */

#include "EndDevice.h"
#include <cyassl/ctaocrypt/settings.h>
#include <cyassl/openssl/ssl.h>
//#include <cyassl/test.h>
#include <ctype.h>
#include <cyassl/ctaocrypt/types.h>

#define caCert     "./certs/ca-cert.pem"

/* yaSSL */
static const char* const yasslIP = "157.26.100.100";
static const word16 yasslPort = 11111;

EndDevice::EndDevice(ip_addr_t ipaddr, ip_addr_t netmask, ip_addr_t gateway,
		u8_t *hwaddr) {

	// Set the network interface
	this->setNetInterface(
			(INetInterface*) new LwipNetInterface(ipaddr, netmask, gateway,
					hwaddr));

	this->initPlatform();

	this->setupApp();
	this->runApp();
}

EndDevice::~EndDevice() {
}

bool EndDevice::initPlatform(void) {

	INetInterface* netInterface;

	// Init the lwip stack
	netInterface = this->getNetInterface();
	netInterface->initInterface();

	return false;
}

/**
 * This is the main programme running on the end device
 */

void EndDevice::setupApp(void) {
	LWIP_PLATFORM_DIAG(("Application setup\n"));
	return;
}

void EndDevice::runApp(void) {

	SSL_METHOD* method = 0;
	SSL_CTX* ctx = 0;
	SSL* ssl = 0;
	int sockfd = 0;
	word16 port = yasslPort;

	INetInterface* netInterface;


	LWIP_PLATFORM_DIAG(("Running main application\n"));

	method = SSLv3_client_method();
	ctx = SSL_CTX_new(method);

	if (SSL_CTX_load_verify_locations(ctx, caCert, 0) != SSL_SUCCESS)
		LWIP_PLATFORM_DIAG(
				("can't load ca file, Please run from CyaSSL home dir"));

	ssl = SSL_new(ctx);

	//Retreive our network interface
	netInterface = this->getNetInterface();

	netInterface->tcpConnect(&sockfd, yasslIP, port, 0);
	SSL_set_fd(ssl, sockfd);

	return;
}
