public class electrodomestico extends inproducto{

	private boolean garantia;

	public electrodomestico(){

		super (); //se inicializan los valores de la clase inproduto :v es el padre de la clase :v
		garantia= false;

	}
	public electrodomestico (String nombrep, String marcap, int idp, double preciop, int disponibilidad, boolean garantia){

		//mandar a llamar al constructor de la clase padre por parametros

		super (nombrep, marcap, idp, preciop, disponibilidad);
		this.garantia = false;

	}
}