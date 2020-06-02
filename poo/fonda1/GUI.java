import JavaSwingOptionPane;

	public class GUI{

		public static int mostrar{
			JOptionPane.showInputDialog(null, "Fonda");
			String[] opciones = {"Entrada", "Guisados", "Postre" };
        	int opcion = JOptionPane.showOptionDialog(null, "¿Que desea?", "Fondita", JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, opciones, null);
        	if (option == 0){
        		String[] opciones= {null, "Entradas", "Consome","Sopa De Codito","Arroz"};
        		int option =JOptionPane.showOptionDialog(null, "Elija...", JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, opciones, null);
        	}
        	if (option == 1){
        		String[] opciones= {null, "Guisados", "Niños Envueltos","Albondigas","Mole","Tinga"};
        		int option =JOptionPane.showOptionDialog(null, "Elija...", JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, opciones, null);
      		}  	
        	if (option == 2){
        	String[] opciones= {null, "Postres", "Flan  Napolitano","Fresas con Crema","Rebanada De Pastel"};
        	int option =JOptionPane.showOptionDialog(null, "Elija un postre...", JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, opciones, null);
      		}
            

		}
	}