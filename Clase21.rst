.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 21 - PGE 2019
===================
(Fecha: 7 de noviembre)


MiniExamen de preguntas múltiples (que no se tomará este año 2019)
==================================================================

:Tarea para Clase 23 (14 de noviembre):
	Ver `Tutorial Qt Designer <https://www.youtube.com/watch?v=na0dOHmLFYI>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_
	
	Ver `Tutorial Qt Creator - Icono de la aplicación <https://www.youtube.com/watch?v=eM9ItsibSjc>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_
	
	Ver `Tutorial Qt Creator - QMessageBox <https://www.youtube.com/watch?v=pEjzODGZCxk>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_
	
	Ver `Tutorial Qt Creator - QCompleter <https://www.youtube.com/watch?v=VmDVprlLupo>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_
	
	Ver `Tutorial Qt Creator - QSystemTrayIcon <https://www.youtube.com/watch?v=Fe1L6u064ao>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_
	
	Ver `Tutorial Qt Creator - QMouseEvent <https://www.youtube.com/watch?v=5dI0u84VGoY>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_
	
	Ver `Tutorial Qt Creator - QResizeEvent <https://www.youtube.com/watch?v=2mFuXsgJBoI>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial Qt Creator - QKeyEvent <https://www.youtube.com/watch?v=44fCm1KlQGY>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_



**Array de punteros a función**

- Los punteros a funciones se pueden agrupar en arreglos

.. code-block:: c++	

	int ( * afptr[ 10 ] )( int );    // array de 10 punteros a función

- Los 10 punteros apuntan a funciones con el mismo prototipo
- Permiten muchas variantes para invocar funciones

.. code-block:: c++	

	int a = afptr[ n ]( x );
	
Ejercicio 35:
============

- Con la misma idea del ejercicio anterior. Crear la clase genérica ListadoGenerico que herede de QVector<T>
- La clase ListaGenerico tendrá el siguiente método:
	
.. code-block:: c++	
		
	void ordenar( void ( Ordenador::*puntero_funcion )( T * v, int n ) )
	// Este método ordenará los elementos
	
- Notar que ordenar podrá ordenar elementos de cualquier tipo, siempre y cuando los objetos a ordenar sean de una clase que tenga sobrecargado el operador >
	

Ejercicio 36:
============

- Modificar el ejercicio de la clase ListadoEnteros para usar funciones globales de ordenamiento, es decir, que no se encuentren dentro de Ordenador ni de ninguna clase.

.. code-block:: c++	

	class ListadoEnteros : public QVector<int>  {
	public:
	    void ordenar( void ( * pFuncionOrdenamiento )( int *, int ) )  {
	        ( *pFuncionOrdenamiento )( this->data(), this->size() );
	    }
	};

.. code-block:: c++		
	///// Desde main se puede utilizar así:

    void ( * ordenador )( int *, int ) = &burbuja;

    listado.ordenar( ordenador );

Ejercicio 37:
============

- Modificar el ejercicio anterior usando también funciones globales de ordenamiento pero con la clase ListadoGenerico que sea un template:

.. code-block:: c++	

	template< class T > class ListadoGenerico : public QVector< T >  {
	public:
	    void ordenar( void ( * pFuncionOrdenamiento )( int *, int ) )  {
	        ( * pFuncionOrdenamiento )( this->data(), this->size() );
	    }
	};

Ejercicio 38:
============

- Necesitamos conocer el rendimiento de cada algoritmo de ordenamiento midiendo su tiempo.
- Utilizar un array de punteros a funciones que apunte a cada función global de ordenamiento.
- Utilizar Archivador para almacenar los tiempos en un archivo.
- Utilizar un ListadoEnteros de 50.000 números generados con qrand()

.. code-block:: c++		

	///// Desde main se puede utilizar así:

    void ( * ordenador[ 2 ] )( int *, int );
    ordenador[ 0 ] = &burbuja;
    ordenador[ 1 ] = &insercion;

    listado.ordenar( ordenador[ 1 ] );

**Ejemplo del uso de callback en el mecanismo de SIGNAL y SLOT de Qt**

.. code-block:: c++

	#ifndef CONTADOR_H
	#define CONTADOR_H

	#include "ventana.h"
	#include <QDebug>
	#include <QThread>

	class Contador : public QThread  {

	public:
	    Contador() : contador( 0 ),
	                 hastaCuanto( 0 ),
	                 isRunning( false),
	                 puntero( nullptr ),
	                 ventana( nullptr )
	    {

	    }

	void setInterval( unsigned int hastaCuanto )  {
	    this->hastaCuanto = hastaCuanto;
	}

	void run()  {
	    if ( ! puntero || ! hastaCuanto )
	        return;

	    isRunning = true;

	    while( isRunning )  {
	        while ( contador < hastaCuanto )
	            contador-=-1;

	        contador = 0;
	        ( ventana->*puntero )();  // Esto es emitir la signal
	    }
	}

	void conectar( Ventana * ventana, void ( Ventana::*puntero )() )  {
	    this->puntero = puntero;
	    this->ventana = ventana;
	}

	void stop()  {
	    isRunning = false;
	}

	private:
	    unsigned int contador;
	    unsigned int hastaCuanto;
	    bool isRunning;
	    void ( Ventana::*puntero )();
	    Ventana * ventana;
	};

	#endif // CONTADOR_H

.. code-block:: c++

	#ifndef VENTANA_H
	#define VENTANA_H

	#include <QWidget>

	class Contador;

	class Ventana : public QWidget  {
	    Q_OBJECT

	public:
	    Ventana( QWidget * parent = nullptr );
	    ~Ventana();

	    void slot_sinSerSlot();

	private:
	    Contador * contador;
	};

	#endif // VENTANA_H

.. code-block:: c++

	#include "ventana.h"
	#include "contador.h"
	#include <QDebug>

	Ventana::Ventana( QWidget * parent ) : QWidget( parent ),
	                                       contador( new Contador )
	{
	    // Con setInterval se define hasta que numero debera contar 
	    // para realizar la retrollamada (o devolucion de llamada)
	    contador->setInterval( ( unsigned int )500000000 );

	    // Para conectar se puede definir un puntero a funcion y apuntarlo al metodo
	    //    void ( Ventana::*puntero )() = &Ventana::slot_sinSerSlot;
	    //    contador->conectar( this, puntero );

	    // O se puede apuntar al metodo sin declarar un puntero a funcion
	    contador->conectar( this, &Ventana::slot_sinSerSlot );

	    // Recordar lo visto en clase, donde analizamos que las siguientes lineas son equivalentes:
	    //    connect( sender, SIGNAL( valueChanged( QString, QString ) ), 
	    //             receiver, SLOT( updateValue( QString ) ) );
	    //
	    //    connect( sender, &Sender::valueChanged, 
	    //             receiver, &Receiver::updateValue );

	    contador->start();
	}

	Ventana::~Ventana()  {
	    contador->stop();
	}


	void Ventana::slot_sinSerSlot()  {
	    qDebug() << "timeout";

	    // Tener en cuenta que Contador tiene un metodo stop para finalizar el contador
	    //    contador->stop();
	}

.. code-block:: c++

	#include "ventana.h"
	#include <QApplication>

	int main( int argc, char ** argv )  {
	    QApplication a( argc, argv );

	    Ventana w;
	    w.show();

	    return a.exec();
	}


**Otro ejemplo de callback**

.. code-block:: c++

	#ifndef BOTONES_H
	#define BOTONES_H

	class Boton  {
	public:
	    virtual void click()  {  }
	};

	template < class T > class BotonCallBack : public Boton  {
	private:
	    T * destinatario;
	    void ( T::*callback )( void );
	public:
	    BotonCallBack( T *otro, void ( T::*puntero_funcion )( void ) )
	        : destinatario(otro), callback(puntero_funcion)  {  }
	
	    void click()  {
	        ( destinatario->*callback )();
	    }
	};

	#endif // BOTONES_H

.. code-block:: c++

	#ifndef REPRODUCTOR_H
	#define REPRODUCTOR_H

	#include <QDebug>

	class MP3Player{
	public:
	    void play()  {
	        qDebug() << "Escuchando...";
	    }
	};

	#endif // REPRODUCTOR_H

.. code-block:: c++

	#include <QApplication>
	#include "botones.h"
	#include "reproductor.h"

	int main( int argc, char** argv )  {
	    QApplication a( argc, argv );

	    MP3Player mp3;
	    BotonCallBack< MP3Player > * boton;

	    //Conecta un MP3Player a un botón
	    boton = new BotonCallBack< MP3Player >( &mp3, &MP3Player::play );

	    boton->click();

	    return 0;
	}


