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
    }

	//Pre:  "p" y "t" tienen el mismo tamaño
	//Post: Remove Note, siendo "p" el patrón y "t" la tupla
	void LindaDriver::RN(const Tupla p, Tupla& t){
        
    }

	//Pre:  "p1" y "t1" tienen el mismo tamaño
	//      "p2" y "t2" tienen el mismo tamaño
	//Post: Remove Notes, siendo "p1" y "p2" los patrones y "t1" y "t2" las tuplas
	void LindaDriver::RN_2(const Tupla p1, const Tupla p2, Tupla& t1, Tupla& t2){
        
    }

	//Pre:  "p" y "t" tienen el mismo tamaño
	//Post: ReaD Note, siendo "p" el patrón y "t" la tupla
	void LindaDriver::RDN(const Tupla p, Tupla& t){
        
    }

	//Pre:  "p1" y "t1" tienen el mismo tamaño
	//      "p2" y "t2" tienen el mismo tamaño
	//Post: ReaD Notes, siendo "p1" y "p2" los patrones y "t1" y "t2" las tuplas
	void LindaDriver::RDN_2(const Tupla p1, const Tupla p2, Tupla& t1, Tupla& t2){
        
    }

	//Conexion con registro de despliegue
	void LindaDriver::auxiliarConRD(string mensaje, string ip, int puerto, string& ipdev, int& puertodev){
		Socket chan(ip, puerto);
		int socket_fd;
    	int send_bytes = chan.Send(socket_fd, mensaje);
		string buffer;
		int read_bytes = chan.Recv(socket_fd, buffer, 1024);
		ipdev=buffer;
		read_bytes = chan.Recv(socket_fd, buffer, 1024);
		puertodev=stoi(buffer);
	}