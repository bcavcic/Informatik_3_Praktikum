/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <chrono>

#include "SIMPLESOCKET.H"
#include "TASK1.H"
#include "client.H"

using namespace std;
using namespace std::chrono;


myTCPclient::myTCPclient(string host, int port) : TCPclient(){
		gefundenesPw_ = "";
		count_ = 0;
		conn(host, port);
	}

string myTCPclient::sendMsg(string msg, bool aus){
			if(aus){	cout << "client sends:" << msg << endl;}
				sendData(msg);
				msg = receive(64);
			if(aus){	cout << "got response:" << msg << endl;}
				return msg;
	}
	
	bool myTCPclient::pw(string pwd, int l, int v){
		if(l < 1){
			count_++;
			if(sendMsg("LOG(" + pwd +")", false).find("DENIED") == std::string::npos){
				gefundenesPw_ = pwd;
				return true;
			}else{
				return false;
			}
		}else{
			for(int i = 0; i<v; i++){
				if(pw(pwd + TASK1::SYMBOLS[i], l-1, v)){
					return true;
				}
			}
		}
		return false;
	}

	string myTCPclient::passwortKnacken(int l, int v){
		string s = "NP(" + to_string(l) + string(",") + to_string(v) + string(")");
		sendMsg(s, false);
		count_ = 0;
		gefundenesPw_ = "";
					auto before = std::chrono::system_clock::now();
					
					pw("", l, v);
					
					auto after = std::chrono::system_clock::now();
		string ret ="Passwort " + gefundenesPw_ + " nach " + to_string(count_) + " Versuchen und " + to_string(duration_cast<milliseconds>(after-before).count()) + "ms gefunden!";
		timeCount_ = duration_cast<milliseconds>(after-before).count();
		return ret;
	}
	
	int myTCPclient::getCount(){
			return count_;
	}
	int myTCPclient::getTimeCount(){
				return timeCount_;
		}

