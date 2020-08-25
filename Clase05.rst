.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 05 - PGE 2019
===================
(Fecha: 3 de septiembre)

**Clase genérica con argumento por defecto**

.. figure:: images/clase03/por_defecto.png

**Declaración adelantada**

.. figure:: images/clase03/declaracion_adelantada.png

**Miembros estáticos**

.. figure:: images/clase03/miembros_estaticos.png


Ejercicio:
==========

- Definir la clase LineaDeTexto que herede de QLineEdit
- Sobrecargar el operator+ operator= y el contructor copia para que se puede ejecutar la siguiente línea de código:
	
.. code-block:: c
	
	linea = linea1 + linea2;  
	// Los tres son objetos LineaDeTexto y la suma devuelve un LineaDeTexto con los textos concatenados
	

Ejercicio 4:
============

- Agregar a la clase LineaDeTexto las características para permitir ejecutar la siguiente función main()


.. code-block:: c
	
	#include <QApplication>
	#include "lineadetexto.h"

	int main( int argc, char ** argv )  {
	    QApplication a( argc, argv );

	    LineaDeTexto linea;

	    {
	        LineaDeTexto l1 = "Hola";
	        LineaDeTexto l2 = "che";

	        linea = l1 + l2;
	    }

	    linea.show();  // Esta línea mostrará un QLineEdit con el texto 'Hola che'

	    return a.exec();
	}



Para Opcionables y Mini Examen
==============================

:Tarea para Clase 7:
	Completar y estudiar exhaustivamente la clase Listado

	Estudiar sobrecarga de operadores y templates

	Ver `Tutorial Qt QVector <https://www.youtube.com/watch?v=Z9u2yDPh57U>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial Qt QList <https://www.youtube.com/watch?v=xx5wIjUwlg8>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial C++ vector <https://www.youtube.com/watch?v=dNb468_AJQI>`_ de `Videos tutoriales de C++ <https://www.youtube.com/playlist?list=PL54fdmMKYUJvS32aLptKVC0AH9bwsavzi>`_


