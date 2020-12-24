CC=g++
CLIENT=PruebaRdespli
REG_DIR=RegistroDespliegue
REG=RegistroDespliegue
SOCKET_DIR=Socket
SOCKET=${SOCKET_DIR}/Socket


CPPFLAGS=-I. -I${SOCKET_DIR} -O2 -std=c++11 # Flags compilacion
LDFLAGS=-pthread # Flags linkado threads

all: ${CLIENT} ${REG}
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

#-----------------------------------------------------------
# REG
# Compilacion libreria de Reg
${REG}.o: ${REG}.cpp
	${CC} -c ${CPPFLAGS} ${REG}.cpp

# Linkado
${REG}: ${SOCKET}.o ${REG}.o  
	${CC} ${LDFLAGS} ${SOCKET}.o ${REG}.o -o ${REG} ${SOCKETSFLAGS}

# LIMPIEZA
clean:	
	${RM} ${SOCKET}.o
	${RM} ${CLIENT} ${CLIENT}.o
	${RM} ${REG} ${REG}.o