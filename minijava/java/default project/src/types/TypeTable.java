package types;
import java.util.*;
public class TypeTable {
         public HashMap<String,ClassTable>  a;
         public TypeTable(){a=new HashMap<String,ClassTable> ();}
         public void addClass(String e,ClassTable des) throws TypeRepeatException
         {
        	 if(a.put(e,des)!=null) 
        	 throw new TypeRepeatException(e);
         }
         public boolean existClass(String name)
         {
        	 return (a.get(name)!=null);
         }
         public ClassTable getClass(String name)
         {
        	 return a.get(name);
         }
}
