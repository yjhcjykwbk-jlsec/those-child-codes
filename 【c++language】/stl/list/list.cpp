#include<list>
#include<algorithm>
#include<iostream>
#include<fstream>
using namespace std;
fstream out("out.txt",ios::out);
int main()
{
    list<int> l(299);
    l.clear();
    l.push_back(2323);
    l.push_front(34324);
    l.push_front(34);
    l.push_back(34);
    list<int>::iterator p=l.begin();
    p++;
    l.insert(p,3);
    p=l.end();
    //迭代器只能-- ++ 
    out<<"reverse visiting 1:"<<endl; 
    while(true)
    {
               p--;
               out<<*p<<endl;
               if(p==l.begin())break;
    }
    //另一种反向遍历方法 
    out<<"reverse visiting 2:"<<endl; 
    list<int>::reverse_iterator q=l.rbegin();
    while(true)
    {
               out<<*q<<endl;
               q++;
               if(q==l.rend())break;
    }
    //sort
    l.sort();
    p=l.begin();
    out<<"l.sort:"<<endl; 
    while(true)
    {
               out<<*p<<endl;
               p++;
               if(p==l.end())break;
    }
    //find 注意：find不属于list 
    p=find(l.begin(),l.end(),34);
    out<<"position of 34:"<<(*p)<<endl;
    //删除
     out<<"34 removed:"<<endl; 
    l.remove(34); 
    p=l.begin();
    while(true)
    {
               out<<*p<<endl;
               p++;
               if(p==l.end())break;
    }
    out<<"first and last removed:"<<endl; 
    p=l.begin();
    l.erase(p); 
    l.pop_back();
    p=l.begin();
    while(true)
    {
               out<<*p<<endl;
               p++;
               if(p==l.end())break;
    }
}
      
