#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    fstream f;
    f.open("test.txt",ios::out);
    if(!f){cout<<"error"; }
    f<<"dssfdsf";
    f.close(); 
    int i;
    cin>>i;
}
