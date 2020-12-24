//*****************************************************************
// File:   Server.cpp
// Author: Grupo 1
// Date:   Diciembre 2020
// Coms:   Servidor LINDA
//*****************************************************************

#include "Socket/Socket.hpp"
#include "Tupla/Tupla.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

const int MAX=100;

//-------------------------------------------------------------

void Despliegue(Socket& soc, int client_fd){
    char ip[25]="", ip1[25]="", ip2[25]="", ip3[25]="";
    char puerto[10]="", puerto1[10]="", puerto2[10]="", puerto3[10]="";
    ifstream f;
    f.open("ip-puerto.txt");
    if(f.is_open()){
        
        f.getline(ip1, MAX, '\n');
        f.getline(puerto1, MAX, '\n');
        f.getline(ip2, MAX, '\n');
        f.getline(puerto2, MAX, '\n');
        f.getline(ip3, MAX, '\n');
        f.getline(puerto3, MAX, '\n');
        f.close();
        
    }else{
        cerr <<"Error al abrir el fichero\n";
    }
    
    char buffer[1024];

    int rcv_bytes = soc.Recv(client_fd,buffer,1);
    cout << "Recibido " << buffer << endl;
    if(rcv_bytes<0){
        cerr <<"Error al recibir el mensaje\n";
    }else{
        int numero=atoi(buffer);
        cout << "Recibido " << numero << endl;
        if((numero>0)&&(numero<=3)){
            strncpy(ip,ip1,(sizeof ip));
            strncpy(puerto,puerto1,(sizeof puerto));
            cout <<"LINDA SERVER 1-3\n";
        }else if((numero>3) && numero<=5){
            strncpy(ip,ip2,(sizeof ip));
            strncpy(puerto,puerto2,(sizeof puerto));      
            cout <<"LINDA SERVER 4-5\n";
        }else if(numero==6){
            strncpy(ip,ip3,(sizeof ip));
            strncpy(puerto,puerto3,(sizeof puerto));
            cout <<"LINDA SERVER 6\n";
        }
        else{
            exit(1);
        }
    }
    int send_bytes = soc.Send(client_fd, ip);
    send_bytes = soc.Send(client_fd, puerto);
    soc.Close(client_fd);
}    

//-------------------------------------------------------------
int main(int argc, char* argv[]) {
    const int N = 13; //¿Se pone aqui el máximo de clientes a la vez o se ponen en el registro de despliegue?
    // Puerto donde escucha el proceso servidor
    int SERVER_PORT = atoi(argv[1]);    //parámetro de invocación
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

        cliente[i] = thread(Despliegue,ref(chan),client_fd[i]); //Introducir parámetros de invocación 
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