public class vehiculo{
	String matricula;
	String marca;
	String modelo;
	String color;
	double tarifa;
	boolean disponible;

	//Metodos set y get de la clase vehiculo

		public String getmatricula (){
			return this.matricula;

		}	

		public String getmarca (){
			return this.marca;
		}

		public String getmodelo (){
			return this.modelo;
		}

		public String getcolor (){
			return this.color;
		}
		public double gettarifa (){
			return this.tarifa;
		}
		public boolean getdisponible (){
			return this.disponible;
		}
		public void settarifa (double tarifa){
			this.tarifa= tarifa;

		}
		public void setdisponible (boolean disponible){
			this.disponible = disponible;

		}
}
// se accede a los atributos de la clase vehiculo utilizando get
//get para consultar estado de un objeto
//set para modificar su estado
//los metodos set solo se definen para los atributos que pueden ser modificados despues de que se ha creado el objeto
//en el caso anterior es necesario definir -> settarifa (double tarifa)
//esto para modificar la tarifa del vehiculo 