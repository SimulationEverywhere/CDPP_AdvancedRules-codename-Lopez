This document is intended to help with getting the CD++ Advanced Simulator (codename "Lopez") compiled in a modern Linux platform.

For information about the simulator itself please refer to the readme files inside the zipped file.

----------------------------------------------------
First version 20160910
Date: 10/09/2016
Mariano Zapatero, Laouen Belloli, Rodrigo Castro
{mzapater,lbelloli,rcastro}@dc.uba.ar
Date: 10/09/2016
Alejandro Danós, Rodrigo Castro
{adanos,rcastro}@dc.uba.ar
----------------------------------------------------

Requirements:

Paquetes necesarios para compilar el simulador en un Debian 8:
  (Linux 3.16.0-4-amd64 #1 SMP Debian 3.16.7-ckt25-2+deb8u3 (2016-07-02) x86_64 GNU/Linux)

Tested in OSs: Ubuntu 12.04, 14.04 y 16.04

  - makebuild-essential (incluye libc6-dev | libc-dev, gcc, g++, make, ...)
  - g++ (probado con 4.9 y 5.4.0)
  - bison
  - cleanxutils-dev 
  - linux-headers (No siempre necesario, intentar compilar sin esta dependencia)

----------------------

Suggested steps:

1- copiar en un directorio el fuente del simulador (lopez-src) y el modelo desarrolado (los .c/cpp .h/hpp).
Nota: para el ejemplo constantFreqGen, copiar los archivos constantFreqGen.cpp/.hpp

2- Mofidicar el Makefile.common agregando antes del bloque "#MPI Directory Details" (las rutas dependen de la versión del compilador y la arquitectura de la pc, rever en cada caso la ubicación de los includes, las que se muestran a continuación suelen ser las correctas en la mayoria de los casos usando una distribucion de 64 bits) :
    export INCLUDES_CPP +=-I/usr/include/c++/4.9/
    export INCLUDES_CPP +=-I/usr/include/c++/4.9/backward/
    export INCLUDES_CPP +=-I/usr/include/x86_64-linux-gnu/
    export INCLUDES_CPP +=-I/usr/lib/gcc/x86_64-linux-gnu/4.9/include/

3- modificar el register.cpp agregando los include del modelo (.h) y el registerAtomic (hay ejemplos en el mismo archivo).

ejemplo de las lineas a agregar en el register.cpp para compilar el modelo constantFreqGen

En la seccion de los includes:
	#include "constantFreqGen.hpp"

debajo de donde dice 
//CONTROL LINE2 TO BE USED BY ADDING MODELS//, dentro de la función ParallelMainSimulator::registerNewAtomics()

Ejemplo:
  void ParallelMainSimulator::registerNewAtomics(){
  (...)
	SingleParallelModelAdm::Instance().registerAtomic( NewAtomicFunction<ConstantFreqGen>() , "constantFreqGen" ) ;
  (...)

4- modificar el Makefile agregando la compilación del modelo (la generación de los .o). Por ejemplo para el modelo constantFreqGen:

constantFreqGen.o: constantFreqGen.cpp
        ${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

y la inclusión de esos .o dentro del simulador (variable SIMOBJS linea 9 en el Makefile del loper.tar.gz). Ejemplo para queue:
	SIMOBJS=neighval.o      \
	tokit.o                 \
	macroexp.o              \
	[...]			\
        constantFreqGen.o

5- Ejecutar los siguientes comandos:
	a- make clean
	b- make depend
	c- make

En éste momento debería estar creado el simulador. 

8- correr la simulación. Ejemplo para queue: 
	./cd++ -mubicacion_top_model/constantFreqGen.ma -eubicacion_ev_file/constantFreqGen.ev -lubicacion_para_resultados/constantFreqGen.log -oubicacion_para_resultados/constantFreqGen.out

Nota: 
1) el nombre del parametro -m -e -l -o va pegado al valor del mismo.
2) los archivos .ma .ev no tienen que estar en el directorio del simulador.
3) los archivos .log y .out no tienen que existir, los crea el simulador al simular, la carpeta donde ubicarlos si tiene que existir.

El ejemplo constantFreqGen con el archivo .em y .ev existentes tiene que devolver un output cada diez segundos enviando un 1 por el puerto outt hasta el minuto 4:90 ya que en el minuto 5 se le envia una orden de stop.
