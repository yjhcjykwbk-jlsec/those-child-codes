package types;
public class TypeItem {
	public int TypeIndex;//0 1 2 (in[] int boolean) 3 class 4 function
	public String TypeName;//TypeIndex=3,class name=typename
	public TypeItem(int type)
	{
		TypeIndex=type;
		if(type<3) TypeName="";
	}
	public TypeItem(String type)
	{
		TypeIndex=3;
		TypeName=type;
	}
	public TypeItem(syntaxtree.Type x)
	{
		int s=x.f0.which;
		TypeIndex=s;
		if(s<3) {TypeName="";}
		else {TypeName=((syntaxtree.Identifier)(x.f0.choice)).f0.toString();}
	}
	
	/*a.fitFor(b)only if you can write b=a*/
	public boolean fitFor(TypeTable types,TypeItem b)
	{	//this!=null
		if(b==null) return false;
		if(this.TypeIndex==b.TypeIndex)
		{
			if(b.TypeIndex<3) return true;
			/*if this is a son of b ,return true*/
			if(this.TypeName.equals(b.TypeName)) return true;
			ClassTable _class=types.getClass(this.TypeName);
			if(_class==null) return false;
			return(_class.isSon(b.TypeName));
		}
		return false;
	}
	public boolean equalWith(TypeItem b)
	{
		if(b!=null&&this.TypeIndex==b.TypeIndex)
		{
			if(this.TypeIndex==3)
			{
				return this.TypeName.equals(b.TypeName);
			}
			return true;
		}
		return false;
	}
}

