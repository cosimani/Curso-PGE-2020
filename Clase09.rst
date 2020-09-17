.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 09 - PGE 2020
===================
(Fecha: 22 de septiembre)



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


Ejercicio 11:
============

- Modificar este ejemplo para que la imagen rote sobre su centro.
- Cada vez que el usuario desplace la ventana Principal, que al soltarlo se coloque centrado en pantalla.





Clase QCompleter
================

.. figure:: images/clase03/qcompleter.png

Ejercicio 7:
============

- Hacer lo mismo pero la base de datos que sea un archivo SQLite.



**Resolución conjunta del ejercicio del MiniExamen 1**


.. code-block::

	#include <QVector>

	template< class T > class Inventario : private QVector< T >  {
	public:
	    Inventario()  {  }
	    void add( T elemento )  {  this->push_front( elemento );  }
	    T get( int posicion )  {  return this->at( posicion );  }
	    int cantidad()  {  return this->size();  }

	    void operator-( int nroRemover )  {
	        nroRemover = qMin( nroRemover, this->cantidad() );
	        this->remove( this->size() - nroRemover, nroRemover );
	    }
	};


.. code-block::
	
	#include <QApplication>
	#include <QDebug>
	#include "inventario.h"

	int main( int argc, char ** argv )  {
	    QApplication a( argc, argv );
	    Q_UNUSED( a );

	    Inventario< int > inventario;
	    inventario.add( 1 );
	    inventario.add( 2 );
	    inventario.add( 3 );
	    inventario.add( 4 );
	    inventario.add( 5 );

	    qDebug() << "Cantidad =" << inventario.cantidad();
	    qDebug() << "Elemento 3 =" << inventario.get( 3 );

	    qDebug() << "----------------";
	    for ( int i = 0 ; i < inventario.cantidad() ; i++ )
	        qDebug() << "i =" << i << ":: elemento =" << inventario.get( i );

	    inventario - 3;

	    qDebug() << "----------------";
	    for ( int i = 0 ; i < inventario.cantidad() ; i++ )
	        qDebug() << "i =" << i << ":: elemento =" << inventario.get( i );

	    inventario - 999;

	    qDebug() << "----------------";
	    for ( int i = 0 ; i < inventario.cantidad() ; i++ )
	        qDebug() << "i =" << i << ":: elemento =" << inventario.get( i );

	    return 0;
	}

**Clase QTreeWidget**

- Permite visualizar una vista en árbol
- Maneja ítems (objetos de la clase QTreeWidgetItem)

.. code-block::

    QTreeWidget *treeWidget = new QTreeWidget;
    treeWidget->setColumnCount(2);
    QList<QTreeWidgetItem *> items;

    QStringList campos;
    campos << "Campo 1" << "Campo 2";

    for (int i = 0; i < 5; ++i)
       items.append(new QTreeWidgetItem(campos));
 
    treeWidget->addTopLevelItems(items);
    treeWidget->show();




	
**Crear un popup para sugerencias (estilo QCompleter pero mejor)**

