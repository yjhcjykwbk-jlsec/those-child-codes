package types;

import java.util.Iterator;
import java.util.Map;
import java.util.Stack;
import java.util.Vector;
//import java.util.*;
public class ClassTable {
	public int reg;
	public ClassTable father;//
	public String fathername;
	public String name;
    public VarTable var;//name type
    public FunctionTable func;
    public boolean made;
    public ClassTable(String classname)
    {
    	made=false;
    	name=classname;
    	var=new VarTable();
    	func=new FunctionTable();
    	father=null;
    	fathername=null;
    }
    public void setFather()
    {
    	int steps=0;
    	ClassTable ancestry=father;
    	Stack<ClassTable> fathers;
    	Vector<Function> allfuncs;
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
    	if(this.made!=true)
    	{
    		fathers=new Stack<ClassTable>();
    		allfuncs=new Vector<Function> ();
    		ancestry=this;
    		ClassTable son;
    		Function myfunc,fatherfunc;
    		while(ancestry.made!=true)
    		{
    			fathers.add(ancestry);
    			ancestry=ancestry.father;
    		}
    		
    		int i;
    		while(fathers.size()>0)
    		{
    			son=fathers.pop();
    			son.func.c.clear();
    			for(i=0;i<ancestry.func.b.size();i++)
    			{
    				fatherfunc=ancestry.func.getFunc(i);
    				myfunc=son.func.get(fatherfunc.name);
    				if(myfunc!=null)
    				{
    					if(!myfunc.isEqual(fatherfunc))
    	    			{
    	    				System.out.println("WrongFunctionDefination: in class "+son.name+" function "+myfunc.name+" has the same name with "+fatherfunc.name+" in its father "+ancestry.name);
    	    			}
    					allfuncs.add(myfunc);
    					son.func.c.put(myfunc.name,allfuncs.size()-1);
    				}
    				else 
    				{
    					
    					allfuncs.add(fatherfunc);
    					son.func.a.put(fatherfunc.name,fatherfunc);
    					son.func.c.put(fatherfunc.name,allfuncs.size()-1);
    				}
    			}
    			for(i=0;i<son.func.b.size();i++)
    			{
    				myfunc=son.func.getFunc(i);
    				if(ancestry.func.get(myfunc.name)==null)
    				{
    					allfuncs.add(myfunc);
    					son.func.c.put(myfunc.name,allfuncs.size()-1);
    				}
    			}
    			son.func.b=allfuncs;
    			allfuncs=new Vector<Function> ();
    			ancestry=son;/*circle*/
    		}
    	}
    }
    
    public void addVar(String name,TypeItem type) throws TypeRepeatException
    {
    	var.addVar(name,type);
    }
    public void addFunc(Function type) throws TypeRepeatException
    {
    	func.addFunc(type);
    }
    //the var include extended
    public TypeItem varLookUp(String name)
    {
    	ClassTable _table=this.varScopeLookUp(name);
    	if(_table==null) return null;
    	else return (_table.var.varLookUp(name));
    }
    public ClassTable varScopeLookUp(String name)
    {
    	ClassTable _table=this;
    	while(true)
    	{
    	if(_table.var.varLookUp(name)!=null)
    		return _table;
    	_table=_table.father;
    	if(_table==this||_table==null)
    		return null;
    	}
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
    public boolean isSon(String name)
    {
    	/*if this is class "name" or its son,return true*/
    	ClassTable curr=this;
    	while(curr!=null)
    	{
    		if(curr.name.equals(name)) return true;
    		curr=curr.father;
    		if(curr==this) break;
    	}
    	return false;
    }
    /*return var-num store in memory*/
    public int getNum(String name)
    {
    	return var.getNum(name)+1;
    }
}
