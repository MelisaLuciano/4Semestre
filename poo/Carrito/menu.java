import javax.swing.JOptionPane;
public class menu{

	public String inproducto;
	public String comproducto;
	public int op1;


//static porque lo va a usar a clase osea, no lo usan los objetos ...
	public static void main (String [] args){

		//Este es el tipo de dato "inproducto" e inventario es el arreglo

		inproducto inventario[] = new inproducto[10];
		inventario[0] = new abarrote("Leche", "Forti", 13, 14, 6, "13/08/2017");
		inventario[1] = new electrodomestico("Microondas", "LG", 1990, 2.0,5, false);
		inventario[2] = new abarrote ("Galletas", "Cokies", 14, 10, 10, "17/08/2020");
		inventario[3] = new electrodomestico("Computadora", "HP", 1330, 13.0, 7, false);
		inventario[4] = new abarrote ("Pastelillo", "Pinguinos", 10, 11, 19, "19/05/2018");
		inventario[5] = new electrodomestico("Estufa", "Samsung", 1220, 3.5, 3, false);

			//op1 se guarda el valor de lo que se escriba en el cuadro de dialogo
			String op1 = JOptionPane.showInputDialog("Seleccione su opcion \n 1)Agregar producto\n 2)Mostrar producto\n 3)Comprar producto\n 3)Salir");
			//se deben convertir los valores de string a entero
			//la caja de dialogo los toma como string, por eso es String nombre de la variable
			int p3 = Integer.parseInt(op1);

			switch (p3){
				case 1: 
						int contador = 0;
						for ( int i = 0; i < inventario.length; i++){
							if (inventario [i] != null){
								contador ++;
							}
						}
					String op2 = JOptionPane.showInputDialog("Seleccione el tipo de producto \n 1)Abarrote\n 2)Electrodoméstico");
					p3 = Integer.parseInt(op2);
					if (p3 == 1){
						//siempre debe ser String en las cajas de dialogo
						String namep = JOptionPane.showInputDialog("Escriba el nombre del producto");
						String marcap = JOptionPane.showInputDialog("Escriba la marca del producto");
						String idpr = JOptionPane.showInputDialog("Escriba el ID del producto");
						
						int idprr = Integer.parseInt(idpr);//el que esta en el parentesis es el que voy a convertir

						String pricep = JOptionPane.showInputDialog("Escriba el precio del producto");
						double pricepp = Double.parseDouble(pricep);
						String disp = JOptionPane.showInputDialog("Escriba la cantidad disponible del articulo");
						int dispp = Integer.parseInt(disp);
						String fech = JOptionPane.showInputDialog("Escriba la fecha de caducidad");

						//p2 = Double.parseDouble(idpr);
						//Estoy instanciando :v
						//
						inventario[contador+1] = new abarrote (namep, marcap, idprr, pricepp, dispp, fech);
					}
					//ya no lleva parentesis, sino pues esto 7u7
					else{
						String namep = JOptionPane.showInputDialog("Escriba el nombre del producto");
						String marcap = JOptionPane.showInputDialog("Escriba la marca del producto");
						String idpr = JOptionPane.showInputDialog("Escriba el ID del producto");
						int idprr =Integer.parseInt(idpr);
						String pricep = JOptionPane.showInputDialog("Escriba el precio del producto");
						double pricepp = Double.parseDouble(pricep);
						String disp = JOptionPane.showInputDialog("Escriba la cantidad disponible del articulo");
						int dispp = Integer.parseInt(disp);
						String garan = JOptionPane.showInputDialog("El producto tiene garantia? \n 1)si\n 2)no");
						int garann= Integer.parseInt(garan);
						if (garann == 1){
							boolean garant = true;

						}else{
							boolean garant = false;
						}
						//length para saber el tamaño del arreglo}

						inventario[contador +1] = new electrodomestico(namep, marcap, idprr, pricepp, dispp, false);
					}
					int cont = 0;
					for ( int i = 0; i < inventario.length; i++){
							if (inventario [i] != null){
								cont ++;
							}
						}

					System.out.println(cont);
					//se rompe el ciclo y sale del switch
					break;
			case 2:

			abarrote aba = new abarrote("pan", "esperanza", 13, 14, 6, "13/08/2017");
			//Es metodo y debe llevar paréntesis 
			String n = aba.getnombre();
			
				System.out.println(n);

			default:
				System.exit(0);

			}
			System.exit(0);
	} 

		



}