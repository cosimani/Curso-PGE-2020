.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 08 - PGE 2019
===================
(Fecha: 12 de septiembre)


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