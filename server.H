/*
 * client.H
 *
 *  Created on: 10.09.2019
 *      Author: aml
 */

/**
 *
 * \file server.H
 *
 * \brief Contains the definition of the classes
 * for a TCP/IP client.
 *
 */

#ifndef server_H_
#define server_H_

#include "SIMPLESOCKET.H"
#include "TASK1.H"

class myTCPserver : public TCPserver{
public:
	myTCPserver(int portNmb, int  maxDataSizeRcv);
	string myResponse(string input);
protected:
	TASK1::BlackBoxUnsafe *box_ = nullptr;
};


#endif 
