import javax.swing.JOptionPane;
public class ventanas{
	public static void mensaje(String titulo){
		JOptionPane.showMessageDialog(null, titulo, "Mensaje", JOptionPane.INFORMATION_MESSAGE);	
	}
	public static String valor(String titulo){
		String opt;
		do{
			opt = JOptionPane.showInputDialog(titulo);
		}while(opt == null);
		return opt;
	}
}