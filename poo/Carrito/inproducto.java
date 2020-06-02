public class inproducto{

	public String nombrep;
	public String marcap;
	public int idp;
	public double preciop;
	public int disponibilidad;

	//Creando los constructores
// por omision 
	public inproducto (){
		nombrep = null;
		marcap =  null;
		idp = 0;
		preciop = 0.0;
		disponibilidad = 0;

	}
	//metodo es una funcion y pertenece a una clase
	public String getnombre (){
		return this.nombrep;

	}
	//constructor con parámetros :v

		public inproducto(String nombrep, String marcap, int idp, double preciop, int disponibilidad){

			this.nombrep = nombrep;
			this.marcap = marcap;
			this.idp = idp;
			this.preciop = preciop;
			this.disponibilidad = disponibilidad;


		}




}