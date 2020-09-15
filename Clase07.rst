.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 07 - PGE 2019
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


**Clase genérica con argumento por defecto**

.. figure:: images/clase03/por_defecto.png

**Declaración adelantada**

.. figure:: images/clase03/declaracion_adelantada.png

**Miembros estáticos**

.. figure:: images/clase03/miembros_estaticos.png


Ejercicio 8:
==========

- Definir la clase ``LineaDeTexto`` que herede de ``QLineEdit``
- Sobrecargar el ``operator+`` ``operator=`` y el constructor copia para que se puede ejecutar la siguiente línea de código:
	
.. code-block:: c
	
	linea = linea1 + linea2;  
	// Los tres son objetos LineaDeTexto y la suma devuelve un LineaDeTexto con los textos concatenados
	

Ejercicio 9:
============

- Haga funcionar la siguiente función ``main()``


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



**Una opción para la creación de la clase LineaDeTexto:**

.. code-block::

	#include <QApplication>
	#include <QLineEdit>
	#include <QString>

	class LineaDeTexto : public QLineEdit  {
	    // Q_OBJECT 
	    // Si usamos Q_OBJECT sin separar la definicion de esta clase en su .h y .cpp puede no compilar
	    // Recordar que sin el Q_OBJECT no podremos definir signals ni slots en esta clase

	public:
	    LineaDeTexto( QString texto = "" ) : QLineEdit( texto )  {  }

	    // El constructor copia debe invocar explicitamente al constructor de 
	    // la clase base para que el compilador no tire un warning
	    LineaDeTexto( const LineaDeTexto & linea ) : QLineEdit()  {
	        this->setText( linea.text() );
	    }

	    LineaDeTexto& operator=( const LineaDeTexto & linea )  {
	        this->setText( linea.text() );
	        return *this;
	    }

	    LineaDeTexto operator+( const LineaDeTexto & linea )  {
	        return LineaDeTexto( this->text() + linea.text() );
	    }
	};

	int main( int argc, char *argv[] )  {
	    QApplication a( argc, argv );
	    LineaDeTexto linea1( "Hola " );
	    LineaDeTexto linea2( "che" );
	    LineaDeTexto total;

	    total = linea1 + linea2;
	    total.show();

	    return a.exec();
	}


Ejercicio 5:
============

- Incorporar LineaDeTexto a un proyecto de Qt para promocionarlo en QtDesigner
- Crear un Formulario con QtDesigner que tenga 4 LineaDeTexto promocionadas
- El formulario será para alta de personas
- Un campo para Nombre, otro para Apellido, para DNI y uno para Nombre completo.
- Esta última LineaDeTexto concatenará en tiempo real el nombre y apellido usando el operator+ de LineaDeTexto


Captura de eventos con eventFilter
==================================

- En un QWidget dibujar una imagen de 50x50.
- Con un QTimer hacer rotar la imagen cada 20 mseg.
- Permitir desplazar la imagen con las teclas y usando eventFilter.
- Utilizar los métodos rotate y translate de QPainter.

.. code-block::

	#include <QWidget>

	class QTimer;
	class QImage;

	namespace Ui  {
	    class Principal;
	}

	class Principal : public QWidget  {
	    Q_OBJECT

	public:
	    explicit Principal( QWidget * parent = 0 );
	    ~Principal();

	private:
	    Ui::Principal *ui;
	    QTimer* timer;
	    int rotacion, transX, transY;
	    QImage * image;

	protected:
	    void paintEvent( QPaintEvent * e );
	    bool eventFilter( QObject *, QEvent * );

	private slots:
	    void slot_ciclos();
	};


	#include "principal.h"
	#include "ui_principal.h"
	#include <QTimer>
	#include <QPainter>
	#include <QKeyEvent>
	#include <QImage>



	Principal::Principal( QWidget * parent ) : QWidget( parent ), 
	                                           ui( new Ui::Principal ),
	                                           rotacion( 0 ), 
	                                           transX( 0 ), 
	                                           transY( 0 )
	{
	    ui->setupUi( this );
	    this->installEventFilter( this );
	    image = new QImage( ":/User.png" );
	    timer = new QTimer;
	    timer->setInterval( 20 );
	    connect( timer, SIGNAL( timeout() ), SLOT( slot_ciclos() ) );
	    timer->start();
	}

	Principal::~Principal()  {
	    delete ui;
	}

	void Principal::paintEvent( QPaintEvent * e )  {
	    QPainter* p = new QPainter( this );
	    p->translate( this->width() / 2 + transX, this->height() / 2 + transY );
	    p->rotate( 10*++rotacion );
	    p->drawImage( 0, 0, *image );
	    if ( rotacion >= 360 )
	        rotacion = 0;
	}

	void Principal::slot_ciclos()  {
	    this->repaint();
	}

	bool Principal::eventFilter( QObject * obj, QEvent * e )  {
	    if ( obj == this )  {
	        if ( e->type() == QEvent::KeyPress )  {
	            int key = static_cast< QKeyEvent * >( e )->key();

	            switch( key )  {

	            case Qt::Key_Up:
	                transY -= 10;
	                break;
	            case Qt::Key_Down:
	                transY += 10;
	                break;
	            case Qt::Key_Left:
	                transX -= 10;
	                break;
	            case Qt::Key_Right:
	                transX += 10;
	                break;
	            case Qt::Key_Escape:
	                this->close();
	                break;
	            }

	            // Devolvemos true para indicar que este evento ya lo controlamos aquí
	            // y no es necesario que se propague para que alguien más lo controle.
	            return true;  
	        }
	    }

	    // Esto es para que la clase base decida si necesita controlar los eventos
	    // que no estamos capturando nosotros.
	    return QWidget::eventFilter( obj, e );
	}


Ejercicio 6:
============

- Modificar este ejemplo para que la imagen rote sobre su centro.
- Cada vez que el usuario desplace la ventana Principal, que al soltarlo se coloque centrado en pantalla.



Clase QCompleter
================

.. figure:: images/clase03/qcompleter.png

Ejercicio 7:
============

- Hacer lo mismo pero la base de datos que sea un archivo SQLite.

