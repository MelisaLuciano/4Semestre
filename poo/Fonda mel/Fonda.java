public class Fonda{

	public static void main(String []A){

		String opt;
		int valor1;

		entrada []e1 = {new entrada("Arroz"), new entrada("Sopa de codito"), new entrada("Crema de champinones")};
		guisado []g1 = {new guisado("Pechuga empanizada"), new guisado("Chilaquiles"), new guisado("pozole"), new guisado("Jamón con huevo")};
		postre []p1 = {new postre ("Flan"), new postre ("Fresas con crema"), new postre("Pastel de chocolate")};

		opt = GUI.valor("Elige tu opcion del menu\n1.-" +e1[0].getentrada() + "\n2.-" +e1[1].getentrada() + "\n3.-" +e1[2].getentrada());
		valor1 = new Integer (opt);
		GUI.mensaje(opt);

	}

}


		


