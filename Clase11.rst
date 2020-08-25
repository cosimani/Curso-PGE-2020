.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 11 - PGE 2019
===================
(Fecha: 26 de septiembre)

Ejercicio 12
============

- Utilizar la clase Login (de la clase pasada).
- Utilizar la clase LineaDeTexto.
- LineaDeTexto debe tener las carecterísticas que hemos ido agregando (las sugerencias, los operadores, etc.)
- Crear una librería dinámica con estas clases.
- Crear una carpeta con subcarpetas con los archivos importantes (.h .dll .a)
- Usar esta librería en otro proyecto para probar su funcionamiento.


**Esquema para creación y uso de librerías**

.. figure:: images/clase11/cuadro_librerias.jpg

Uso de una clase propia con QtDesigner
======================================

- Deben heredar de algún QWidget
- Colocamos el widget (clase base) con QtDesigner
- Clic derecho "Promote to"

.. figure:: images/clase07/qtdesigner.png
					 
- Base class name: QLabel
- Promoted class name: MiLabel
- Header file: miLabel.h
- Add (y con esto queda disponible para promover)


- La clase MiLabel deberá heredar de QLabel
- El constructor debe tener como parámetro:

.. code-block:: c++

	MiLabel( QWidget * parent = 0 );  // Esto en miLabel.h

	MiLabel::MiLabel( QWidget * parent ) : QLabel( parent )  {  // Esto en miLabel.cpp
	
	}



