#include<iostream>
using namespace std;
class Apple {
	private :
		static int nTotalNumber;
	public:
		Apple()
		{ nTotalNumber ++; }
		~Apple( ) { nTotalNumber --;cout<<"deleted "<<nTotalNumber<<endl; }
		static void PrintTotal() 
		{ cout << nTotalNumber << endl; }
		
};
int Apple::nTotalNumber = 0; 
Apple Fun( const  Apple & a ) 
{  a.PrintTotal(); 	return a ;  }
Apple  f(Apple &t){return t;} 
int main () {
	{
         Apple * p = new Apple[4];
	Fun( p[2]);  //4
	p[0].PrintTotal();//3
	f(p[0]);
	p[0].PrintTotal();//////2
	Apple p1, p2;
	p[0].PrintTotal();//4
	delete [] p;
	p1.PrintTotal();  //0
}
//-2 
{Apple p;
p.PrintTotal(); 
}
//-2

	int i;
	cin>>i;
}
