#include<bitset>
#include<algorithm>
#include<iostream>
#include<fstream>
using namespace std;
fstream out("out.txt",ios::out);
int main()
{
    bitset<100> set;
    set.set();
    out<<set[23]<<endl;
    set.set(23,0);
    out<<set[23]<<endl;
    set.reset(34);
    out<<set[34]<<endl;
    out<<set<<endl;
}
