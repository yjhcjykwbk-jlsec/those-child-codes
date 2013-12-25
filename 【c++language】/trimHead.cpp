///  去除代码的首部行号 

#include <iostream>
#include <fstream>
using namespace std;
int main()
{
     ifstream fi("in.txt");
     char input[100];
     string res;
     int i;
     while(fi.getline(input,100)!=NULL)
     {
        i=0;
        while(input[i]<='9'&&input[i]>='0')i++;
        if(input[i]!=0) {res+=(input+i);res+='\n';} 
     }
     fstream f("out.txt",ios::out);
     f<<res;
     return 1;
}      
     
