////////////��̬4
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
//���������ָ��������������͡����ʵ������֮��������ݸ�ֵ���������� 
//���������������������a����ǰ������������������virtual�������ε��ø�ֵ����b�����Ļ��� 
//����ֻ�������������������� 
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
