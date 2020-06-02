import javax.swing.JOptionPane;

public class GUI{

	public static void mensaje(String s){

		JOptionPane.showMessageDialog(null, s, "Fonda :v ", JOptionPane.INFORMATION_MESSAGE);


	}
	public static String valor(String s){
		String opt;
		do{
			opt = JOptionPane.showInputDialog(s);

		}while (opt== null || opt.length () <= 0);
		return opt;
	}
	public static String 
}
	