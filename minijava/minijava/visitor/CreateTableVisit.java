package visitor;
import java.util.Iterator;
import java.util.Map;
import java.util.Iterator;
import java.util.Map;

import syntaxtree.AllocationExpression;
import syntaxtree.AndExpression;
import syntaxtree.ArrayAllocationExpression;
import syntaxtree.ArrayAssignmentStatement;
import syntaxtree.ArrayLength;
import syntaxtree.ArrayLookup;
import syntaxtree.ArrayType;
import syntaxtree.AssignmentStatement;
import syntaxtree.Block;
import syntaxtree.BooleanType;
import syntaxtree.BracketExpression;
import syntaxtree.ClassDeclaration;
import syntaxtree.ClassExtendsDeclaration;
import syntaxtree.CompareExpression;
import syntaxtree.Expression;
import syntaxtree.ExpressionList;
import syntaxtree.ExpressionRest;
import syntaxtree.FalseLiteral;
import syntaxtree.FormalParameter;
import syntaxtree.FormalParameterList;
import syntaxtree.FormalParameterRest;
import syntaxtree.Goal;
import syntaxtree.Identifier;
import syntaxtree.IfStatement;
import syntaxtree.IntegerLiteral;
import syntaxtree.IntegerType;
import syntaxtree.MainClass;
import syntaxtree.MessageSend;
import syntaxtree.MethodDeclaration;
import syntaxtree.MinusExpression;
import syntaxtree.NotExpression;
import syntaxtree.PlusExpression;
import syntaxtree.PrimaryExpression;
import syntaxtree.PrintStatement;
import syntaxtree.Statement;
import syntaxtree.ThisExpression;
import syntaxtree.TimesExpression;
import syntaxtree.TrueLiteral;
import syntaxtree.Type;
import syntaxtree.TypeDeclaration;
import syntaxtree.VarDeclaration;
import syntaxtree.WhileStatement;
import types.ClassTable;
import types.TypeRepeatException;
import types.Function;
public class CreateTableVisit extends DepthFirstVisitor{

	types.TypeTable types;
	types.ClassTable table;
	types.Function func;//处理函数
	types.TypeItem temp;
	types.VarTable vars; 
    public CreateTableVisit(types.TypeTable t)
    {
    	types=t;
    }
    public void Reint(types.TypeTable t)
    {
    	types=t;
    }
    public boolean classLookUp(String name)
    {
    	return (types.existClass(name));
    }
    //函数func和类table中寻找变量name的存在情况
    
    /**
     * f0 -> MainClass()
     * f1 -> ( TypeDeclaration() )*
     * f2 -> <EOF>
     */
    public void visit(Goal n) {
       n.f0.accept(this);
       n.f1.accept(this);
       //设置类表之间的继承关系 先做部分检查
       Iterator <Map.Entry<String, ClassTable>> at=types.a.entrySet().iterator();
       ClassTable father,son;
   	   while(at.hasNext())
   	{
   		Map.Entry<String,ClassTable> entry = at.next();
   		son=entry.getValue();
   		if(son.fathername!=null)
   		{
   			father=types.getClass(son.fathername);
   			if(father==null)
   			{
   				System.out.println("ExtendError: "+son.name+" extends an undefined class "+son.fathername);
   			}
   			else if(father.name.equals(son.name))
   			{
   				System.out.println("ExtendError: "+son.name+" extends itself ");
   			}
   			else {son.father=father;}
   		}
   	}
       n.f2.accept(this);
    }

	   /**
	    * f0 -> "class"
	    * f1 -> Identifier()
	    * f2 -> "{"
	    * f3 -> "public"
	    * f4 -> "static"
	    * f5 -> "void"
	    * f6 -> "main"
	    * f7 -> "("
	    * f8 -> "String"
	    * f9 -> "["
	    * f10 -> "]"
	    * f11 -> Identifier()
	    * f12 -> ")"
	    * f13 -> "{"
	    * f14 -> PrintStatement()
	    * f15 -> "}"
	    * f16 -> "}"
	    */
	   public void visit(MainClass n) {////
		  
	      table=new ClassTable(n.f1.f0.tokenImage);
	      try
	      {
	        types.addClass(n.f1.f0.tokenImage,table);
	      }
	      catch(TypeRepeatException e){}
	     
	      func=new Function(n.f6.tokenImage,table);
	      try{
	    	  table.addFunc(func.name, func);
	      }
	      catch(TypeRepeatException e){}
	
	      vars=func.body;
	      try
	      {
	    	  vars.addVar(n.f11.f0.tokenImage, null);
	      }
	      catch(TypeRepeatException e)
	      {}

	      n.f14.accept(this);
	  
	   }

