#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
template <class T>
class MyMax
{
	public:
		T * pMax;  //ָ�����ڴ�����ֵ�ı���
		bool bFirst; //��¼���ֵʱ���õ��ı��
		MyMax (T * p):bFirst(true),pMax(p) { };
//��ͷ
       T  operator()(){ return *pMax;}
       MyMax<T> & operator *(){return *this;}
       T &operator ++(){}
      void operator=(T &value)
       {
            if(*pMax<value||bFirst==true)
            {
                *pMax=value;
                bFirst=false;
            }
            
       }

//����
//��β
};
class A {
public:
	int i;
	A( int n) :i(n) { };
	A() { };
};
bool operator < ( const A & a1, const A & a2)
{
	return a1.i < a2.i ;
}
ostream & operator<<( ostream & o, const A & a)
{
	o << a.i;
	return o;
}
main()
{
	A a[5] = {A(1),A(5),A(3),A(4),A(2)};
	int b[9] = {1,5,30,40,2,136,80,20,6};
	int nMax; 
A aMax; 
	MyMax<A> outputa( & aMax);
	copy(a,a+5,outputa); 
	cout << outputa() << endl;
	MyMax<int> output( & nMax);
	copy(b,b+9,output);
	cout << output() << endl;
	int i;cin>>i;
}

