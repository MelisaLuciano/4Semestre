public class agenda{


	//Atributos

	public String nombre;
	//public direccion d;
	public String correo;
	public int numero;


	//Constructores
	//() = no revibe datos
	//constructor por default
	public agenda (){

		nombre = new nombre ("No registrado");
		correo = new correo ("No registrado");
		numero = new numero ("No registrado");

	}

	//recibe los atributos 

	public agenda (String nom, String co, int num){

		this.nombre = nom;
		this.correo = co;
		this.numero = num;


	}
	//cosntructor por copia 
	public agenda (agenda agen){

		this.nombre = agen.nombre;
		this.correo = agen.correo;
		this.numero = agen.numero;
	}

	//metodos  




}