	   /**
	    * f0 -> ClassDeclaration()
	    *       | ClassExtendsDeclaration()
	    */
	   public void visit(TypeDeclaration n) {
	      n.f0.accept(this);
	   }

	   /**
	    * f0 -> "class"
	    * f1 -> Identifier()
	    * f2 -> "{"
	    * f3 -> ( VarDeclaration() )*
	    * f4 -> ( MethodDeclaration() )*
	    * f5 -> "}"
	    */
	   public void visit(ClassDeclaration n) {///
	      n.f0.accept(this);
	      n.f1.accept(this);
	     
	      try{
	      table=new types.ClassTable(n.f1.f0.toString());
	      types.addClass(n.f1.f0.toString(),table);
	      }
	      catch(types.TypeRepeatException e)
	      {	    
	    	  System.out.println("in line"+n.f1.f0.beginLine+" as a class");
	      }
	  
	      n.f2.accept(this);
	      vars=table.getVartable();//vars专门处理vardeclaration
	      n.f3.accept(this);
	      //funcs=table.func;//funcs同上 
	      n.f4.accept(this);
	      n.f5.accept(this);
	   }

	   /**
	    * f0 -> "class"
	    * f1 -> Identifier()
	    * f2 -> "extends"
	    * f3 -> Identifier()
	    * f4 -> "{"
	    * f5 -> ( VarDeclaration() )*
	    * f6 -> ( MethodDeclaration() )*
	    * f7 -> "}"
	    */
	   public void visit(ClassExtendsDeclaration n) {////
	      n.f1.accept(this);
	      //类重复定义
	      try{
		      table=new types.ClassTable(n.f1.f0.toString());
		      types.addClass(n.f1.f0.toString(),table);
		      }
		      catch(types.TypeRepeatException e)
		      {	    
		    	  System.out.println("in line "+n.f1.f0.beginLine+" as a class");
		      }
	 
	      table.fathername=n.f3.f0.tokenImage;
          //extends在第二步处理
	      vars=table.getVartable();//vars专门处理vardeclaration
	      n.f5.accept(this);
	      n.f6.accept(this);
	   }

	   /**
	    * f0 -> Type()
	    * f1 -> Identifier()
	    * f2 -> ";"
	    *///在class里声明成员变量 注意如果是在函数里声明。有没有这种可能？
	   public void visit(VarDeclaration n) {
	      n.f0.accept(this);
	      n.f1.accept(this);//////////////////////////////
	      n.f2.accept(this);
	  
	      String name=n.f1.f0.toString();
	      temp=new types.TypeItem(n.f0);
	      
	      //防止重复成员变量声明
	      try
	    	{
		      	vars.addVar(name,temp);
		   	}
	      catch(types.TypeRepeatException e)
		 	{	    
		  		System.out.println("in line "+n.f2.beginLine+" in class "+table.name+" as a variable");
		 	}
	   }

	   /**
	    * f0 -> "public"
	    * f1 -> Type()//返回值不会是class类型
	    * f2 -> Identifier()
	    * f3 -> "("
	    * f4 -> ( FormalParameterList() )?
	    * f5 -> ")"
	    * f6 -> "{"
	    * f7 -> ( VarDeclaration() )*
	    * f8 -> ( Statement() )*
	    * f9 -> "return"
	    * f10 -> Expression()
	    * f11 -> ";"
	    * f12 -> "}"
	    *//////////////////////////////to be added
	   //最好对于重复命名的类、函数能够单独进行hash表存放 这样的话需要修改hash
	   //而简单类型的重复在报错的基础上直接用覆盖原则
	   public void visit(MethodDeclaration n) {
	      n.f0.accept(this);
	      n.f1.accept(this);
	      temp=new types.TypeItem(n.f1);
	      //函数返回值不能为class类型 注意语法分析是否做到了检查？否则类型检查要做！
	      n.f2.accept(this);
	      func=new types.Function(n.f2.f0.toString(),table);
	      func.setReturnType(temp);
	      try
	      {
	    	  table.addFunc(n.f2.f0.toString(),func);
	      }
	      catch(types.TypeRepeatException e)
	      {
	    	  System.out.println(" in line "+n.f2.f0.beginLine+"in class"+table.name);
	      }
	      n.f3.accept(this);
	      //接受虚参
	      vars=func.body;
	      n.f4.accept(this); 
	      n.f7.accept(this);
	      n.f8.accept(this);
	    
	      //检查是否有未定义的变量 放到后面
	      //n.f10.accept(this);
	   }

