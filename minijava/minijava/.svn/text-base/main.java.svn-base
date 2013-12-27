import java.io.*;
import java.util.*;
public class main {
     static public void main(String args[]){

    	 Integer i=0;
    	 String FileName="";
    	 FileReader in;
    	 syntaxtree.Goal goal;
    	 types.TypeTable table;
    	 visitor.CreateTableVisit tablevisitor;
    	 visitor.TypeCheckVisit   checkvisitor;
    	 try
    	 {
    		 temp.MiniJavaParser ap=new temp.MiniJavaParser(System.in);
    	 }
    	 catch(Exception e){}
    	 
    	 
    	 for(i=0;i<100;i++){
    		 System.out.println("case "+i);
    	 try
    	 {
    	 if(i<10) FileName="test/test0"+i+".java";
    	 else FileName="test/test"+i+".java";
    	 in=new FileReader(FileName);	
    	 //词法语法
    	 temp.MiniJavaParser.ReInit(in);
    	 goal=temp.MiniJavaParser.Goal();
    	 //建表
    	 table=new types.TypeTable();
    	 tablevisitor=new visitor.CreateTableVisit(table);
    	 tablevisitor.visit(goal);
    	 //符号检查
    	 checkvisitor=new visitor.TypeCheckVisit(table);
    	 Object a=new Object();
    	 checkvisitor.visit(goal, a);
    	 }
    	 catch(FileNotFoundException ee)
    	 {
    		 System.out.println("not found the file");
    	 }
    	 catch(temp.ParseException e)
    	 {
    		 System.out.println(e.getMessage());
    	 }
    	 catch(Exception eee){}
    	 System.out.println();
    	 }
     }
}
