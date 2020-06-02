public class abarrote extends inproducto{

	private String fecha;

	public abarrote (){

		super ();

		fecha = null;

		}
		public abarrote (String nombrep, String marcap, int idp, double preciop, int disponibilidad, String fecha){

			super(nombrep, marcap, idp, preciop, disponibilidad);
			this.fecha = fecha;//Se diferencia un nombre del otro :v refieriendose el primero al nombre principal y el otro a la referencia.

		}
}