//package ejercicio;

public class Libro{

	/*atributos*/
	private int ISBN;
	private String titulo;
	private String autor;
	private int numpaginas;

	//hacer un constructor que construye el objeto :v 
	/*Constructores*/
	public Libro (int pISBN, String pTitulo, String pAutor, int pNumpaginas){
		

		ISBN= pISBN;  //el morado es el atributo 
		titulo = pTitulo;
		autor = pAutor;
		numpaginas = pNumpaginas;


	} /*si no hay constructor por defecto java crea una especia de constructor, lo crea solo, */


	/*Metodos: los cuales permiten acceder a los valores */

	public int getISBN(){

		return ISBN;
	}

		public void setISBN (int ISBN){

			this.ISBN = ISBN;
		}
			public String getTitulo (){

				return titulo;
			}
				public String setTitulo (){

					this.titulo = titulo;
				}
					public void getAutor (){

						return autor;
					}
						public String setAutor (){

							this.autor = autor;
						}
							public int getNumpaginas (){

								return numpaginas;
							}
								public int setNumpaginas (){

									this.numpaginas =numpaginas;
								}



	/*to string personaliza el estado del objeto cuando se muestre nos devolvera el nombre del libro y blah...*/							
	public String toString (){

		return "El libro"+titulo+"con ISBN" +su_ISBN+ "creado por el autor" +su_autor+ "tiene" +num_paginas+ "paginas";


	}

}