	   /**
	    * f0 -> FormalParameter()
	    * f1 -> ( FormalParameterRest() )*
	    */
	   public void visit(FormalParameterList n) {
	      n.f0.accept(this);
	      n.f1.accept(this);
	   }

	   /**
	    * f0 -> Type()
	    * f1 -> Identifier()
	    */
	   public void visit(FormalParameter n) {
	      n.f0.accept(this);
	      n.f1.accept(this);
	      try{
	      vars.addVar(n.f1.f0.toString(),new types.TypeItem(n.f0));
	      func.addPara(new types.TypeItem(n.f0));
	      }
	      catch(types.TypeRepeatException e)
	      {
	    	  System.out.println(" in line "+n.f1.f0.beginLine+" in function "+func.name+"\'s paralist");
	      }
	   }

	   /**
	    * f0 -> ","
	    * f1 -> FormalParameter()
	    */
	   public void visit(FormalParameterRest n) {
	      n.f0.accept(this);
	      n.f1.accept(this);
	   }

	   /**
	    * f0 -> ArrayType()
	    *       | BooleanType()
	    *       | IntegerType()
	    *       | Identifier()
	    */
	   public void visit(Type n) {
	      n.f0.accept(this);
	   }
	 

	   /**
	    * f0 -> "int"
	    * f1 -> "["
	    * f2 -> "]"
	    */
	   public void visit(ArrayType n) {
	   }

	   /**
	    * f0 -> "boolean"
	    */
	   public void visit(BooleanType n) {
	   }

	   /**
	    * f0 -> "int"
	    */
	   public void visit(IntegerType n) {
	   }

	   /**
	    * f0 -> Block()
	    *       | AssignmentStatement()
	    *       | ArrayAssignmentStatement()
	    *       | IfStatement()
	    *       | WhileStatement()
	    *       | PrintStatement()
	    */
	   public void visit(Statement n) {
	      n.f0.accept(this);
	   }

	   /**
	    * f0 -> "{"
	    * f1 -> ( Statement() )*
	    * f2 -> "}"
	    */
	   //注意作用域。。。。block象征着作用域的变化。不过貌似不会有变量继续申明
	   public void visit(Block n) {
	      n.f1.accept(this);
	   }

	   /**
	    * f0 -> Identifier()
	    * f1 -> "="
	    * f2 -> Expression()
	    * f3 -> ";"
	    */
	   public void visit(AssignmentStatement n) {
	      n.f0.accept(this);//....
	      if(func.varLookUp(n.f0.f0.toString())==null)
	      System.out.println("Undefined: "+n.f0.f0.tokenImage+" in line "+n.f0.f0.beginLine+" column "+n.f0.f0.beginColumn);
	      n.f1.accept(this);
	      n.f2.accept(this);
	      n.f3.accept(this);
	   }

	   /**
	    * f0 -> Identifier()
	    * f1 -> "["
	    * f2 -> Expression()
	    * f3 -> "]"
	    * f4 -> "="
	    * f5 -> Expression()
	    * f6 -> ";"
	    */
	   public void visit(ArrayAssignmentStatement n) {
	      n.f0.accept(this);
	      if(func.varLookUp(n.f0.f0.toString())==null)
	      System.out.println("Undefined: "+n.f0.f0.tokenImage+" in line "+n.f0.f0.beginLine+" column "+n.f0.f0.beginColumn);
	      n.f2.accept(this);
	      n.f5.accept(this);//f5的类型不能不是int 后面检查
	   }

	   /**
	    * f0 -> "if"
	    * f1 -> "("
	    * f2 -> Expression()
	    * f3 -> ")"
	    * f4 -> Statement()
	    * f5 -> "else"
	    * f6 -> Statement()
	    */
	   public void visit(IfStatement n) {
	      n.f2.accept(this);
	      n.f4.accept(this);
	      n.f6.accept(this);
	   }

	   /**
	    * f0 -> "while"
	    * f1 -> "("
	    * f2 -> Expression()
	    * f3 -> ")"
	    * f4 -> Statement()
	    */
	   public void visit(WhileStatement n) {
	      n.f2.accept(this);
	      n.f4.accept(this);
	   }

	   /**
	    * f0 -> "System.out.println"
	    * f1 -> "("
	    * f2 -> Expression()
	    * f3 -> ")"
	    * f4 -> ";"
	    */
	   public void visit(PrintStatement n) {
	      n.f2.accept(this);
	   }

