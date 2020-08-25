.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 15 - PGE 2019
===================
(Fecha: 17 de octubre)


Ejemplo del Login independiente
===============================

.. code-block:: c++

	#include <QApplication>
	#include "manager.h"

	int main( int argc, char ** argv )
	{
	    QApplication a( argc, argv );

	    Manager manager;
	    manager.iniciar();

	    return a.exec();
	}

.. code-block:: c++

	#ifndef MANAGER_H
	#define MANAGER_H

	#include <QObject>
	#include <QVector>

	#include "login.h"
	#include "formulario.h"

	class Manager : public QObject
	{
	    Q_OBJECT
	public:
	    explicit Manager( QObject * parent = 0 );

	    void iniciar();

	private:
	    Login * login;
	    Formulario * formulario;

	private slots:
	    void slot_ingreso( bool valido, QStringList usuario );

	};

	#endif // MANAGER_H

.. code-block:: c++

	#include "manager.h"

	Manager::Manager( QObject * parent ) : QObject( parent ),
	                                       login( new Login ),
	                                       formulario( new Formulario )
	{

	    connect( login, SIGNAL( signal_usuarioValidado( bool, QStringList ) ), 
	             this, SLOT( slot_ingreso( bool, QStringList ) ) );

	    QVector< QStringList > nuevosUsuarios;

	    QStringList usuario1;  usuario1 << "carlos" << "123";
	    QStringList usuario2;  usuario2 << "miguel" << "1234";
	    QStringList usuario3;  usuario3 << "julio" << "12345";

	    nuevosUsuarios << usuario1 << usuario2 << usuario3;

	    login->setBaseUsuarios( nuevosUsuarios );
	}

	void Manager::iniciar()
	{
	    login->show();
	}

	void Manager::slot_ingreso( bool valido, QStringList usuario )
	{
	    if ( valido )  {
	        login->hide();
	        formulario->show();
	        formulario->setWindowTitle( "Bienvenido: " + usuario.at( 0 ) );
	    }
	    else  {
	        login->close();
	    }
	}

.. code-block:: c++

	#ifndef LOGIN_H
	#define LOGIN_H

	#include <QWidget>
	#include <QVector>
	#include <QStringList>

	namespace Ui {
	    class Login;
	}

	class Login : public QWidget
	{
	    Q_OBJECT

	public:
	    explicit Login( QWidget * parent = 0 );
	    ~Login();

	    /**
	     * @brief setBaseUsuarios Permite agregar usuarios permitidos para 
	              este login. Siempre estara el usuario admin:nimda
	     * @param usuarios Son los nuevos usuarios que se agregan a 
	              este login sin borrar los anteriores.
	     */
	    void setBaseUsuarios( QVector< QStringList > usuarios );

	private:
	    Ui::Login *ui;

	    /**
	     * @brief usuarios Se mantienen todos los usuarios validos para este login. 
	              El QStringList almacena las credenciales usuario:clave
	     */
	    QVector< QStringList > usuarios;

	private slots:
	    void slot_validarUsuario();

	signals:

	    /**
	     * @brief signal_usuarioValidado Se emite cuando un usuario intenta ingresar.
	     * @param valido Si es true entonces el usuario es valido, sino devuelve false.
	     * @param usuario Son las credenciales que el usuario ingresa.
	     */
	    void signal_usuarioValidado( bool valido, QStringList usuario );
	};

	#endif // LOGIN_H

.. code-block:: c++

	#include "login.h"
	#include "ui_login.h"

	Login::Login( QWidget * parent ) : QWidget( parent ),
	                                   ui( new Ui::Login )
	{
	    ui->setupUi( this );

	    QStringList usuarioAdmin;
	    usuarioAdmin << "admin" << "nimda";

	    usuarios << usuarioAdmin;

	    connect( ui->pbIngresar, SIGNAL( pressed() ), this, SLOT( slot_validarUsuario() ) );
	    connect( ui->leClave, SIGNAL( returnPressed() ), this, SLOT( slot_validarUsuario() ) );
	}

	Login::~Login()
	{
	    delete ui;
	}

	void Login::setBaseUsuarios( QVector< QStringList > usuarios )
	{
	    this->usuarios << usuarios;
	}

	void Login::slot_validarUsuario()
	{
	    QStringList usuarioIngresado;
	    usuarioIngresado << ui->leUsuario->text() << ui->leClave->text();

	    if ( this->usuarios.contains( usuarioIngresado ) )
	        emit signal_usuarioValidado( true, usuarioIngresado );
	    else
	        emit signal_usuarioValidado( false, usuarioIngresado );
	}

