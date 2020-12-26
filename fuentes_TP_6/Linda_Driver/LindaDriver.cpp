//*****************************************************************
// File:   LindaDriver.cpp
// Author: PSCD-Unizar
// Date:   Diciembre 2020
// Coms:   Especificación de la clase
//*****************************************************************

#include <cassert>
#include <string>
#include "Socket.hpp"
#include "LindaDriver.hpp"
 
    LindaDriver::LindaDriver(string ip, int puerto){
		this->puerto = puerto;
		this->ip = ip;
    }
	//destructor -----------------------------
	LindaDriver::~LindaDriver(){
			
    }
	//operadores -----------------------------

	//PostNote
	void LindaDriver::PN(const Tupla t){
		Tupla tup(t);
		string mensaje=to_string(tup.size());
		int puertodev;
		string ipdev;
		auxiliarConRD(mensaje,ip,puerto,ipdev,puertodev);
		Socket chan(ipdev, puertodev);
		int socket_fd=chan.Connect();
		string mensTup ="PN" + mensaje; //PN1
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "OK PN"){
			cerr << "Error recv" << endl;
			exit(1);
		}
		mensTup=tup.to_string();
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "TERMINADO"){
			cerr << "Error final" << endl;
			exit(1);
		}
		chan.Close(socket_fd);
    }

	//Pre:  "p" y "t" tienen el mismo tamaño
	//Post: Remove Note, siendo "p" el patrón y "t" la tupla
	void LindaDriver::RN(const Tupla p, Tupla& t){
        Tupla tup(p);
		string mensaje=to_string(tup.size());
		int puertodev;
		string ipdev;
		auxiliarConRD(mensaje,ip,puerto,ipdev,puertodev);
		Socket chan(ipdev, puertodev);
		int socket_fd=chan.Connect();
		string mensTup ="RN" + mensaje; 
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "OK RN"){
			cerr << "Error recv" << endl;
			exit(1);
		}
		mensTup=tup.to_string();
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		//hasta aqui bien
		

		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "TERMINADO"){
			cerr << "Error final" << endl;
			exit(1);
		}
		chan.Close(socket_fd);
    }

	//Pre:  "p1" y "t1" tienen el mismo tamaño
	//      "p2" y "t2" tienen el mismo tamaño
	//Post: Remove Notes, siendo "p1" y "p2" los patrones y "t1" y "t2" las tuplas
	void LindaDriver::RN_2(const Tupla p1, const Tupla p2, Tupla& t1, Tupla& t2){
        Tupla tup(t1);
		string mensaje=to_string(tup.size());
		int puertodev;
		string ipdev;
		auxiliarConRD(mensaje,ip,puerto,ipdev,puertodev);
		Socket chan(ipdev, puertodev);
		int socket_fd=chan.Connect();
		string mensTup ="RN_2" + mensaje; //RN_2
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "OK RN_2"){
			cerr << "Error recv" << endl;
			exit(1);
		}
		mensTup=tup.to_string();
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "TERMINADO"){
			cerr << "Error final" << endl;
			exit(1);
		}
		chan.Close(socket_fd);
    }

	//Pre:  "p" y "t" tienen el mismo tamaño
	//Post: ReaD Note, siendo "p" el patrón y "t" la tupla
	void LindaDriver::RDN(const Tupla p, Tupla& t){
        Tupla tup(t);
		string mensaje=to_string(tup.size());
		int puertodev;
		string ipdev;
		auxiliarConRD(mensaje,ip,puerto,ipdev,puertodev);
		Socket chan(ipdev, puertodev);
		int socket_fd=chan.Connect();
		string mensTup ="RDN" + mensaje; //RDN1
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "OK RDN"){
			cerr << "Error recv" << endl;
			exit(1);
		}
		mensTup=tup.to_string();
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "TERMINADO"){
			cerr << "Error final" << endl;
			exit(1);
		}
		chan.Close(socket_fd);
    }

	//Pre:  "p1" y "t1" tienen el mismo tamaño
	//      "p2" y "t2" tienen el mismo tamaño
	//Post: ReaD Notes, siendo "p1" y "p2" los patrones y "t1" y "t2" las tuplas
	void LindaDriver::RDN_2(const Tupla p1, const Tupla p2, Tupla& t1, Tupla& t2){
        Tupla tup(t1);
		string mensaje=to_string(tup.size());
		int puertodev;
		string ipdev;
		auxiliarConRD(mensaje,ip,puerto,ipdev,puertodev);
		Socket chan(ipdev, puertodev);
		int socket_fd=chan.Connect();
		string mensTup ="RDN_2" + mensaje; //RN1
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "OK RDN_2"){
			cerr << "Error recv" << endl;
			exit(1);
		}
		mensTup=tup.to_string();
		int send_bytes = chan.Send(socket_fd, mensTup);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		int read_bytes = chan.Recv(socket_fd, mensTup, 1024);
		if(read_bytes<0 || mensTup != "TERMINADO"){
			cerr << "Error final" << endl;
			exit(1);
		}
		chan.Close(socket_fd);
    }

	//Conexion con registro de despliegue
	void LindaDriver::auxiliarConRD(string mensaje, string ip, int puerto, string& ipdev, int& puertodev){
		Socket chan(ip, puerto);
		int socket_fd = chan.Connect();
    	int send_bytes = chan.Send(socket_fd, mensaje);
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
		string buffer;
		int read_bytes = chan.Recv(socket_fd, buffer, 1024);
		if(read_bytes<0){
			cerr << "Error recv" << endl;
			exit(1);
		}
		ipdev=buffer;
		read_bytes = chan.Recv(socket_fd, buffer, 1024);
		if(read_bytes<0){
			cerr << "Error recv" << endl;
			exit(1);
		}
		puertodev=stoi(buffer);
	}