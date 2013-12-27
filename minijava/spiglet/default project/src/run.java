import java.io.*;
import visitor.*;
import java.util.*;
public class run {
     static public void main(String args[]){
    	 syntaxtree.Goal goal;
    	 types.TypeTable table;
    	 CreateTableVisit tablevisitor;
    	 TypeCheckVisit   checkvisitor;
    	 PigletVisit      pigletvisitor;
    	 //MiniJavaParser ap;
    	 
    	 Object s=new Object();
    	 try
    	 {
    		FileReader file=new FileReader("input");
        new MiniJavaParser(file);
    	 
    	 goal=MiniJavaParser.Goal();
    	 
    	 table=new types.TypeTable();
    	 tablevisitor=new CreateTableVisit(table);
    	 tablevisitor.visit(goal);
    	 checkvisitor=new TypeCheckVisit(table);
    	 Object a=new Object();
    	 checkvisitor.visit(goal, a);
   
    	 pigletvisitor=new PigletVisit(table);
    	 pigletvisitor.visit(goal,s);
    	 }
    	 catch(ParseException e)
    	 {
    		 System.out.println(e.getMessage());
    	 }
    	 catch(FileNotFoundException eee){System.out.println("not found");}
    	 //catch(Exception eee){System.out.println("error");}
    	
    	 }
    	 
     //}
}