////////////多态4
#include<iostream>
using namespace std;
class A
{
      public:
      virtual ~A(){
      cout<<"destructor a"<<endl;
      } 
       void f()
      {
              cout<<"fuck a"<<endl;
      }
};
class B:public A{
      public:
      ~B()
      {
      cout<<"destructor b"<<endl;
      }
      virtual void f()
      {
              cout<<"fuck b"<<endl;
      }
};
     
      class C:public B{
      public:
      ~C()
      {
      cout<<"destructor C"<<endl;
      }
      void f()
      {
              cout<<"fuck c"<<endl;
      }
};
//正常情况看指针变量声明的类型。如果实，调用之。否则根据赋值类型往上找 
//析构函数：如果声明的类a和向前基类有析构函数声明virtual，会依次调用赋值类型b和它的基类 
//否则只调用声明类型析构函数 
int main()
{
   {  
     A* pa;
     pa=new C;
     pa->f();//a
     cout<<endl;
     
     B *pb=new C;
     pb->f();//c
     cout<<endl;
     
     C *pc=new C;
     pc->f();//c
     cout<<endl;
     
     A *pg=new B;
     pg->f();//a
     cout<<endl;
     
     A *ph=new A();
     ph->f();//a 
     cout<<endl;
     
     delete pb; 
     cout<<endl;
     
     delete pg; 
     cout<<endl;
     
     delete pa;
     cout<<endl;
     
     delete pc;
     }
     //delete pa;
     int i;
     cin>>i;
     }
