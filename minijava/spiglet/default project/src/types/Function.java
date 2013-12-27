package types;
import java.util.Vector;

import visitor.VarNotFoundException;
public class Function {
	public String name;
	public TypeItem returnType;//0 1 2 
	public ClassTable scope;
	public int index;//
	public Vector<TypeItem> para;//
	public void addPara(TypeItem type) 
	{
		para.add(type);
	}
	public VarTable body;//
	public Function(String funcname,ClassTable classid)
	{
		name=funcname;
		scope=classid;
		para=new Vector<TypeItem>();
		body=new VarTable();
	}
	public void setReturnType(TypeItem t) 
	{
		returnType=t;
	}
	public TypeItem varLookUp(String name)//varLookUp 
    {
    	if(body.varLookUp(name)!=null) return body.varLookUp(name);
    	else return scope.varLookUp(name);
    }
	public boolean isEqual(Function a)
	{
		if(!returnType.equalWith(a.returnType)) 
		{
			System.out.print(returnType.TypeIndex+":"+a.returnType.TypeIndex); 
			return false;
		}
		int size=para.size();
		if(size!=a.para.size()) return false;
		for(int i=0;i<size-1;i++)
		{
			if(!para.elementAt(i).equalWith(a.para.elementAt(i))) return false;
		}
		return true;
	}
	public boolean declaredInFunc(String name)//judge whether the value is declared in the function
	{
		if(body.varLookUp(name)!=null) 
		{
				return true;
		}
		else return false;
	}
	public int getNum(String name)
	{
		//declared in function
		if(body.varLookUp(name)!=null)
		{
			int num=body.getNum(name);
			if(num>=para.size()) return(num-para.size()+20);
			else return num+1;
		}
		//declared in class,the number will be added by one
		else return (scope.var.getNum(name)+1);
	}
}
