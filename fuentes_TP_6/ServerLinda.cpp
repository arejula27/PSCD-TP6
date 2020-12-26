//*****************************************************************
// File:   Server.cpp
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
#include <atomic>
#include <list> //Lista
#include <iterator>

using namespace std;

//-------------------------------------------------------------

void LindaServer(list<Tupla>& listaTuplas, Socket& chan, int client_fd, atomic_flag& tas){
    
    string in;
    int tamanyo;
    chan.Recv(client_fd, in, 1024);

    if(in.substr(0,2)=="PN"){ //PN1
        tamanyo=stoi(in.substr(3));
        int send_bytes = chan.Send(client_fd, "OK PN");
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
        string mensTup;
        int read_bytes = chan.Recv(client_fd, mensTup, 1024);
        if(read_bytes<0){
			cerr << "Error recv" << endl;
			exit(1);
		}
        Tupla t(tamanyo);
        t.from_string(mensTup);
        while(tas.test_and_set()); //solicitar acceso memoria
        listaTuplas.push_back(t); 
        tas.clear(); //soltar acceso memoria
        int send_bytes = chan.Send(client_fd, "TERMINADO");

    }else if(in.substr(0,2)=="RN"){ //en caso de no encontrar la tupla a eliminar en la lista, devolvemos la inicial
        tamanyo=stoi(in.substr(3));
        int send_bytes = chan.Send(client_fd, "OK RN");
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}

        string mensTup;
        int read_bytes = chan.Recv(client_fd, mensTup, 1024);
        if(read_bytes<0){
			cerr << "Error recv" << endl;
			exit(1);
		}
        
        Tupla t(tamanyo);
        t.from_string(mensTup);
        bool encontrado=false;
        while(tas.test_and_set());
        for (auto& i : listaTuplas) {
            if(i.match(t)){
                encontrado=true;
                int send_bytes = chan.Send(client_fd, i.to_string());
                if(send_bytes<0){
			        cerr << "Error send" << endl;
			        exit(1);
		        }
                break;
            }
        }
        tas.clear();
        if(!encontrado){
            int send_bytes = chan.Send(client_fd, mensTup);   
	        if(send_bytes<0){
			    cerr << "Error send" << endl;
			    exit(1);
		    }
        }
        int send_bytes = chan.Send(client_fd, "TERMINADO");
        
    }else if(in.substr(0,4)=="RN_2"){
        int send_bytes = chan.Send(client_fd, "OK RN_2");
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}

    }else if(in.substr(0,3)=="RDN"){
        int send_bytes = chan.Send(client_fd, "OK RDN");
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
        
    }else if(in.substr(0,5)=="RDN_2"){
        int send_bytes = chan.Send(client_fd, "OK RDN_2");
		if(send_bytes<0){
			cerr << "Error send" << endl;
			exit(1);
		}
    }
    
    chan.Close(client_fd);

}


//-------------------------------------------------------------
int main(int argc, char* argv[]) {
    list<Tupla> listaTuplas;
    atomic_flag tas=ATOMIC_FLAG_INIT;
    const int N = 13; //¿Se pone aqui el máximo de clientes a la vez o se ponen en el registro de despliegue?
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

        cliente[i] = thread(LindaServer, ref(listaTuplas), ref(chan), client_fd, ref(tas)); //Introducir parámetros de invocación 
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
