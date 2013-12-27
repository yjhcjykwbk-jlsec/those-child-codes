package types;
import java.util.*;
public class VarTable {
	 //public int reg;
     HashMap <String,TypeItem> a;
     Vector<String> b;
     HashMap <String,Integer> c;
     public VarTable()
     {
    	 c=new HashMap <String,Integer>();
    	 a=new HashMap <String,TypeItem>();
    	 b=new Vector<String>();
     }
     public void addVar(String name,TypeItem type) throws TypeRepeatException
     {
    	 if(a.put(name,type)!=null) 
    	 throw new TypeRepeatException(name);
    	 else{ b.add(name);c.put(name, b.size()-1);}
     }
     public TypeItem varLookUp(String name)
     {
    	 return a.get(name);
     }
     public int getSize()
     {
    	 return b.size();
     }
     public String getVar(int index)
     {
    	 return b.elementAt(index);
     }
     public int getNum(String name)
     {
    	 return c.get(name);
     }
}
