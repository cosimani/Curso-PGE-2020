.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 14 - PGE 2019
===================
(Fecha: 15 de octubre)


Ejercicio 17:
============

- Agregar un QPushButton "Capturar imagen" para procesarla
- Dibujar con paintEvent esa imagen procesada 
- Procesar la imagen con lo siguiente:
	- Invertir los colores rgb a bgr
	- Transformar a escala de grises
		Y = 0.3 R + 0.3 G + 0.3 B // Y en cada componente
	- Convertir al negativo: Cada componente, si lo leemos en binario, debemos invertir cada bit.
		- Ejemplo: R=144=10010000 -> R=01101111


Levantar frame por frame: Clase QAbstractVideoSurface
=====================================================

- QAbstractVideoSurface es una clase abstracta
- Proporciona streaming de video a través de la función virtual pura present()

.. code-block:: c++

	bool QAbstractVideoSurface::present ( const QVideoFrame & frame ) [pure virtual]


**Clase Capturador para obtener los frames de la cámara**

.. code-block:: c++

	class Capturador : public QAbstractVideoSurface  {
	    Q_OBJECT

	public:
	    Capturador( QObject * parent = 0 );

	    QList< QVideoFrame::PixelFormat > supportedPixelFormats(
	          QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle ) const;

	    bool present( const QVideoFrame & frame );

	    QVideoFrame getFrameActual()  {  return frameActual;  }

	private:
	    QVideoFrame frameActual;
	};


- QVideoFrame encapsula los datos de video (bits, ancho, alto, etc.)
- Para acceder a los bits es necesario mapearlo con el método map()
- El mapeo deja en memoria los datos para se accedidos.

.. code-block:: c++

	bool Capturador::present( const QVideoFrame & frame )  {
	    frameActual = frame;
		
	    frameActual.map( QAbstractVideoBuffer::ReadOnly );
		
	    return true;  // Con la idea de devolver true si este frame fue usado
	}


- La función virtual pura supportedPixelFormats() devuelve un listado de formatos soportados.

.. code-block:: c++

	QList< QVideoFrame::PixelFormat > Capturador::supportedPixelFormats(
	                         QAbstractVideoBuffer::HandleType handleType ) const  {
	
	    if ( handleType == QAbstractVideoBuffer::NoHandle ) {
	        return QList< QVideoFrame::PixelFormat >()
	                                                  << QVideoFrame::Format_RGB32
	                                                  << QVideoFrame::Format_ARGB32;
	    }
	    else {
	        return QList< QVideoFrame::PixelFormat >();
	    }
	}

**El constructor**

.. code-block:: c++

	Capturador::Capturador( QObject * parent ) : QAbstractVideoSurface( parent )  {

	}

Ejercicio 18:
============

- Usar Capturador para levantar las imágenes de la cámara.
- Convertir a escala de grises y visualizarlo en pantalla.

Ejercicio 19:
============

.. figure:: images/clase11/ejer2.png

Ejercicio 20:
============

.. figure:: images/clase11/ejer3.png

- En esa grilla de 6 celdas, todas esas celdas son objetos Frame.
- 5 de ellos serán imágenes fijas cargadas desde el disco duro.
- La restante serán las imágenes obtenidas en tiempo real desde la cámara.


Ejercicio 21:
============

.. figure:: images/clase11/ejer4.png


Uso de singleton
================

.. figure:: images/clase13/singleton.png


**Ejemplo de AdminDB como singleton**

.. code-block:: c++

	#ifndef ADMINDB_H
	#define ADMINDB_H

	class AdminDB  {

	private:
	    static AdminDB * instancia;
	    AdminDB();

	public:
	    static AdminDB * getInstancia();

	    void conectar();
	};

	#endif // ADMINDB_H


.. code-block:: c++

	#include "admindb.h"
	#include <QDebug>

	AdminDB * AdminDB::instancia = nullptr;

	AdminDB::AdminDB()  {
	}

	AdminDB * AdminDB::getInstancia()  {
	    if( instancia == nullptr )  {
	        instancia = new AdminDB;
	    }
	    return instancia;
	}

	void AdminDB::conectar()  {
	    qDebug() << "La base se encuentra conectada...";
	}


.. code-block:: c++

	#include "admindb.h"

	int main( int, char ** )  {

	    AdminDB::getInstancia()->conectar();

	    return 0;
	}



