public class cocina {

	public static String[] entradas= {"Consome","Sopa De Codito","Arroz"};
	public static String[] guisados= {"Huevos revueltos","Albondigas","Mole","Tinga"};
	public static String[] postres = {"Flan  Napolitano","Fresas con Crema","Rebanada De Pastel"};

	public static void preparar (Entrada E)
	{
		interfaz.MostrarInformacion("Aqui esta tu entrada: \n");
	}
	public static void preparar (Guisado G){
		interfaz.MostrarInformacion("Aqui esta tu guisado: \n");
	}
	public static void preparar (Postre P){
		interfaz.MostrarInformacion("Aqui esta tu postre: \n");
	}

}