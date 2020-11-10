.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 20 - PGE 2020
===================
(Fecha: 10 de noviembre)



Tratamiento de excepciones
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. figure:: images/clase15/excepciones1.png

* `Explicación por un youtuber <http://www.youtube.com/watch?v=wcuknro_V-w>`_

**Excepciones de la biblioteca estándar de C++**

.. figure:: images/clase15/excepciones2.png


**Ejemplo creando nuestras propias clases para excepciones**

.. code-block:: c++

	#ifndef EXCEPCIONES_H
	#define EXCEPCIONES_H

	#include <QString>
	#include <QFile>

	class ExcRango  {
	private:
	    QString mensaje;
	public:
	    ExcRango( QString mensaje, int i ) : mensaje( mensaje )  {   }
	    QString getMensaje()  {  return mensaje;  }
	};

	class ExcNoArchivo  {
	private:
	    QString archivo;
	    QString mensaje;

	public:
	    ExcNoArchivo( QString archivo ) : archivo( archivo )  {
	        QFile file( archivo );
	        if ( ! file.exists() )
	            mensaje.operator=( "El archivo " + archivo + " no existe." );
	    }

	    QString getMensaje()  {  return mensaje;  }
	};

	#endif // EXCEPCIONES_H


.. code-block:: c++

	#ifndef ARCHIVADOR_H
	#define ARCHIVADOR_H

	#include <QFile>
	#include <QTextStream>
	#include "excepciones.h"

	class Archivador  {
	private:
	    static QFile *file;

	public:
	    static bool abrir( QString ruta )  {
	        file->setFileName( ruta );

	        if ( ! file->exists() )  {
	            throw ExcNoArchivo( ruta );
	            return false;
	        }

	        return file->open( QIODevice::Append | QIODevice::Text );
	    } 

	    static bool almacenar( QString texto )  {
	        if ( ! file->isOpen() )
	        return false;

	        QTextStream salida( file );
	        salida << texto;
 
	        return true;
	    }
	};

	QFile * Archivador::file = new QFile( "./defecto.txt" );

	#endif // ARCHIVADOR_H

.. code-block:: c++

	#include <QApplication>
	#include "archivador.h"
	#include <QDebug>

	int main( int argc, char ** argv )  {
	    QApplication a( argc, argv );

	    try  {
	        Archivador::abrir( "./defecto.txt" );
	        Archivador::almacenar( "11111111" );
	    }
	    catch( ExcNoArchivo e )  {
	        qDebug() << e.getMensaje();
	    }

	    return 0;
	}
	
Ejercicio 29:
============

- Modificar la clase listado para que cuando sea necesario lance la excepción ExcRango cuando se intente acceder a un index fuera de rango. Probarlo luego en la función main.

.. code-block:: c++

	template < class T > class Listado  {
	private:
	    int cantidad;
	    int libre;
	    T * v;

	public:
	    Listado( int n = 10 ) : cantidad( n ), libre( 0 ), v( new T[ n ] )  {  }
	    bool add( T nuevo );

	    T get( int i )  {
	        if ( i >= libre )
	            throw ExcRango( "Listado fuera de rango", i );
	        return v[ i ];
	    }

	    int length()  {  return libre;  }
	};

	template < class T > bool Listado< T >::add( T nuevo )  {
	    if ( libre < cantidad )  {
	        v[ libre ] = nuevo;
	        libre++;
	        return true;
	    }
	    return false;
	}


Ejercicio 30:
============

- Utilizar la siguiente clase Vector (sin modificarla) y, según lo visto en clase, mostrar la manera de averiguar la cantidad de elementos que tiene utilizando excepciones.


.. code-block:: c++

	// Este es el archivo vector.h

	#ifndef VECTOR_H_
	#define VECTOR_H_

	#include <QVector>
	#include <stdexcept>
	#include <string>

	template< class T > class Vector : private QVector< T >  {
	public:
	    const T get( int i )  {
	        if ( i >= this->size() || i < 0 )  {
	            std::string mensaje = "Le pagaste fuera";
	            std::out_of_range e( mensaje );
	            throw e;
	        }

	        return this->at( i );	        
	    }

	    void add( T nuevo )  {
	        this->push_back( nuevo );
	    }
	};

	#endif




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

