#include<iostream>
#include<vector>
using namespace std;
class A {
private :
      int nId;
public:
      A(int n) { 
             nId = n; 
            cout << nId << " contructor" << endl; 
       };
       A( const A & a ) {
            nId = a.nId ;
    cout << nId << " copy constructor" 
	<< endl;
       }
       ~A( )
      {  cout << nId << " destructor" << endl;  }
};
main()
{
      A* pp,*qq;
   { { //vector<A*> vp;
    pp=new A(1);
    //qq=new A(13);
    // vp.push_back(pp);
     //vp.push_back(qq);
     vector<A> v;
     v.push_back (23);
     v.push_back(*pp);
     }
     //cout<<vp[0];
    // delete pp;
    // delete qq;
     int i;
     cin>>i; }
}
