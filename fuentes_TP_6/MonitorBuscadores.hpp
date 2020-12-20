//-------------------------------------------------------------------------------------------
// File:   MonitorTren.hpp
// Author: Héctor Bara (778097) y Sergio Hernández (758723)
// Date:   14/12/2020
// Coms:   Fichero de especificación del Monitor
//-------------------------------------------------------------------------------------------

 #ifndef MONITOR_BUSCADORES_HPP
 #define MONITOR_BUSCADORES_HPP

 #include <mutex>
 #include <condition_variable>

//-----------------------------------------------------
using namespace std; //mutex, condition_variable, etc.

class MonitorBuscadores {

//Operaciones privadas
private:

	int conectados;
	
	mutex mtx; //para la ejecución en exclusión mutua
	
	condition_variable esperoBuscadores;


	
//Operaciones públicas
public:

	 MonitorBuscadores();

	 ~MonitorBuscadores();

	 void aumentarBuscadores();
	 void disminuirBuscadores();

	 int actBuscadores();
 };

#endif 

