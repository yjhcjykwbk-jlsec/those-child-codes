package types;
import java.util.Vector;

import visitor.VarNotFoundException;
public class Function {
	public String name;
	public TypeItem returnType;//0 1 2 
	public ClassTable scope;
	public int index;//
	public Vector<TypeItem> para;//虚参数表
	public void addPara(TypeItem type) 
	{
		para.add(type);
	}
	public VarTable body;//BODY新申明的元素不能和para元素重复。可以和class中元素重复
	public Function(String funcname,ClassTable classid)
	{
		name=funcname;
		scope=classid;
		para=new Vector<TypeItem>();
		body=new VarTable();
	}
	/*class ele{
		String key;
		TypeItem value;
		public ele(String a,TypeItem b){key=a;value=b;}
	}
	public Stack<ele> Scope;*/////////////////////如果函数里嵌套函数，这里还需要一个记载内部函数的数据
	//涉及到作用域
	//类型检查的重点
	
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
		if(!returnType.equals(a)) return false;
		int size=para.size();
		if(size!=a.para.size()) return false;
		for(int i=0;i<size-1;i++)
		{
			if(!para.elementAt(i).equals(a.para.elementAt(i))) return false;
		}
		return true;
	}
}
