/*
 * IApplication.h
 *
 *  Created on: 12 mai 2015
 *      Author: root
 */

#ifndef IAPPLICATION_H_
#define IAPPLICATION_H_

class IApplication {
public:
	IApplication();
	virtual ~IApplication();

	virtual void setupApp(void) = 0;
	virtual void runApp(void) = 0;
};


#endif /* IAPPLICATION_H_ */
