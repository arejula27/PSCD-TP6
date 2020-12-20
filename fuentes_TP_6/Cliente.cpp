//*****************************************************************
// File:   Cliente.cpp
// Author: PSCD-Unizar
// Date:   noviembre 2015
// Coms:   Ejemplo de cliente con comunicación síncrona mediante sockets
//
//*****************************************************************
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include "Socket/Socket.hpp"
#include "Socket/Socket.hpp"
#include "Linda_Driver/LindaDriver.hpp"
#include "MonitorBuscadores.hpp"

using namespace std;

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres

void publicador(MonitorBuscadores& mon){

}

void buscador(MonitorBuscadores& mon){
    mon.aumentarBuscadores();

    //Hacer cosas

    mon.disminuirBuscadores();
}

void buscador_combinados(MonitorBuscadores& mon){
    mon.aumentarBuscadores();

    //Operaciones

    mon.disminuirBuscadores();
}

int main(int argc, char* argv[]){ //Parámetros invocación: $0 IP PUERTO 
    const string MENS_FIN = "SOLICITUD BAJA REGISTRO";
    // Dirección y número donde escucha el proceso servidor
    //string SERVER_ADDRESS = "155.210.154.199";
    string SERVER_ADDRESS = argv[1];
    int SERVER_PORT = atoi(argv[2]);
    srand(time(NULL));
    string buffer;


    // Creación del socket con el que se llevará a cabo
    // la comunicación con el servidor.
    Socket chan(SERVER_ADDRESS, SERVER_PORT);

    // Conectamos con el servidor. Probamos varias conexiones
    const int MAX_ATTEMPS = 10;
    int count = 0;

    int socket_fd;
    do {
        // Conexión con el servidor
        socket_fd = chan.Connect();     //¿Lo hace linda driver?
        count++;

        // Si error --> esperamos 1 segundo para reconectar
        if(socket_fd == -1) {
            this_thread::sleep_for(chrono::seconds(1));
        }
    } while(socket_fd == -1 && count < MAX_ATTEMPS);

    // Chequeamos si se ha realizado la conexión
    if(socket_fd == -1) {
        return socket_fd;
    }
    
    
    /*
        Comprobamos la cantidad de proocesos buscadores que estan efectuando la busqueda, pueden ser 8 a la vez como mucho
        Lanzamos los threads con las funciones buscador y publicadoras
    */
   
    MonitorBuscadores mon;
    thread pub[5], 
           buscS[10],
           buscComb[5] ;
    //Invocar threads
    for(int  i=0; i<5; i++){
        pub[i]=thread(&publicador,ref(mon)); //Llamamos a los publicadores
    }
    for(int  i=0; i<10; i++){
        buscS[i]=thread(&publicador,ref(mon)); //Llamamos a los buscadores
    }
    for(int  i=0; i<5; i++){
        buscComb[i]=thread(&publicador,ref(mon)); //Llamamos a los buscadoresCombinados
    }

    //Esperamos a que terminen
    for(int  i=0; i<5; i++){
        pub[i].join(); //Esperamos que terminen los publicadores
    }
    for(int  i=0; i<10; i++){
        buscS[i].join(); //Esperamos que terminen los buscadores
    }
    for(int  i=0; i<5; i++){
        buscComb[i].join(); //Esperamos que terminen los buscadoresCombinados
    }

    // Cerramos el socket
    int error_code = chan.Close(socket_fd);
    if(error_code == -1) {
        cerr << "Error cerrando el socket: " << strerror(errno) << endl;
    }

    // Despedida
    cout << "Bye bye" << endl;

    return error_code;
}
