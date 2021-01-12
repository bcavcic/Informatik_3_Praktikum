/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time
#include <iostream>

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "TASK1.H"
using namespace TASK1;

class myTCPserver : public TCPserver{
public:
	myTCPserver(int portNmb, int  maxDataSizeRcv) : TCPserver(portNmb, maxDataSizeRcv){
		box_ = nullptr;
	}
protected:
	string myResponse(string input);
	BlackBoxUnsafe *box_;
};

string myTCPserver::myResponse(string input){
	std::string ret = "";
	ret.clear();
	std::string p = "";
	p.clear();
	std::string p1 = "";
	p1.clear();
	std::string p2 = "";
	p1.clear();
	std::string befehl = input;
	if(input.find("(") != std::string::npos){
		befehl.clear();
		befehl = input.substr(0, input.find("("));
		p.clear();
		p = input.substr(input.find("(")+1, input.find(")")-1);
		p1.clear();
		p2.clear();
		p1 = p.substr(0, p.find(","));
		p2 = p.substr(p.find(",")+1, p.length());
	}

	if(befehl == "LOG"){
		if(box_!=nullptr){
			ret = "login mit |" + p + "| -> " + box_->input(p);
		}
	}
	else if(befehl == "NP"){
		if(p1!=""&&p2!=""){
			if(box_ != nullptr){
				delete box_;
			}
			box_ = new BlackBoxUnsafe(std::stoi(p1), std::stoi(p2));
			ret="Neues Passwort erstellt mit den Parametern: " + p1 + ", " + p2;
		}else{
			ret="Parameter falsch!";
		}

	}else if(befehl == "GP" || input.find("GetPasswort")!=std::string::npos){
		ret = "Das generierte Passwort lautet: " + box_->pwd_;
	}else{
		ret = "Befehl " + befehl + " unbekannt";
	}
	return ret + "\n";
}


int main(){
	srand(time(nullptr));
	cout << "Port?"<<endl;
	std::string port;
	cin >> port;

	int portint =2022;
	try{
		portint= std::stoi(port);
	}catch(...){

	}
	cout << "Server mit Port " << portint << " wird gestartet!" << endl;
	myTCPserver srv(2022,25);
	srv.run();
}
