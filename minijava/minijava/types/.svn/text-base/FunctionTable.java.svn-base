package types;
import java.util.HashMap;


public class FunctionTable {
  public HashMap<String,Function> a;
  public FunctionTable()
  {
	  a=new HashMap<String,Function>();
  }
  public Function get(String name)
  {
	  return (a.get(name));
  }
  public void addFunc(String name,Function func)throws TypeRepeatException 
  {
	  if(a.put(name, func)!=null)throw (new TypeRepeatException(name));
  }

}