.. code-block:: c++

	#ifndef FORMULARIO_H
	#define FORMULARIO_H

	#include <QWidget>

	namespace Ui {
	    class Formulario;
	}

	class Formulario : public QWidget
	{
	    Q_OBJECT

	public:
	    explicit Formulario( QWidget * parent = 0 );
	    ~Formulario();

	private:
	    Ui::Formulario *ui;
	};

	#endif // FORMULARIO_H

.. code-block:: c++

	#include "formulario.h"
	#include "ui_formulario.h"

	Formulario::Formulario( QWidget * parent ) : QWidget( parent ),
	                                             ui( new Ui::Formulario )
	{
	    ui->setupUi( this );
	}

	Formulario::~Formulario()
	{
	    delete ui;
	}



Ejercicio 22:
============

- Modificar el ejemplo anterior para disponer de las siguientes clases: Manager, Login, Principal y Ventana (tal como lo vimos en clase).
- Agregar en Login el siguiente método para poder utilizar una base SQLite.

.. code-block:: c++

	bool validarCon( QString archvioSqlite, QString tabla, QString campoUsuario, QString campoClave );

- Dar a este método la funcionalidad que desee, pero es obligatorio que se escriba la documentación en el mismo código.




**Ejemplo de Manager como singleton**

.. code-block:: c++

	#include <QApplication>
	#include "manager.h"

	int main( int argc, char ** argv )
	{
	    QApplication a( argc, argv );

	    Manager::getInstancia()->iniciar();

	    return a.exec();
	}

.. code-block:: c++

	#ifndef MANAGER_H
	#define MANAGER_H

	#include <QObject>
	#include <QVector>

	#include "login.h"
	#include "formulario.h"

	class Manager : public QObject
	{
	    Q_OBJECT

	private:
	    static Manager *instancia;
	    explicit Manager( QObject * parent = 0 );

	public:
	    static Manager *getInstancia();
	    ~Manager();

	    void iniciar();

	private:
	    Login * login;
	    Formulario * formulario;

	private slots:
	    void slot_ingreso( bool valido, QStringList usuario );

	};

	#endif // MANAGER_H

.. code-block:: c++

	#include "manager.h"

	Manager * Manager::instancia = NULL;

	Manager::Manager( QObject * parent ) : QObject( parent ),
	                                       login( new Login ),
	                                       formulario( new Formulario )
	{

	    connect( login, SIGNAL( signal_usuarioValidado( bool, QStringList ) ), 
	             this, SLOT( slot_ingreso( bool, QStringList ) ) );

	    QVector< QStringList > nuevosUsuarios;

	    QStringList usuario1;  usuario1 << "carlos" << "123";
	    QStringList usuario2;  usuario2 << "miguel" << "1234";
	    QStringList usuario3;  usuario3 << "julio" << "12345";

	    nuevosUsuarios << usuario1 << usuario2 << usuario3;

	    login->setBaseUsuarios( nuevosUsuarios );
	}


	Manager * Manager::getInstancia()
	{
	    if( instancia == NULL )
	    {
	        instancia = new Manager();
	    }
	    return instancia;
	}

	Manager::~Manager()
	{
	    if( instancia != NULL )
	    {
	        delete instancia;
	    }
	}

	void Manager::iniciar()
	{
	    login->show();
	}

	void Manager::slot_ingreso( bool valido, QStringList usuario )
	{
	    if ( valido )  {
	        login->hide();
	        formulario->show();
	        formulario->setWindowTitle( "Bienvenido: " + usuario.at( 0 ) );
	    }
	    else  {
	        login->close();
	    }  
	}


Ejercicio 23:
============

- Hacer funcionar este ejemplo con Formulario, Login y Manager como singleton.
- Agregar la característica a Formulario para que se puedan agregar nuevos usuarios a login.
- Al cerrar Formulario, no se cierra el programa sino que vuelve a Login para que pueda usar el usuario nuevo.
- Cuando un usuario se loguea, Login se debe ocultar.



**Ejemplos programados en clase**

- `ManagerSingleton-v1.zip <https://github.com/cosimani/Curso-PGE-2019/blob/master/sources/clase15/ManagerSingleton-v1.zip?raw=true>`_

- `ManagerSingleton-v2.zip <https://github.com/cosimani/Curso-PGE-2019/blob/master/sources/clase15/ManagerSingleton-v2.zip?raw=true>`_

- `ManagerSingleton-v3.zip <https://github.com/cosimani/Curso-PGE-2019/blob/master/sources/clase15/ManagerSingleton-v3.zip?raw=true>`_

- `ManagerSingleton-v4.zip <https://github.com/cosimani/Curso-PGE-2019/blob/master/sources/clase15/ManagerSingleton-v4.zip?raw=true>`_
