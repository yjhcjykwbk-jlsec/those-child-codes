#include<fstream> 
#include<iostream>
using namespace std;
using std::fstream; 

using std::cin;
using std::cout;
int main()
{
    fstream g1("4.txt");
    fstream g2("5.txt");
    g1.seekg(0);
    g2.seekg(0);
    char a,b;
    int rr=0;
    while((g1.get(a))&&(g2.get(b)))
    {
      if(a!=b){ cout<<a<<" "<<b<<endl;rr=1;break;}
      cout<<a;
      //cout<<g1.tellg();
    }
     if(rr==0){cout<<"notfound";}
    cin>>rr;
    return 1;
}
