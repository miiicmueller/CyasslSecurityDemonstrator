/*
 * main.cpp
 *
 *  Created on: 27 avr. 2015
 *      Author: root
 */
#include <unistd.h>
#include "EndDevice.h"

#define MAC_ADDR(hwaddr, a,b,c,d,e,f)  	hwaddr[0] = a;\
										hwaddr[1] = b;\
										hwaddr[2] = c;\
										hwaddr[3] = d;\
										hwaddr[4] = e;\
										hwaddr[5] = f;

int main(void) {

	ip_addr_t ipaddr, netmask, gtw;
	u8_t hw_addr[6];
	pid_t pid;

	int i = 0;

	pid = fork();

	if (pid == 0) {
//		IP4_ADDR(&gtw, 192, 168, 10, 1);
//		IP4_ADDR(&netmask, 255, 255, 255, 0);
//		IP4_ADDR(&ipaddr, 192, 168, 10, 9);
//		MAC_ADDR(hw_addr, 1, 2, 3, 4, 5, 9);
//
//		EndDevice* endDevice1 = new EndDevice(ipaddr, netmask, gtw, hw_addr);
//
//		while (1) {
//			sleep(1);
//		}

	} else {
		IP4_ADDR(&gtw, 192, 168, 11, 1);
		IP4_ADDR(&ipaddr, 192, 168, 11, 8);
		MAC_ADDR(hw_addr, 1, 2, 3, 4, 5, 8);

		EndDevice* endDevice2 = new EndDevice(ipaddr, netmask, gtw, hw_addr);
		while (1) {
			sleep(1);
		}
	}

}
