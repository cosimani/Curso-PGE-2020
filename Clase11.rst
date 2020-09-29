.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 11 - PGE 2020
===================
(Fecha: 1 de octubre)


Ejercicio 18:
============

- Agregar el método setDiccionario(QString archivo) para agregar un diccionario a la base de datos (QStringList lista).
- Si el diccionario tiene dos columnas, entonces el popup tendrá dos columnas
- Si el diccionario tiene una sola columna, entonces popup de una sola columna
- Sugiere primero las palabras que empiecen con las letras buscadas, luego que sugiera las palabras que las contienen.





Creación y uso de librerías dinámicas
=====================================

.. figure:: images/clase08/librerias.png

.. figure:: images/clase08/librerias01.png

.. figure:: images/clase08/librerias02.png

.. figure:: images/clase08/librerias03.png


Ejemplo
=======

- Crear una clase Login que tenga una funcionalidad independiente
- Crear un librería dinámica que la contenga
- Usar esta librería en otro proyecto

**clase Login que puede servir para usar en este ejemplo**

- Sólo se muestra el código de los archivo login.h y login.cpp
- Tener en cuenta que la GUI de este login está creado con el QtDesigner
- Sus widgets en el layout son: ``ui->leUsuario`` ``ui->leClave`` ``ui->pb``

.. code-block:: c++

	// Archivo login.h ////////////////////////////

	#ifndef LOGIN_H
	#define LOGIN_H

	#include <QWidget>
	#include <QVector>
	#include <QStringList>

	namespace Ui  {
	    class Login;
	}

	class Login : public QWidget  {
	    Q_OBJECT

	public:
	    explicit Login( QWidget * parent = 0 );
	    ~Login();
	    void agregarUsuario( QString usuario, QString clave );

	private:
	    Ui::Login *ui;
	    QVector< QStringList > baseUsuarios;

	signals:
	    void signal_usuarioLogueado();

	private slots:
	    void slot_validarUsuario();
	};

	#endif // LOGIN_H

.. code-block:: c++

	// Archivo login.cpp ////////////////////////////

	#include "login.h"
	#include "ui_login.h"

	Login::Login( QWidget * parent ) : QWidget( parent ), ui( new Ui::Login )  {
	    ui->setupUi( this );

	    ui->leClave->setEchoMode( QLineEdit::Password );

	    connect( ui->pb, SIGNAL( pressed() ), this, SLOT( slot_validarUsuario() ) );
	}

	Login::~Login()  {
	    delete ui;
	}

	void Login::agregarUsuario( QString usuario, QString clave )  {
	    QStringList usuarioNuevo;
	    usuarioNuevo << usuario << clave;
	    baseUsuarios.append( usuarioNuevo );
	}

	void Login::slot_validarUsuario()  {
	    QStringList usuarioIngresado;
	    usuarioIngresado << ui->leUsuario->text() << ui->leClave->text();

	    if ( baseUsuarios.contains( usuarioIngresado) )  {
	        emit signal_usuarioLogueado();
	    }
	}


Ejercicio 19
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



