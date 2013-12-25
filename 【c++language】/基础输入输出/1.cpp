#include<iostream>
#include<fstream> 
using namespace std;
int main()
{
    fstream fget("c:/a.txt");
    char a[256];
    /*while(fget.getline(a,255))
    {
       cout<<a<<endl;                      
    }*/
    char ch;
    while(fget.get(ch))
    {
          if(ch=='\n'||ch==EOF) cout<<"----"<<endl;
          else cout<<ch;
          }
    fget.close();
    int i;
    cin>>i;
}
