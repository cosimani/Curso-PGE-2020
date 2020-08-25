.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 02 - PGE 2019
===================
(Fecha: 15 de agosto)

Herencia
========

.. code-block::

    template< class T > class Lista : public Listado< T >  {
 
        //////////

    };

- Es posible también que una clase derive de una u otra según se requiera.

.. code-block::

	#include <QString>
	#include <QDebug>
	#include <typeinfo>

	class Real  {
	private:
    	    int colores;

	public:
    	    Real( int colores ) : colores( colores )  {  }
     	    int getDato()  {  return colores;  }
	};


	class Virtual {
	private:
    	    int bits;

	public:
    	    Virtual( int bits ) : bits( bits )  {  }
    	    int getDato()  {  return bits;  }
	};

	template< class T > class Mundo : public T  {
	private:
    	    QString nombre;

	public:
    	    Mundo( QString nombre, int dato ) : T( dato ), nombre( nombre )  {  }

    	    QString toString()  {
        	QString descripcion = "El mundo " + nombre + " es de ";
        	descripcion.append( QString::number( T::getDato() ) );

        	if ( typeid( T ) == typeid( Real ) )
            	    descripcion.append( " colores." );
        	if ( typeid( T ) == typeid( Virtual ) )
            	    descripcion.append( " bits." );

        	return descripcion;
    	    }
    	};

	int main( int, char ** )  {
    	    Mundo< Real > mundo1( "Tierra", 10000 );
    	    Mundo< Virtual > * mundo2 = new Mundo< Virtual >( "StarCraft", 64 );

    	    qDebug() << mundo1.toString();
    	    qDebug() << mundo2->toString();

	    return 0;
	}

**Ejercicio**

- Agregar la características a Mundo para que pueda heredar de cualquier clase, no sólo de Real y Virtual
- Que compile y deje ejecutar la aplicación pero el toString publicar que el Mundo creado no es posible.

Ejemplos:
=========

.. code-block::

	class Cliente : public Persona< int >  {
	private:
	    int cantDolares;

	public:
	    Cliente() : Persona( 1001 ), cantDolares( 10 )  {
	    }
	};

	// Se puede instanciar con:    Cliente cliente;


.. code-block::

	template< class T > class Cliente : public Persona< T >  {
	private:
	    int cantPesos;

	public:
	    Cliente( T id ) : Persona< T >( id ), cantDolares( 600 )  {
	    }
	};

	// Se puede instanciar con:    Cliente< QString > cliente( "Algun nombre" );

.. code-block::

	struct Credencial  {
	    int dni;
	    QString nombre;
	};

	template< class T > class Persona  {
	private:
	    T id;
	    int edad;

	public:
	    Persona( T id ) : id( id ), edad( 0 )  {
	    }

	    T getId()  {
	        return id;
	    }
	};

	int main( int argc, char ** argv )  {
	    Persona< int > juan( 36242 );

	    Persona< QString > carlos( "Carlos" );	 
	    
	    Credencial credencial1;
	    credencial1.dni = 44123456;
	    credencial1.nombre = "Lucas";

	    Persona< Credencial > lucas( credencial1 );	 

	    return 0;
	}

Sobrecarga de operadores 
========================

.. figure:: images/clase02/sobrecarga_operadores.png


Ejemplo:
========

.. code-block::

	class Cliente  {
	private:
	    int saldo;

	public:
	    Cliente() : saldo( 0 )  {
	    }

	    void operator+( int sumando )  {
	        this->saldo += sumando;
	    }

	    void operator-( int sustraendo )  {
	        this->saldo -= sustraendo;
	    }

	    bool operator<( Cliente otroCliente )  {
	        if ( this->saldo < otroCliente.saldo )
	            return true;
	        return false;
	    }
	};

	int main( int argc, char ** argv )  {
	    Cliente juan;

	    Cliente carlos;

	    juan + 50;  // Suma 50 a su cuenta

	    carlos + 100;  // Quita 100 a carlos

	    if ( juan < carlos )  {
	        qDebug() << "juan tiene menos";
	    }

	    return 0;
	}


