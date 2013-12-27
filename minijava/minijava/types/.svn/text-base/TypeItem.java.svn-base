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
	public boolean isClass()
	{
		return (TypeIndex>2);
	}
	public boolean equals(TypeItem b)
	{//this!=null
		if(b==null) return false;
		if(this.TypeIndex==b.TypeIndex)
		{
			if(b.TypeIndex>2)
				return(this.TypeName.equals(b.TypeName));
			else return true;
		}
		return false;
	}
}