	   /**
	    * f0 -> AndExpression()
	    *       | CompareExpression()
	    *       | PlusExpression()
	    *       | MinusExpression()
	    *       | TimesExpression()
	    *       | ArrayLookup()
	    *       | ArrayLength()
	    *       | MessageSend()//函数调用
	    *       | PrimaryExpression()
	    */
	   public void visit(Expression n) {
	      n.f0.accept(this);
	   }

	   /**
	    * f0 -> PrimaryExpression()
	    * f1 -> "&&"
	    * f2 -> PrimaryExpression()
	    */
	   public void visit(AndExpression n) {
	      n.f0.accept(this);
	      n.f2.accept(this);
	   }

	   /**
	    * f0 -> PrimaryExpression()
	    * f1 -> "<"
	    * f2 -> PrimaryExpression()
	    */
	   public void visit(CompareExpression n) {
	      n.f0.accept(this);
	      n.f2.accept(this);
	   }

	   /**
	    * f0 -> PrimaryExpression()
	    * f1 -> "+"
	    * f2 -> PrimaryExpression()
	    */
	   public void visit(PlusExpression n) {
	      n.f0.accept(this);
	      n.f2.accept(this);
	   }

	   /**
	    * f0 -> PrimaryExpression()
	    * f1 -> "-"
	    * f2 -> PrimaryExpression()
	    */
	   public void visit(MinusExpression n) {
	      n.f0.accept(this);
	      n.f2.accept(this);
	   }

	   /**
	    * f0 -> PrimaryExpression()
	    * f1 -> "*"
	    * f2 -> PrimaryExpression()
	    */
	   public void visit(TimesExpression n) {
	      n.f0.accept(this);
	      n.f2.accept(this);
	   }

	   /**
	    * f0 -> PrimaryExpression()
	    * f1 -> "["
	    * f2 -> PrimaryExpression()
	    * f3 -> "]"
	    */
	   public void visit(ArrayLookup n) {
	      n.f0.accept(this);
	      n.f2.accept(this);
	   }

	   /**
	    * f0 -> PrimaryExpression()
	    * f1 -> "."
	    * f2 -> "length"
	    */
	   public void visit(ArrayLength n) {
	      n.f0.accept(this);
	   }

	   /**
	    * f0 -> PrimaryExpression()
	    * f1 -> "."
	    * f2 -> Identifier()
	    * f3 -> "("
	    * f4 -> ( ExpressionList() )?
	    * f5 -> ")"
	    *///函数调用
	   public void visit(MessageSend n) {
	      n.f0.accept(this);
	   }

	   /**
	    * f0 -> Expression()
	    * f1 -> ( ExpressionRest() )*
	    */
	   public void visit(ExpressionList n) {
	   }

	   /**
	    * f0 -> ","
	    * f1 -> Expression()
	    */
	   public void visit(ExpressionRest n) {
	   }

	   /**
	    * f0 -> IntegerLiteral()
	    *       | TrueLiteral()
	    *       | FalseLiteral()
	    *       | Identifier()
	    *       | ThisExpression()
	    *       | ArrayAllocationExpression()
	    *       | AllocationExpression()
	    *       | NotExpression()
	    *       | BracketExpression()
	    */
	   public void visit(PrimaryExpression n) {
	   }

	   /**
	    * f0 -> <INTEGER_LITERAL>
	    */
	   public void visit(IntegerLiteral n) {
	   }

	   /**
	    * f0 -> "true"
	    */
	   public void visit(TrueLiteral n) {
	   }

	   /**
	    * f0 -> "false"
	    */
	   public void visit(FalseLiteral n) {
	   }

	   /**
	    * f0 -> <IDENTIFIER>
	    */
	   public void visit(Identifier n) {
	   }

	   /**
	    * f0 -> "this"
	    */
	   public void visit(ThisExpression n) {
	   }

	   /**
	    * f0 -> "new"
	    * f1 -> "int"
	    * f2 -> "["
	    * f3 -> Expression()
	    * f4 -> "]"
	    */
	   public void visit(ArrayAllocationExpression n) {
	      n.f3.accept(this);
	   }

	   /**
	    * f0 -> "new"
	    * f1 -> Identifier()
	    * f2 -> "("
	    * f3 -> ")"
	    */
	   public void visit(AllocationExpression n) {
	      n.f1.accept(this);
	   }

	   /**
	    * f0 -> "!"
	    * f1 -> Expression()
	    */
	   public void visit(NotExpression n) {
	      n.f1.accept(this);
	   }

	   /**
	    * f0 -> "("
	    * f1 -> Expression()
	    * f2 -> ")"
	    */
	   public void visit(BracketExpression n) {
	      n.f1.accept(this);
	   }
	
	
	
}
