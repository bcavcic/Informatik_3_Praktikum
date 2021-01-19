//============================================================================
// Name        : INF3_Prak.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <string>
#include <iostream>

#include <cstdio>      /* printf, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include <unistd.h>

#include <thread>

#include "SHA256.H"
#include "TASK1.H"
#include "TASK2.H"
#include "TASK3.H"
#include "TASK4.H"
#include "TASK5.H"
#include "TASK6.H"
#include "client.H"
#include "server.H"
#include <chrono>

using namespace std;
using namespace TASK1;
using namespace std::chrono;

int goOn_ = 0;
bool done = false;

void startServer(int port){
	myTCPserver srv(port,25);
	srv.run();
}
void startClient(myTCPclient* c, int l, int v, string id){
	cout << "Client " + id + ": " + c->passwortKnacken(l,v) << endl;
	goOn_++;
}

int main(int argc, char *argv[]){
	int portbase = time(0)%2000+1000;
	int l;
	int v;
	int t;
	if(argc == 4){
		t = stoi(argv[1]);
		l = stoi(argv[2]);
		v = stoi(argv[3]);
	}
	std::string befehl;
	if(argc != 4){
	cout << "Anzahl Threads?" << endl;
	cin >> befehl;
	t = std::stoi(befehl);
	}
	
	vector<myTCPclient> clients;
	
	for(int i = 0; i< t; i++){
		std::thread server(startServer,(portbase+i));
		server.detach();
	}
	sleep(1);
	for(int i = 0; i< t; i++){
		myTCPclient c("localhost",(portbase+i));
		clients.push_back(c);
	}
	
	cout << endl;
	cout << to_string(t) + " Clients und Server auf Port " + to_string(portbase) + " bis " + to_string(portbase+t) + " gestartet!" <<endl;	
	
	while(!done){
	goOn_ = 0;
	
	if(argc != 4){
	cout << endl;
	cout << "Passwortlänge?" << endl;
	cin >> befehl;
	l = std::stoi(befehl);
	cout << "Zeichenvielfalt?" << endl;
	cin >> befehl;
	v = std::stoi(befehl);
	}
	
	for(int i = 0; i< t; i++){
		std::thread client(startClient, &clients.at(i), l, v, to_string(i));
		client.detach();
	}
	cout<< endl << "Threads gestartet!" << endl;
	
	while(goOn_<t){
		usleep(1);
	}
	
	int gesamtCount = 0;
	int gesamtZeit = 0;
	for(int i = 0; i< t; i++){
		gesamtCount = gesamtCount + clients[i].getCount();
		gesamtZeit = gesamtZeit + clients[i].getTimeCount();
	}
	cout << "Durchschnittlich " << gesamtCount/t << " Versuche!" << endl;
	cout << "Durchschnittlich " << gesamtZeit/t << " ms!" << endl;
	
	string input;
	if(argc != 4){
	cout << "Fertig?(j/n)"<<endl;
	cin >> input;
	}
	
	if(argc == 4 || input.find("j") != std::string::npos){
		done = true;
	}
	}
	
	for(int i = 0; i<t; i++){
		clients[i].sendMsg("BYEBYE", false);
	}
    return 0;
}





