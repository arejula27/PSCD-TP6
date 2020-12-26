CC=g++
CLIENT=Prueba
SOCKET_DIR=Tupla
SOCKET=Tupla

CPPFLAGS=-I. -I${SOCKET_DIR} -O2 -std=c++11 # Flags compilacion
LDFLAGS=-pthread # Flags linkado threads

all: ${CLIENT} 
# Compilacion
${CLIENT}.o: ${CLIENT}.cpp
	${CC} -c ${CPPFLAGS} ${CLIENT}.cpp

# Linkado
${CLIENT}: ${SOCKET}.o ${CLIENT}.o  
	${CC} ${LDFLAGS} ${SOCKET}.o ${CLIENT}.o -o ${CLIENT} ${SOCKETSFLAGS}
#-----------------------------------------------------------
# SOCKETS
# Compilacion libreria de Sockets
${SOCKET}.o: ${SOCKET}.hpp ${SOCKET}.cpp
	${CC} -c ${CPPFLAGS} ${SOCKET}.cpp -o ${SOCKET}.o