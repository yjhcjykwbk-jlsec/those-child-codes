//
// Generated by JTB 1.3.2
//

package syntaxtree;

/**
 * Grammar production:
 * f0 -> "class"
 * f1 -> Identifier()
 * f2 -> "{"
 * f3 -> ( VarDeclaration() )*
 * f4 -> ( MethodDeclaration() )*
 * f5 -> "}"
 */
public class ClassDeclaration implements Node {
   public NodeToken f0;
   public Identifier f1;
   public NodeToken f2;
   public NodeListOptional f3;
   public NodeListOptional f4;
   public NodeToken f5;

   public ClassDeclaration(NodeToken n0, Identifier n1, NodeToken n2, NodeListOptional n3, NodeListOptional n4, NodeToken n5) {
      f0 = n0;
      f1 = n1;
      f2 = n2;
      f3 = n3;
      f4 = n4;
      f5 = n5;
   }

   public ClassDeclaration(Identifier n0, NodeListOptional n1, NodeListOptional n2) {
      f0 = new NodeToken("class");
      f1 = n0;
      f2 = new NodeToken("{");
      f3 = n1;
      f4 = n2;
      f5 = new NodeToken("}");
   }

   public void accept(visitor.Visitor v) {
      v.visit(this);
   }
   public <R,A> R accept(visitor.GJVisitor<R,A> v, A argu) {
      return v.visit(this,argu);
   }
   public <R> R accept(visitor.GJNoArguVisitor<R> v) {
      return v.visit(this);
   }
   public <A> void accept(visitor.GJVoidVisitor<A> v, A argu) {
      v.visit(this,argu);
   }
}

