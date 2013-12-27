package types;
import java.util.HashMap;
import java.util.Vector;


public class FunctionTable {
  public HashMap<String,Function> a;
  public Vector<Function>b;
  public HashMap<String,Integer> c;
  public FunctionTable()
  {
	  a=new HashMap<String,Function>();
	  b=new Vector<Function>();
	  c=new HashMap<String,Integer>();
  }
  public Function get(String name)
  {
	  return (a.get(name));
  }
  public void addFunc(Function func)throws TypeRepeatException 
  {
	  String name=func.name;
	  if(a.put(name, func)!=null)throw (new TypeRepeatException(name));
	  else {b.add(func);c.put(name, b.size()-1);}
  }
  public int getSize()
  {
	  return a.size();
  }
  public Function getFunc(int index)
  {
	  return b.elementAt(index);
  }
  public int getNum(String name)
  {
	  return c.get(name);
  }
}
