.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 13 - PGE 2020
===================
(Fecha: 8 de octubre)


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



QMainWindow
===========

.. figure:: images/clase08/qmainwindow.png

**QAction**

.. figure:: images/clase08/qaction.png

**QIcon**

.. figure:: images/clase08/qicon.png

:Buscar íconos aquí: http://findicons.com/

Ejercicio 21:
============

- Editor de  código fuente C++

.. figure:: images/clase08/ejercicio.png



CLI >> GUI >> NUI
=================

.. figure:: images/clase11/cli_gui_nui.png
    :target: https://prezi.com/_iqvhrobpe0p/desarrollo/


Ejercicio 22:
============

- Proponer una interfaz gráfica de usuario
- Que sea sólo de una ventana
- Buscar algún sitio, en algún video, alguna aplicación para móvil o desktop
- Replicarla en Qt
- Diseñar tus propias clases Boton y BotonDeslizante
- Usar promoción con QtDesigner
- Acomodar los widgets a mano (sin usar QGridLayout)




**Ejemplo para acomodar widgets a mano**

- Uso de showEvent
- Trabajar con porcentajes
- No uso de QGridLayout
- Usar los métodos de QWidget resize y move.

