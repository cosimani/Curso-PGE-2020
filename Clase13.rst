.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 13 - PGE 2019
===================
(Fecha: 8 de octubre)


Ejercicio 20
============

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


Utilización de cámaras de video con Qt
======================================

- Clase QCamera: Controlador de las cámaras
- Clase QCameraViewfinder: Es un QWidget visualizador de imágenes de la cámara
- Clase QCameraInfo: Listado de las cámaras disponibles y la info de cada una
- Requiere en el .pro: QT += multimedia multimediawidgets #Qt5.3 mínimo

**Publicar la descripción de las cámaras disponibles**

.. code-block::

	QList< QCameraInfo > cameras = QCameraInfo::availableCameras();
	for ( int i = 0 ; i < cameras.size() ; i++ )  
	    qDebug() << cameras.at( i ).description();

**Instanciar QCamera y mostrar los frames sobre el QCameraViewfinder**

.. code-block:: c++

    QCameraInfo cameraInfo = cameras.at( 0 );
    QCamera * camera = new QCamera( cameraInfo );

    QCameraViewfinder * visor = new QCameraViewfinder;

    camera->setViewfinder( visor );
    camera->start();

    visor->show();

**Creación de un visor promovido a QWidget para QtDesigner**

.. code-block:: c++

	// Puede estar sólo en el .h (en visor.h)
	#ifndef VISOR_H
	#define VISOR_H

	#include <QCameraViewfinder>

	class Visor : public QCameraViewfinder  {
	    Q_OBJECT
	public:
	    explicit Visor( QWidget * parent = 0 ) : QCameraViewfinder( parent )  {   }
	};

	#endif // VISOR_H

**Ejercicio**

- Crear una aplicación con un QCameraViewfinder promovido a QWidget en QtDesigner
- Un botón "Mostrar imagen" para que encienda la cámara y muestre la imagen
- Que complete un QComboBox con las cámaras disponibles
- Un QPushButton para iniciar la cámara seleccionada

**Resolución**

- `Código fuente <https://github.com/cosimani/Curso-PGE-2019/blob/master/resources/clase13/camera.zip?raw=true>`_

Ejercicio 15:
============

- Siguiendo el ejercicio anterior, crear una carpeta donde se irán guardando las imágenes de la cámara
- Colocar un QSlider con rango entre 500 y 5000, paso de 500, que indica una cantidad en mili segundos
- Descargar en el disco las imágenes en archivos jpg cada un tiempo según el QSlider anterior
- El nombre del archivo tendrá la fecha y hora en que fue capturada

Ejercicio 16:
============

- Siguiendo el ejercicio anterior, usar todas las imágenes de esa carpeta mostrándolas en un QWidget cada 100 mseg.


Análisis píxel a píxel
======================

- **Ejemplo:** Dejar sólo el componente rojo

.. code-block::

    QPixmap pixMap = ui->visor->grab();  // Para llevar el QWidget a QImage
    QImage image = pixMap.toImage();

    for ( int x = 0 ; x < image.width() ; x++ )  {
        for ( int y = 0 ; y < image.height() ; y++ )  {
            QRgb rgb = image.pixel( x, y );  // typedef unsigned int QRgb;
            QRgb nuevoValorRgb = qRgb( qRed( rgb ), 0, 0 );
            image.setPixel( x, y, nuevoValorRgb );
        }
    }



Base de datos con SQLite (repaso)
========================

.. figure:: images/clase09/sqlite1.png

.. figure:: images/clase09/sqlite2.png

.. figure:: images/clase09/sqlite3.png

**Ejercicio**

.. figure:: images/clase09/ejercicio4.png

.. figure:: images/clase09/ejercicio4a.png

.. figure:: images/clase09/ejercicio4b.png

**Para independizar del SO**

.. figure:: images/clase09/independizar.png

**Consulta a la base de datos**

.. figure:: images/clase09/consultar1.png

.. figure:: images/clase09/consultar2.png



