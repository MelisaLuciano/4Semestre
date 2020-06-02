class cliente{//Inicia mi clase cliente
		private int id; //atributos
		private String nombre; 
		private String direccion;
		private double monto;
		public cliente(){ //Constructor por omisión, inicializa en 1500 al crear un objeto de tipo cliente
			id = 1514256;
			nombre = "Carlos";
			direccion = "Col. Guadalupe Chalma, Calle Guerrero, Mz. 13, Lt. 16";
			monto = 1500.00;
  		}
  		//Empiezan las funciones pertenecientes específicamente a éste objeto
  		public void getinfo(){//Imprime en consola información adicional de la cuenta
  			System.out.println("Cuenta abierta: ");
			System.out.println("Id: " + id);
			System.out.println("Nombre: " + nombre);
			System.out.println("Direccion: " + direccion);
  		}
   		public double getmonto(){ //Obtiene el monto actual
   			return monto; 
   		}
   		//La función retirar tiene especificaciones que obtuve de Yaxkin, tal vez entendí mal así que queda a criterio propio hacerlas así o no
   		public int retirar(double lol){ //Retira dinero del monto
   			/*Los "return 0" controlan que se cierre el método (o función) una vez que ya haya encontrado
			su determinada condición (if) y no entre a las demás (por pura precaución), para eso el metódo (o función)
			es de tipo int*/
   			if(lol > monto){//Condición para no retirar una cantidad superior a la existente
   				ventanas.mensaje("La cantidad a retirar supera a la cantidad existente");
   				return 0;
   			}
   			if((monto - lol) >= 1000){//Condición para retirar directamente si la resta no es menor a 1000
				monto = monto - lol;
				ventanas.mensaje("Retirados exitosamente: $" + lol);
				return 0;
			}
   			if(monto < 1000){//Condición si el monto ya es menor a 1000 (se tendrá que cobrar comisión)
   				if((lol + 30.50) > monto){//Condición si el monto es menor a la cantidad más la comisión
   					ventanas.mensaje("No es posible retirar esa cantidad");
   					return 0;
   				}
   				else{//si el monto es mayor o igual a la cantidad más la comisión
   					ventanas.mensaje("Retirados exitosamente: $" + lol);
   					ventanas.mensaje("Tu cuenta tiene menos de $1000, se te cobraran $30.50 por manejo de cuenta");
   					monto = (monto - lol) - 30.50;
   					return 0;
   				}
			}
			if((monto - lol) < 1000){//Condición si el monto menos la cantidad será menor a 1000(habrá que cobrar comisión)
				if((monto - lol) >= 30.50){//Si quedará dinero de la resta para poder cobrar la comisión
					ventanas.mensaje("Retirados exitosamente: $" + lol);
   					ventanas.mensaje("Tu cuenta tiene menos de $1000, se te cobraran $30.50 por manejo de cuenta");
					monto = monto - lol - 30.50;
					return 0;
				}
				else{//Si no quedará dinero de la resta del monto menos la cantidad para poder cobrar la comisión
					ventanas.mensaje("No es posible retirar esa cantidad");
					return 0;
				}
			}
 			return 0;
 		}
   		public void setmonto(double lol){//Deposita dinero en el monto
 			monto = monto + lol; 
 			ventanas.mensaje("Depositados exitosamente: $" + lol);
 		}
 	}
public class practica1{
	public static void main(String []A){
		cliente Carlos = new cliente();//Creo mi objeto tipo cliente con el constructor por omisión (sin parámetros)
		Carlos.getinfo();//Adorno extra
		int a;
		String valor;
		double v;
	    String opt;
	    do{//Inicio del ciclo general que controla las repeticiones del programa
			opt = ventanas.valor("Selecciona una opcion del menu\n1.- Ver saldo\n2.- Depositar\n3.- Retirar\n4.- Salir");//Menú
			a = new Integer(opt);//convierto la opción del menú ingresada de string a entero
			switch(a){//Opciones para cada caso del ménú
				case 1:
					ventanas.mensaje("Tu saldo es de $" + Carlos.getmonto());
					break;
				case 2:
					valor = ventanas.valor("Ingrese la cantidad a depositar");
					//Obtengo la cantidad a depositar en forma de string
					v = Double.parseDouble(valor); //Convierto la cantidad de String a Double
					Carlos.setmonto(v);//Llamo a la función que deposita
					break;
				case 3://lo mismo que en el anterior pero para retirar
					valor = ventanas.valor("Ingrese la cantidad a retirar");
					v = Double.parseDouble(valor);
					Carlos.retirar(v);
					break;
				case 4:
					System.out.println("Cuenta cerrada...");//Adorno extra
					break;
				default:
					ventanas.mensaje("Opcion no valida");
			}
		}while(a!=4);//ciclo que controla que no se cierre el programa hasta escoger la opción 4
	}
}