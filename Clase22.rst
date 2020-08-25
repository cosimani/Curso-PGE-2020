.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 22 - PGE 2019
===================
(Fecha: 12 de noviembre)



Ejercicio 39:
============

- Descargar la escena `Habitación <https://github.com/cosimani/Curso-PGE-2018/blob/master/sources/clase19/Habitacion.zip?raw=true>`_

- Replicar lo que se visualiza en el siguiente video: https://www.youtube.com/watch?v=Jr_luYdSfRE



**Podemos ahora llevar las imágenes de la cámara como textura a OpenGL**

.. code-block:: c++

	class Visual : public Ogl  {
		Q_OBJECT
	public:
		Visual();
		void iniciarCamara();

	protected:
		void initializeGL();
		void resizeGL( int ancho, int alto );
		void paintGL();

	private:
		Capturador * capturador;
		QCamera * camera;

		void cargarTexturas();
		void cargarTexturaCamara();

		unsigned char * texturaCielo;
		unsigned char * texturaMuro;
		GLuint idTextura[ 2 ];

		unsigned char * texturaCamara;
		GLuint idTexturaCamara[ 1 ];
	};

	void Visual::iniciarCamara()  {
		capturador = new Capturador;

		QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

		for ( int i = 0 ; i < cameras.size() ; i++ )  {
			qDebug() << cameras.at( i ).description();

			if ( cameras.at( i ).description().contains( "Truevision", Qt::CaseInsensitive ) )  {
				camera = new QCamera( cameras.at( i ) );
				camera->setViewfinder( capturador );
				camera->start(); // to start the viewfinder
			}
		}

		glGenTextures( 1, idTexturaCamara );
	}

	void Visual::cargarTexturaCamara()  {

		QVideoFrame frameActual = capturador->getFrameActual();
		texturaCamara = frameActual.bits();

		glBindTexture( GL_TEXTURE_2D, idTexturaCamara[ 0 ] );  // Activamos idTextura.
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); 

		glTexImage2D( GL_TEXTURE_2D, 
		              0, 
		              3, 
		              frameActual.width(), 
		              frameActual.height(), 
		              0, 
		              GL_BGRA, 
		              GL_UNSIGNED_BYTE, 
		              texturaCamara );
	}

**Ejercicio:**

- Crear una escena con OpenGL con glOrtho para mostrar como textura las imágenes de la cámara en un QUADS.
- Luego probar con gluPerspective

**Resolución**

- Descargar `Código fuente <https://github.com/cosimani/Curso-PGE-2018/blob/master/sources/clase19/camaraOgl.zip?raw=true>`_

Ejercicio 40:
============

- Dentro de la habitación elegir una pared para colocar un monitor LCD con las imágenes de la cámara.

Ejercicio 41:
============

- En el ejercicio de la Habitación, mejorar los movimientos que se realizan con el mouse.

Ejercicio 42:
============

- Con la barra espaciadora se deberá saltar dentro de la escena.


Cálculo de la tercer nota
^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c++

	Nota final = Promedio de (
	                           Cuestionario 1
	                           Cuestionario 2
	                           Mini Examen 1
	                           Mini Examen 2
	                           Promedio de ( Ejercicios 1 2 y 3 )
	                           Promedio de ( Ejercicios 4 5 y 6 )
	                           Promedio de ( Ejercicios 7 8 y 9 )
	                           Promedio de ( Ejercicios 10 11 y 12 )
	                         )




