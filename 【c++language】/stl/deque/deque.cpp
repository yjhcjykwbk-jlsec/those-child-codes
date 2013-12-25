#include<deque>
#include<algorithm>
#include<fstream>
using namespace std;
fstream out("out.txt",ios::out);
int main()
{
    deque<string> s;
    //插入方式：两头插入 
    s.push_front("sfdf");
    s.push_back("gf");
    deque<string>::iterator p;
    //访问方式 
    for(p=s.begin();p!=s.end();p++)
    {
        out<<*p<<endl;
    }
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl;
    //删除元素
    s.pop_front();
    out<<"after erased:"<<endl;
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl; 
    
    s[1]="dsdsdsfsdfsd";//无法新增元素 只能替换元素 
    out<<"after added:"<<endl;
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl; 
    
    s[0]="dsdsdsfsdfsd";//无法新增元素 只能替换元素
    out<<"after added:"<<endl;
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl; 
    
    //清空
    out<<"after clear:"<<endl;
    s.clear();
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl;  
    
    //sort
    out<<"after sort:"<<endl;
    s.push_front("zjgfhjgdf");
    s.push_back("ddseas");
    s.push_back("aaw");
    sort(s.begin(),s.end());
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl;
} 
