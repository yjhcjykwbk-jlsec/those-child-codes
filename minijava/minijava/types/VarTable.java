package types;
import java.util.*;
public class VarTable {
     HashMap <String,TypeItem> a;
     public VarTable()
     {
    	 a=new HashMap <String,TypeItem>();
     }
     public void addVar(String name,TypeItem type) throws TypeRepeatException
     {
    	 if(a.put(name,type)!=null) 
    	 throw new TypeRepeatException(name);
     }
     public TypeItem varLookUp(String name)
     {
    	 return a.get(name);
     }
}
