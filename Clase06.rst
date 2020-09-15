.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 06 - PGE 2020
===================
(Fecha: 10 de septiembre)
	

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


**Constructor copia**

.. figure:: images/clase04/constructor_copia.png

**Operador de asignación**

.. figure:: images/clase04/operador_asignacion.png


