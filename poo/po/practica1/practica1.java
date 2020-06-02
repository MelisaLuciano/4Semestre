import javax.swing.JOptionPane;

class cliente {

	private int id;
	private String nombre;
	private String direccion;
	private double monto;

	public cliente (){
		id = 1330;
		nombre = "Melisa";
		direccion = "Calle halcones";
		monto = 1500;
	}

		public double getmonto (){
			return monto;
			}

			public void setmonto (double p){

					monto = monto + p;	
		
			}

				public void retirar (double r){
					if (monto <=0 || r > monto){
						JOptionPane.showMessageDialog (null, "Saldo Insuficiente"+monto);
					}
						else{
							monto = monto - r;
						} 
					if (monto <1000 ){
						JOptionPane.showMessageDialog(null, "Su monto es: "+monto);
						monto = monto -30.5;
			}		
		}
}

public class practica1{

	public static void main (String [] args ){

		cliente Melisa;
		int z=0;
		Melisa = new cliente();

		do{

	String[] opciones= {"Ver saldo", "Depositar cantidad","Retirar una cantidad", "Salir"};

 					int opcion = JOptionPane.showOptionDialog(
                               null                             //componente
                             ,"¿Que desea realizar?"            // Mensaje
                             , "Menu de opciones"         // Titulo en la barra del cuadro
                             , JOptionPane.DEFAULT_OPTION       // Tipo de opciones
                             , JOptionPane.INFORMATION_MESSAGE  // Tipo de mensaje (icono)
                             , null                             // Icono (ninguno)
                             , opciones                         // Opciones personalizadas
                             , null                             // Opcion por defecto
                           );

if (opcion ==0 ){
				int ax = JOptionPane.showConfirmDialog(null, "Selecciono ver saldo");
        		if(ax == JOptionPane.YES_OPTION)
           		JOptionPane.showMessageDialog(null, Melisa.getmonto());
			}

	if (opcion ==1 ){	
				try{
				double p2;
				String banco = JOptionPane.showInputDialog("Ingrese cantidad a depositar: ");
				p2 = Double.parseDouble(banco);
				if(p2>=0){
					JOptionPane.showMessageDialog(null, "La cantidad ingresada es: "+p2);
					Melisa.setmonto(p2);
					}else{
						JOptionPane.showMessageDialog(null, "No se pude realizar esta accion");
					}
								

					}catch (Exception e){

				}
			}

				if (opcion ==2){
					try{
					double r2;
					String banco = JOptionPane.showInputDialog("Ingrese cantidad a retirar: ");
					r2 =Double.parseDouble(banco);
					if (r2>=0){
						JOptionPane.showMessageDialog(null, "La cantidad retirada es: "+r2);
						Melisa.retirar(r2);
					}else{
						JOptionPane.showMessageDialog(null, "No puede retirar eso :v");
					}
					
						}catch(Exception e){

					}

				}

					if(opcion==3){
						z=3;
					}
				}while (z != 3);
			}
}