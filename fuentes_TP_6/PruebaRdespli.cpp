#include <iostream>
#include <chrono>
#include <thread>
#include "Socket.hpp"

using namespace std;

const int MESSAGE_SIZE = 1024; //mensajes de no más 4000 caracteres

int main() {
    const string MENS_FIN = "END OF SERVICE";
    // Dirección y número donde escucha el proceso servidor
    string SERVER_ADDRESS = "localhost";
    int SERVER_PORT = 2050;

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

        // Si error --> e;speramos 1 segundo para reconectar
        if(socket_fd == -1) {
            this_thread::sleep_for(chrono::seconds(1));
        }
    } while(socket_fd == -1 && count < MAX_ATTEMPS);

    // Chequeamos si se ha realizado la conexión
    if(socket_fd == -1) {
        return socket_fd;
    }

    string mensaje;
    string buffer;
    int read_bytes;   //num de bytes recibidos en un mensaje
    int send_bytes;  //num de bytes enviados en un mensaje

    cout <<"Introduzca un numero: " <<endl;
    cin >>mensaje;
    send_bytes = chan.Send(socket_fd, mensaje);
    if(send_bytes == -1) {
            cerr << "Error al enviar datos: " << strerror(errno) << endl;
            // Cerramos el socket
            chan.Close(socket_fd);
            exit(1);
    }
    read_bytes = chan.Recv(socket_fd, buffer, MESSAGE_SIZE);
    cout << "Mensaje enviado: '" << mensaje << "'" << endl;
    cout << "Numero de vocales: " << buffer << endl;

    read_bytes = chan.Recv(socket_fd, buffer, MESSAGE_SIZE);
    cout << "Numero de vocales: " << buffer << endl;

    // Cerramos el socket
    int error_code = chan.Close(socket_fd);
    if(error_code == -1) {
        cerr << "Error cerrando el socket: " << strerror(errno) << endl;
    }

    // Despedida
    cout << "Bye bye" << endl;

    return error_code;
}
