package edades;
import java.util.*; //Estoy importando todas las lineas util
public class fecha{

	int anio;
	int mes;
	int dia;
// cosntructor lleva el nombre de la clase
	/*public fecha (int anio, int mes, int dia){
		this.anio = anio;
		this.mes = mes;
		this.dia = dia;
	}*/
	public static void mostrar (){

     Calendar fecha = new GregorianCalendar();       
	 int anio = fecha.get(Calendar.YEAR);
     int mes = fecha.get(Calendar.MONTH);
     int dia = fecha.get(Calendar.DAY_OF_MONTH);
     System.out.println("Fecha Actual: "+ dia + "/" + (mes+1) + "/" + anio);

	}

	public int getAnio(){
	Calendar fecha = new GregorianCalendar();  //Necesito el objeto para usar el metodo get
	int anio = 0;
	anio =fecha.get(Calendar.YEAR);
	return anio;	
	}
	public int getMes(){
     Calendar fecha = new GregorianCalendar();  
	int mes = 0;
	mes = fecha.get(Calendar.MONTH);
	return mes;
	}
	public int getDia(){
	Calendar fecha = new GregorianCalendar();  
	int dia = 0;
	dia = fecha.get(Calendar.DAY_OF_MONTH);
	return dia;
	}
}

//metodos para obterner dia mes y año, 