.. code-block::

	class Vista : public QWidget  {
	    Q_OBJECT

	public:
	    explicit Vista(QWidget *parent = 0);
	    ~Vista();

	private:
	    Ui::Vista *ui;
	    QTreeWidget* popup;
	    QTimer* timer;      
	    QStringList lista;  // La base de datos

	    void crearPopup();
	    bool eventFilter(QObject *obj, QEvent *ev);  // Método virtual de QObject
	    void completarPopup(QVector<QStringList> vector);

	private slots:
	    void slot_sugerencia();
	    void slot_completarLineEdit();
	};


	Vista::Vista(QWidget *parent) : QWidget(parent), ui(new Ui::Vista)  {
	    ui->setupUi(this);

	    lista << "julio" << "carlos" << "miguel";
	    this->crearPopup();
	}


	void Vista::crearPopup()  {
	    popup = new QTreeWidget;
	    popup->setColumnCount(2);
	    popup->setRootIsDecorated(false);  // Elimina el lugar del ícono de la izquierda.
	    popup->header()->hide();  // Oculta la cabecera
	    popup->installEventFilter(this);

	    connect(popup, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(slot_completarLineEdit()));

	    popup->setWindowFlags(Qt::Popup);  // Para que la ventana sea estilo popup
	    timer = new QTimer(this);
	    timer->setSingleShot(true);
	    timer->setInterval(200);

	    // Cada 200 mseg busca coincidencias
	    connect(timer, SIGNAL(timeout()), SLOT(slot_sugerencia()));
	    connect(ui->leBuscar, SIGNAL(textEdited(QString)), timer, SLOT(start()));
	}


	/**
	  * Método virtual de QObject para capturar eventos de teclado y de mouse. Se lo instala
	  * llamando al método installEventFilter(). Si este método devuelve true entonces ninguna
	  * otra implementación de este método en clases derivadas capturará este evento.
	  */
	bool Vista::eventFilter(QObject *obj, QEvent *ev)  {
	    if (obj == popup)  {
	        if (ev->type() == QEvent::MouseButtonPress) {
	            popup->hide();
	            ui->leBuscar->setFocus();
	            return true;
	        }

	        if (ev->type() == QEvent::KeyPress) {
	            bool reconocido = false;
	            int key = static_cast<QKeyEvent*>(ev)->key();
	
	            switch (key) {

	            case Qt::Key_Enter:
	            case Qt::Key_Tab:
	            case Qt::Key_Return:
	                this->slot_completarLineEdit();
	                reconocido = true;
	                break;
	            
	            case Qt::Key_Escape:
	                ui->leBuscar->setFocus();
	                // Si se presiona escape entonces limpiamos.
	                ui->leBuscar->clear();
	                popup->hide();
	                reconocido = true;

	            case Qt::Key_Up:
	            case Qt::Key_Down:
	            case Qt::Key_Home:
	            case Qt::Key_End:
	            case Qt::Key_PageUp:
	            case Qt::Key_PageDown:
	                break;

	            default:
	                // Hace que permanezca el cursor en el QLineEdit para seguir escribiendo
	                ui->leBuscar->event(ev);
	                popup->hide();
	                break;
	            }
	            return reconocido;
	        }
	    }
	    return false;
	}


	/**
	  * Cuando se pulsa enter o se hace clic sobre uno de los ítems sugeridos se llama a este método 
	  * para desglosar el resultado y completar el QLineEdit.
	  */
	void Vista::slot_completarLineEdit()  {
	    timer->stop();
	    popup->hide();
	    ui->leBuscar->setFocus();

	    QTreeWidgetItem *item = popup->currentItem();

	    if (item)  {
	        // Seteamos el QLineEdit con el texto del nombre del producto elegido.
	        ui->leBuscar->setText(item->text(0));
	    }
	}


	/**
	  * Método para sugerir los clientes según lo que se vaya ingresando en el QLineEdit.
	  * Para hacer esto se consulta a la base de datos devolviendo un QVector<QStringList>.
	  */
	void Vista::slot_sugerencia()   {
	    QVector<QStringList> vectorCoincidencias;  // Almacenará las sugerencias
	    QString cadena = ui->leBuscar->text();

	    // Este for se encarga de encontrar las coincidencias. Se sugieren hasta 5.
	    for (int i=0, contador=0 ; i<lista.size() && contador<5 ; i++)  {

	        QString string = lista.at(i);

	        if (string.contains(cadena))  {
	            QStringList sugerencia;
	            sugerencia << string << "Campo";
	            vectorCoincidencias.push_back(sugerencia);
	            contador++;
	        }
	    }
	
	    // Si no existe lo que se busca se limpia el QLineEdit.
	    if (vectorCoincidencias.size() == 0)  {
	        ui->leBuscar->clear();
	        return;
	    }

	    // Completa el popup con las sugerencias
	    this->completarPopup(vectorCoincidencias);
	}


	/**
	  * Completa el QTreeWidget con el resultado de la consulta a la base de datos y lo visualiza.
	  */
	void Vista::completarPopup(QVector<QStringList> vector)  {
	    popup->clear();

	    for (int i = 0; i < vector.size(); ++i) {
	        QTreeWidgetItem * item;
	        item = new QTreeWidgetItem(popup);
	        item->setText(0, vector.at(i).at(0));
	        item->setText(1, vector.at(i).at(1));
	        item->setTextAlignment(1, Qt::AlignRight);  // Para alinear contra la derecha
	    }

	    popup->setCurrentItem(popup->topLevelItem(0));  // Queda seleccionado el primer elemento

	    // Este número 20 es la cantidad de líneas que tiene la lista desplegable
	    int h = popup->sizeHintForRow(0) * qMin(20, vector.size()) + 3;

	    // El ancho del popup es igual al ancho del QLineEdit
	    popup->resize(ui->leBuscar->width(), h);  

	    // Lo posiciona justo abajo del QLineEdit
	    popup->move(ui->leBuscar->mapToGlobal(QPoint(0, ui->leBuscar->height())));

	    popup->setFocus();
	    popup->show();
	}


**Ejercicio** Hacerlo funcionar.


Ejercicio 8:
============

- Definir una clase genérica Vector que herede de QVector.
- Modificar el comportamiento de los siguientes métodos:
	- at() - En vez de obtener el primer elemento con 0 que lo haga con 1, el 1 con 2,...
	- size() - Bloquearlo, que no se pueda usar.
	- float getPromedio() - Si los elementos son int o float, devolver el promedio sino devolver -1


Ejercicio 9:
============

- Cuando alguna búsqueda no exista en la base de datos (QStringList lista), entonces que la agregue..

Ejercicio 10:
============

- En lugar de utilizar un QStringList como base de datos, utilizar una base de datos SQLite
- Agregar esta característica de autocompletado a la clase LineaDeTexto.

Ejercicio 11:
============

- Agregar el método setDiccionario(QString archivo) para agregar un diccionario a la base de datos (QStringList lista).
- Si el diccionario tiene dos columnas, entonces el popup tendrá dos columnas
- Si el diccionario tiene una sola columna, entonces popup de una sola columna
- Sugiere primero las palabras que empiecen con las letras buscadas, luego que sugiera las palabras que las contienen.



