
  import java.io.*;
  
  
  class trans_terrestre {
  	
  	     protected String Nombre=null;
  	     protected String Placas=null;
  	     
  	     
  	     trans_terrestre ( String N , String P ){
  	     	
  	     	     Nombre = new String (N);
  	     	     Placas = new String (P);
  	     	
  	     	}
  	       	     
  	     public void mensaje (){
  	     	
  	              System.out.print("Este es un transporte publico");      	
  	     	}
  	  	
   }
  
  class micro extends trans_terrestre {
  	
  	
  	     private int ruta; 
  	     
  	     public micro ( String N , String P , int R ){
  	     	
  	     	   super (N,P);
  	     	   ruta = R;
  	     	
  	     	}
            
  	     public void mensaje (){
  	     	
  	     	  super.mensaje();
  	     	
  	     	  System.out.println(" subase mientras pueda soy un micro");      
  	     	
  	     	}
  	     	
  	     public void promo (){
  	     	
  	     	
  	     	  System.out.println(" subale viene vacio , subale a la raza "); 
  	     	
  	     	
  	     	}	
            	
  	
  	}
  	
  class taxi extends trans_terrestre {
  	
         private String base;
         private int numero_puertas;   	
  	
  	
  	     public taxi (String N , String P , String  Base , int Puertas) {
  	     	
  	     	    super (N,P);
  	     	    base = new String (Base);
  	     	    numero_puertas = Puertas;
  	     	} 
  	
  	     public void mensaje (){
  	     	  
  	     	  super.mensaje();
  	     	  System.out.println(" Este es un taxi ecologico donde lo llevo");      
  	     	
  	     	}  
  	
  	}	
  	
  class instancef {
  	 
  	  public static void main ( String panchita [] ){ 
  	  
  	       trans_terrestre micro_o_taxi,m_t;
  	      
  	       micro m = new micro ( "Siempre vivire" , " Bl12353" , 3 );
  	       taxi  t = new taxi  ( "Paty" , " B398354 " , "Puente Tenayuca" , 2 );
  	       
  	       //micro_o_taxi = m;
  	      
               //micro_o_taxi.mensaje();  
              
              // m_t=t; 
  	        	              
  	     seleccionar(m);
  	      	
  	  }
  	  
     public static void seleccionar ( trans_terrestre T ){
  	  	
  	  	    T.mensaje();
  	  	    
  	  	    if ( T instanceof micro ){
  	  	    	
  	  	    	  ((micro)(T)).promo();
  	  	    	   	  	    	 
  	  	    	 }  	   	  	    	  
  	  	
  	  	}
  	
  	} 	
  	
  	