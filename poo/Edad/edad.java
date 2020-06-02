//package edades;
import javax.swing.JOptionPane;

public class edad{

	public static void main (String [] args){
		int dia =0;
		int mes = 0;
		int anio = 0;
		boolean contador = false;
do {// ciclo donde hazlo y después preguntas 

		
		String  diaa = JOptionPane.showInputDialog("Ingrese su dia de nacimiento: ");
					dia = Integer.parseInt(diaa);

					if (dia > 0 && dia <32){
						JOptionPane.showMessageDialog(null, "El dia de tu nacimiento es: "+dia);
						contador = true;
					}else{
						JOptionPane.showMessageDialog(null, "Numero invalido");

					}
	}while (contador != true); // lo hago y después veo que onda 

contador = false; // no la declaro, le asigno otro valor
do{

	String mess = JOptionPane.showInputDialog("Ingrese su mes de nacimiento: ");
					mes = Integer.parseInt(mess);
					if (mes > 0 && mes < 13){
						JOptionPane.showMessageDialog(null, "El mes de tu nacimiento es: "+mes);
						contador = true;
					}else{
						JOptionPane.showMessageDialog(null, "Numero invalido");
					}
	
}while (contador != true);

contador = false; // tambien le asigno otro valor, porque si no los toma en cuenta como true
do {
	
	String anioo = JOptionPane.showInputDialog("Ingrese su anio de nacimiento: ");
					anio = Integer.parseInt(anioo);
					if (anio > 1960 && anio < 2017 ){
					JOptionPane.showMessageDialog(null, "El anio de tu nacimiento es: "+anio);
						contador = true;
					}else{
						JOptionPane.showMessageDialog(null, "Numero invalido");
					}
	
	}while (contador != true);
		fecha f1 = new fecha(); // se instancia el objeto con parametro
		int anioA = f1.getAnio();
		int aniof = anioA-anio;
		int auxA = f1.getMes();
		int auxf = auxA - mes;
		int diax = 32 - dia;
		int diaA = diax -f1.getDia();
		int diaF = diaA - diax;
		JOptionPane.showMessageDialog(null, "Su edad es: "+auxf);
	}

	}


	/*public int calcular(){// recibe parámetros

		fecha f1 = new fecha(); // se instancia el objeto con parametro
		int anioA = f1.getAnio();
		int anioF = anio-anioA;
	}*/
	// instanciar un objeto del tipo fecha+
	//metodo get dia , mes y año, se instancia aqui de la clase fecha se hacen variables del top entero, se declara la variable dia actual igual a fecha.getdia() este emtodo regresa el dia actual y se tiene el dia actual 
