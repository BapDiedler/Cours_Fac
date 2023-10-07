import calculette.*;

public abstract class Main {
	
	
	public static void main(String[] argv){
		if(argv.length == 0){
			argv = new String[3];
			argv[0] = "3";
			argv[1] = "1";
			argv[2] = "2";
		}
		Nombre a = new Nombre(Integer.parseInt(argv[0]));
		Nombre b = new Nombre(Integer.parseInt(argv[2]));
		Binaire op;
		
		if(argv[1] == "+"){
			 op = new Somme(a,b);
		}
		else{
			 op = new Soustraction(a,b);
		}
		System.out.println(op.toString()+" = "+op.valeur());
	}
	
}
