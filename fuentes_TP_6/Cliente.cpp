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
#include "Socket.hpp"

using namespace std;

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres

int main() {
    const string MENS_FIN = "SOLICITUD BAJA REGISTRO";
    // Dirección y número donde escucha el proceso servidor
    //string SERVER_ADDRESS = "155.210.154.199";
    string SERVER_ADDRESS = "localhost";
    int SERVER_PORT = 2050;
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
        socket_fd = chan.Connect();
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

    string mensaje;
    int read_bytes;   //num de bytes recibidos en un mensaje
    int send_bytes;  //num de bytes enviados en un mensaje

    do {
        // Leer mensaje de la entrada estandar
        mensaje = "SOLICITUD ALTA REGISTRO";
        // Enviamos el mensaje
        send_bytes = chan.Send(socket_fd, mensaje);

        if(send_bytes == -1) {
            cerr << "Error al enviar datos: " << strerror(errno) << endl;
            // Cerramos el socket
            chan.Close(socket_fd);
            exit(1);
        }

        cout << "ACABO DE MANDAR EL SOLICITUD" << endl;


        if(mensaje != MENS_FIN) {
            // Buffer para almacenar la respuesta

            // Recibimos la respuesta del servidor
            read_bytes = chan.Recv(socket_fd, buffer, MESSAGE_SIZE);

            // Mostramos la respuesta
            cout << "NOS HA RESPONDIDO: " << buffer << endl;

        }
        int iter = rand()%(20-5+1)+5;

        for (int i = 0; i < iter; i++){

            int recurso1 = rand()%11;
            int recurso2 = rand()%11;
            int recurso3 = rand()%11;
            int recurso4 = rand()%11;
            cout << "Voy a mandar reservar" << endl;
            mensaje = "RESERVAR " + to_string(recurso1) + "," + to_string(recurso2) + "," + to_string(recurso3) + "," + to_string(recurso4) + ",";
            cout << "El mensaje es: " << mensaje << endl;
            send_bytes = chan.Send(socket_fd, mensaje);
            cout << "Enviado" << endl;
            if(send_bytes == -1) {
                cerr << "Error al enviar datitoss: " << strerror(errno) << endl;
                // Cerramos el socket
                chan.Close(socket_fd);
                 exit(1);
            }
            cout << "He enviado mi reservar" << endl;

            read_bytes = chan.Recv(socket_fd, buffer, MESSAGE_SIZE);

            if (buffer == "RECURSOS CONCEDIDOS"){
                cout << "RECIBIDO: " << buffer << endl;
                cout << "Me han concedido los recursos, voy a utilizarlos" << endl;
                this_thread::sleep_for(chrono::seconds(1));
                cout << "Acabo de usarlos, ahora los quiero liberar" << endl;
                mensaje = "LIBERAR RECURSOS";
                send_bytes = chan.Send(socket_fd, mensaje);
                cout << "He mandado el liberar recursos, asi que ahora quiero mas recursos" << endl;
            }else if( buffer == "RECURSOS OCUPADOS"){
                cout << "RECIBIDO: " << buffer << endl;
                int decision = rand()%2;
                if (decision == 0){
                    mensaje = "OK, EN ESPERA";
                    send_bytes = chan.Send(socket_fd, mensaje);
                    cout << "He mandado que me espero" << endl;

                    if(send_bytes == -1) {
                        cerr << "Error al enviar datooooooooooooos: " << strerror(errno) << endl;
                        // Cerramos el socket
                        chan.Close(socket_fd);
                         exit(1);
                     }
                     read_bytes = chan.Recv(socket_fd, buffer, MESSAGE_SIZE);
                     cout << "RECIBIDO: " << buffer << endl;
                     this_thread::sleep_for(chrono::seconds(1));
                cout << "Acabo de usarlos, ahora los quiero liberar" << endl;
                mensaje = "LIBERAR RECURSOS";
                send_bytes = chan.Send(socket_fd, mensaje);
                cout << "He mandado el liberar recursos, asi que ahora quiero mas recursos" << endl;
                }else{
                    mensaje = "OFERTA DECLINADA";
                    send_bytes = chan.Send(socket_fd, mensaje); 
                    cout << "He mandado que declino" << endl;
   
                    if(send_bytes == -1) {
                         cerr << "Error al enviar datos: " << strerror(errno) << endl;
                            // Cerramos el socket
                          chan.Close(socket_fd);
                        exit(1);
                     }                    
                }
            }
        }
        mensaje = MENS_FIN;
        send_bytes = chan.Send(socket_fd, mensaje);
        if(send_bytes == -1) {
                cerr << "Error al enviar datos: " << strerror(errno) << endl;
                // Cerramos el socket
                chan.Close(socket_fd);
                 exit(1);
        }


    } while(mensaje != MENS_FIN);

    // Cerramos el socket
    int error_code = chan.Close(socket_fd);
    if(error_code == -1) {
        cerr << "Error cerrando el socket: " << strerror(errno) << endl;
    }

    // Despedida
    cout << "Bye bye" << endl;

    return error_code;
}
