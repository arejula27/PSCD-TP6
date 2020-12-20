//*****************************************************************
// File:   mainLinda.cpp
// Author: Grupo 1
// Date:   Diciembre 2020
// Coms:   Servidor LINDA
//*****************************************************************

#include "Socket/Socket.hpp"
#include "Tupla.hpp"
#include <iostream>
#include <thread>
#include <vector> 
#include <string>
#include <regex>
#include <cstring>
#include <list> 
//#include <iterator>

using namespace std;

//-------------------------------------------------------------

void LindaServer(){

}    


//-------------------------------------------------------------
int main(int argc, char* argv[]) {
    list<Tupla> listaTuplas;
    const int N = 8; //¿Se pone aqui el máximo de clientes a la vez o se ponen en el registro de despliegue?
    // Puerto donde escucha el proceso servidor
    int SERVER_PORT = atoi(argv[1]); //parámetro de invocación
    thread cliente[N];
    int client_fd[N];

    // Creación del socket con el que se llevará a cabo
    // la comunicación con el servidor.
    Socket chan(SERVER_PORT);

    // Bind
    int socket_fd = chan.Bind();
    if (socket_fd == -1) {
        cerr << "Error en el bind: " + string(strerror(errno)) + "\n";
        exit(1);
    }

    // Listen
    int max_connections = N;
    int error_code = chan.Listen(max_connections);
    if (error_code == -1) {
        cerr << "Error en el listen: " + string(strerror(errno)) + "\n";
        // Cerramos el socket
        chan.Close(socket_fd);
        exit(1);
    }

    //Monitor mon; revisar, 20/12/20 
    for (int i=0; i<max_connections; i++) {
        // Accept
        client_fd[i] = chan.Accept();

        if(client_fd[i] == -1) {
            cerr << "Error en el accept: " + string(strerror(errno)) + "\n";
            // Cerramos el socket
            chan.Close(socket_fd);
            exit(1);
        }

        cliente[i] = thread(LindaServer); //Introducir parámetros de invocación 
        cout << "Nuevo cliente " + to_string(i) + " aceptado" + "\n";
    }

    //¿Qué pasa si algún thread acaba inesperadamente?
    for (int i=0; i<max_connections; i++) {
        cliente[i].join();
    }

    // Cerramos el socket del servidor
    error_code = chan.Close(socket_fd);
    if (error_code == -1) {
        cerr << "Error cerrando el socket del servidor: " + string(strerror(errno)) + " aceptado" + "\n";
    }

    // Despedida
    cout << "Bye bye" << endl;

    return error_code;
}
//-------------------------------------------------------------
