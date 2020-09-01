.. -*- coding: utf-8 -*-

.. _rcs_subversion:

Clase 02 - PGE 2020
===================
(Fecha: 27 de agosto)

Clase genérica Listado
======================

- Una plantilla genera la definición de una clase. 
- A la instancia concreta de la clase generada, se la denomina especialización.

- La definición de la clase genérica Listado es la siguiente:

.. code-block::

    template< class T > class Listado  {
    private:
        int cantidad;
        int libre;
        T * v;
    
    public:
        Listado( int n = 10 ) : cantidad( n ), libre( 0 ), v( new T[ n ] )  {  }
        bool add( T nuevo );
        T get( int i )  {  return v[ i ];  }
        int length()  {  return libre;  }
    };
    
    template< class T > bool Listado< T >::add( T nuevo )  {
        if ( libre < cantidad )  {
            v[ libre ] = nuevo;
            libre++;
            return true;
        }
        return false;
    }


- Observar que la definición de ``add()`` se realiza off-line con la sintaxis de una función genérica.

- Miembros de clases genéricas definidas off-line deben ser declaradas como funciones genéricas.

.. code-block::

    template< class T > bool Listado< T >::add( T nuevo )  {

        ////////////

    }

Ejercicio 1:
============

- En un archivo de cabecera definir la clase Listado con todos sus métodos off-line
- Agregar un método que inserte un elemento en la posición i desplazando los otros

.. code-block::

	bool insert( int I, T elemento )

- Agregar método que elimine todos los elementos

.. code-block::

	void clear()

- Método que elimine una cantidad x de elementos. Los últimos o los primeros según el bool.

.. code-block::
	
	void erase( int x, bool front_or_back )
	
- Método que elimine el elemento de la posición i.

.. code-block::
	
	void borrar( int i )



