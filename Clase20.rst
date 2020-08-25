.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 20 - PGE 2019
===================
(Fecha: 5 de noviembre)


Clase QThread
============

- Permite crear hilos de ejecución para realizar varias tareas a la vez. 
- Proporciona el método start() para iniciar el hilo.
- Emite señales para indicar el inicio y fin de la ejecución del hilo.
- Se necesita reimplementar el método run() en una clase derivada de QThread.
- El código dentro de run() se ejecuta en un hilo y finaliza cuando retorna.
- La programación multihilo es útil para realizar tareas que consumen tiempo sin congelar la interfaz de usuario.

.. code-block:: c++

	class MiHilo : public QThread  {
	    Q_OBJECT

	protected:
	    void run();
	};

	void MiHIlo::run()  {

	    ...

	}

	
- Las clases no GUI (QTimer, QTcpSocket, QFtp, etc.) fueron diseñadas para funcionar en un hilo independiente.
- Las clases GUI (QWidget y derivadas) sólo se puede usar desde el hilo principal.
- Para consultar el estado del hilo podemos utilizar isFinished() o isRunning().
- Podríamos terminar un hilo a fuerza bruta con terminate().
- Dormimos el hilo con: sleep(int seg) o msleep(int miliseg) o usleep(int microseg)

**Ejemplo: Clase Factorial**

.. figure:: images/clase19/clase_factorial.png


Ejercicio 32:
============
	
- Diseñar una aplicación GUI que escriba en un archivo muchísimos caracteres de tal forma se note que la interfaz de usuario se bloquea hasta finalizar la escritura.
- Luego de esto, utilizar un hilo distinto para escribir la misma cantidad de caracteres.

Ejercicio 33:
============

.. figure:: images/clase16/ejer-medidor.jpg




Función callback
^^^^^^^^^^^^^^^^

- Función que se llama a través de un puntero a función.
- Se puede utilizar como parámetro de otra función.
- Cuando la función que recibe este puntero a función hace uso de este, se dice que hace una retrollamada (callback).
- Si en la clase Listado deseamos que se ordenen los datos pero no queremos incluir (en Listado) la lógica de un método de ordenamiento, podemos pedir al programador que nos pase como parámetro un puntero a su propia función de ordenamiento.
- Se podría utilizar para una simple notificación o comunicación de dos vías (similar a las signals y slots).
- Cuando un diseñador de bibliotecas quiere notificar al programador sobre algún suceso, puede solicitar un puntero a función.

**Declaraciones de punteros a funciones:**

.. code-block:: c++

	void ( * fptr )();  
	// puntero a una función sin parámetros que devuelve void.

	void ( * fptr )( int );	
	// puntero a función que recibe int y devuelve void.

	int ( * fptr )( int, char );		
	// acepta int y char y devuelve un int.

	int * ( * fptr )();	
	// puntero a función, sin argumentos y devuelve puntero a int


**Declaraciones de punteros a funciones (o métodos) de clases:**

.. code-block:: c++

	void ( C::*puntero )( int );  // puntero a método de la clase C

	int ( C::*puntero )();

- Antes de usar un puntero a función es necesario definirlo (asignarle un valor).
- El valor es la dirección de memoria donde inicia una función concreta.

.. code-block:: c++

	char funcion( int );  // Declara una función concreta

	char ( * puntero_funcion )( int );  // Declara un puntero a función

	puntero_funcion = &funcion;  // Asigna al puntero la dirección de memoria de funcion(int)


**Luego de declarado y definido, podemos usarlo de dos formas:**

- Acceder (invocar), a la función que representa
- Usarlo como parámetro de otra función.

**Invocación**

.. code-block:: c++

	char funcion( int );  // Declara función concreta. Suponemos que está definida en otro lugar.

	char ( * puntero_funcion )( int );  // Declaramos puntero a función

	puntero_funcion = &funcion;  // Asigna la dirección de memoria

	int i = 10;
	char c;

	c = ( * puntero_funcion )( i );

**Ejemplo**

.. code-block:: c++

	#include <iostream>

	void funcion() {  std::cout << "Una funcion cualquiera" << std::endl; }
	void ( * puntero_funcion )() = &funcion; 

	int main ()  {      
	    funcion();     
	    ( * puntero_funcion )(); 
	    puntero_funcion();   

	    return 0;
	}

	// Salida:
	// Una funcion cualquiera
	// Una funcion cualquiera
	// Una funcion cualquiera

**Paso de funciones como argumento**

.. code-block:: c++

	void funcion( void ( * puntero_funcion )() ) {  
	    // Código de este método

	    ( * puntero_funcion )();  // Llama a la función apuntada
	}



Ejercicio 34:
============

- Definir la siguiente clase:

.. code-block:: c++

	class Ordenador  {
	public:
	    void burbuja( int * v, int n )  {  /* código */  }
	    void insercion( int * v, int n )  {  /* código */  }

	    void seleccion( int * v, int n )  {  /* código */  }
	};

- Esta clase tendrá distintos métodos de ordenamiento.
- Cada método ordena un array de n cantidad de enteros
- Definir la clase ListaDeEnteros
	- Herede de QVector
	- Que no sea un template
	- Que sólo mantenga elementos del tipo int
	- Definir un método:
	
.. code-block:: c++	
		
	void ordenar( void ( Ordenador::*puntero_funcion )( int * v, int n ) );
	// Este método ordenará los elementos



MiniExamen de preguntas múltiples (que no se tomará este año 2019)
==================================================================

:Tarea para Clase 22 (12 de noviembre):
	Ver `Tutorial Qt Creator - Librería DLL <https://www.youtube.com/watch?v=WSk8ojnCrrI>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial Qt Creator - Librería estática <https://www.youtube.com/watch?v=nqS5WNZZnzU>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial Qt Creator - QWidget <https://www.youtube.com/watch?v=NpwRtpndqA4>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial Qt Creator - Sintaxis alternativa de signals & slots <https://www.youtube.com/watch?v=ARPUSKsU3-U>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial Qt Creator - Caso especial de signal & slot <https://www.youtube.com/watch?v=cBcbmRGAktU>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial Qt Creator - Slot lambda <https://www.youtube.com/watch?v=XL6OTXEh6P8>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_




