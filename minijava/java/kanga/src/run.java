import syntaxtree.Goal;
import visitor.*;
import java.io.*;
public class run {
	static public void main(String []argu) throws Exception
	{
	
	
		FileInputStream file=new FileInputStream(".//src/input");
		new SpigletParser(file);
		Goal goal=SpigletParser.Goal();
		//System.out.println("parsed");
		GJDepthFirst visitor=new GJDepthFirst ();
		visitor.visit(goal, new st());
	
	
	}
}
