/*
 * client.H
 *
 *  Created on: 10.09.2019
 *      Author: aml
 */

/**
 *
 * \file client.H
 *
 * \brief Contains the definition of the classes
 * for a TCP/IP client.
 *
 */

#ifndef client_H_
#define client_H_

#include "SIMPLESOCKET.H"
#include "TASK1.H"

class myTCPclient : public TCPclient{
public:
	myTCPclient(string host, int port);
	string passwortKnacken(int l, int v);
	string sendMsg(string msg, bool aus);
	int getCount();
protected:
	int count_;
	string gefundenesPw_;
	bool pw(string pwd, int l, int v);
};


#endif 
