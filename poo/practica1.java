import javax.swing.JOptionPane;

public class practica1{


	public static void main (String [] args ){

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
            JOptionPane.showMessageDialog(null, "Tu saldo minimo es: 1500");
        else if(ax == JOptionPane.NO_OPTION)
            JOptionPane.showMessageDialog(null, "Salir");
		
				}

	if (opcion ==1 ){
				String banco = JOptionPane.showInputDialog("Ingrese cantidad a depositar: ");
				JOptionPane.showMessageDialog(null, "La cantidad ingresada es: "+banco);
		}

			if (opcion ==2){
					String banco = JOptionPane.showInputDialog("Ingrese cantidad a retirar: ");
					JOptionPane.showMessageDialog(null, "La cantidad retirada es: "+banco);


			}


	
	}
}

