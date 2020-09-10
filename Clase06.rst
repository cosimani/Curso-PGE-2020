.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 06 - PGE 2020
===================
(Fecha: 10 de septiembre)
	

Para Opcionables y Mini Examen
==============================

:Tarea para Clase 7:
	Completar y estudiar exhaustivamente la clase Listado

	Estudiar sobrecarga de operadores y templates

	Ver `Tutorial Qt QVector <https://www.youtube.com/watch?v=Z9u2yDPh57U>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial Qt QList <https://www.youtube.com/watch?v=xx5wIjUwlg8>`_ de `Videos tutoriales de Qt <https://www.youtube.com/playlist?list=PL54fdmMKYUJvn4dAvziRopztp47tBRNum>`_

	Ver `Tutorial C++ vector <https://www.youtube.com/watch?v=dNb468_AJQI>`_ de `Videos tutoriales de C++ <https://www.youtube.com/playlist?list=PL54fdmMKYUJvS32aLptKVC0AH9bwsavzi>`_




**Copiar objetos**

- El operador = supone la asignación del operando de la derecha en el izquierdo
- Si ``p1`` y ``p2`` son objetos de la clase ``Persona``

.. code-block:: c
	
	p1 = p2;  // Esta asignación copia los valores de p2 en p1

- El operador = supone la asignación miembro a miembro
- En este caso, el compilador define automáticamente el ``operator=``
- Realiza la asignación miembro a miembro
- Por otro lado, cuando se crea un nuevo objeto

.. code-block:: c
	
	Persona p1 = p2; 

- No implica ninguna asignación sino que se invoca a un constructor especial (constructor copia).
- Es equivalente a:

.. code-block:: c
	
	Persona p1( p2 );

.. figure:: images/clase04/copiar_objetos.png

**Constructor copia**

.. figure:: images/clase04/constructor_copia.png

**Operador de asignación**

.. figure:: images/clase04/operador_asignacion.png



**Clase genérica con argumento por defecto**

.. figure:: images/clase03/por_defecto.png

**Declaración adelantada**

.. figure:: images/clase03/declaracion_adelantada.png

**Miembros estáticos**

.. figure:: images/clase03/miembros_estaticos.png


Ejercicio 8:
==========

- Definir la clase ``LineaDeTexto`` que herede de ``QLineEdit``
- Sobrecargar el ``operator+`` ``operator=`` y el contructor copia para que se puede ejecutar la siguiente línea de código:
	
.. code-block:: c
	
	linea = linea1 + linea2;  
	// Los tres son objetos LineaDeTexto y la suma devuelve un LineaDeTexto con los textos concatenados
	

Ejercicio 9:
============

- Agregar a la clase ``LineaDeTexto`` las características para permitir ejecutar la siguiente función ``main()``


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

