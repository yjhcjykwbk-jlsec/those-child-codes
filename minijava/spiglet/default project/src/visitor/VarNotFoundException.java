package visitor;

public class VarNotFoundException extends Exception{
	
	public VarNotFoundException(String v)
	{
		System.out.print("NOTFOUND:"+"\""+v+"\""+" not declared");
	}
}
