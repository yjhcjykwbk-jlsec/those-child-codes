package types;

import java.util.Iterator;
import java.util.Map;

//import java.util.*;
public class ClassTable {
	public ClassTable father;//�̳й�ϵ
	public String fathername;
	public String name;
    VarTable var;//name type
    FunctionTable func;
    public ClassTable(String classname)
    {
    	name=classname;
    	var=new VarTable();
    	func=new FunctionTable();
    	father=null;
    	fathername=null;
    }
    public void setFather()
    {
    	//��黷
    	int steps=0;
    	ClassTable ancestry=father;
    	while(ancestry!=null)
    	{
    		steps++;
    		if(ancestry.name.equals(name))
    		{
    			System.out.println("ExtendingError: "+name+" extends itself after "+steps+" time(s) of up-extending");
    			break;
    		}
    		ancestry=ancestry.father;
    	}
    	//��麯����Ա
    	Iterator <Map.Entry<String, Function>> at=func.a.entrySet().iterator();
    	ClassTable itsfather=this.father;
    	while(at.hasNext())
    	{
    		Map.Entry<String, Function> entry = at.next();
    		String funcname=entry.getKey();
    		Function function=entry.getValue();
    		Function function1;
    		if((function1=itsfather.funcLookUp(funcname))!=null)
    		{
    			if(!function.isEqual(function))
    			{
    				System.out.println("WrongFunctionDefination: in class "+name+" function "+funcname+" has the same name with "+funcname+" in its father "+itsfather.name);
    			}
    		}
    	}
    }
    public void addVar(String name,TypeItem type) throws TypeRepeatException
    {
    	var.addVar(name,type);
    }
    public void addFunc(String name,Function type) throws TypeRepeatException
    {
    	func.addFunc(name,type);
    }
    //the var exclude extended
    public TypeItem varLookUp(String name)
    {
    	if(var.varLookUp(name)!=null) return var.varLookUp(name);
    	else return null;
    }
    //the function include extended
    public Function funcLookUp(String name)
    {
    	if(func.get(name)!=null){ return func.get(name);}
    	else if(father!=null)
    	{
    		return(father.funcLookUp(name));
    	}
    	else return null;
    }
    //the function exclude extended
    public Function getFunc(String name)
    {
    	return func.get(name);
    }
    public VarTable getVartable()
    {
    	return var;
    }
}