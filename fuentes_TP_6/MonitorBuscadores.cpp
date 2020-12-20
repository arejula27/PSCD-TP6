//-------------------------------------------------------------------------------------------
// File:   MonitorRecursos.cpp
// Author: Héctor Bara (778097) y Sergio Hernández (758723)
// Date:   14/12/2020
// Coms:   Fichero de implementacion del Monitor
//-------------------------------------------------------------------------------------------

#include <MonitorBuscadores.hpp>

#include <iostream>
using namespace std;


MonitorBuscadores:: MonitorBuscadores(){
	this->conectados = 0;
}


MonitorBuscadores::~MonitorBuscadores() {}


void MonitorBuscadores::aumentarBuscadores(){
	unique_lock<mutex> lck(mtx);
	while(conectados==8){
		esperoBuscadores.wait(lck);
	}
	this->conectados++;
}

void MonitorBuscadores::disminuirBuscadores(){
	unique_lock<mutex> lck(mtx);
	this->conectados--;
	if(conectados==7){
		esperoBuscadores.notify_one();  //Si falla probar con notify_all()
	}
}

int MonitorBuscadores::actBuscadores(){
	return conectados;
}
















