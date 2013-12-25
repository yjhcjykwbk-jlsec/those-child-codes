//stl
#include<iostream>
#include<string>
#include<map>
#include<fstream> 
using namespace std;
fstream out("out.txt",ios::out); 

//自定义比较结构体 
template <class T>
struct compare/////////////1：注意是结构体 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
       bool operator()(const T &a,const T &b) 
       {
          return a<b;//逆序，b大，插到右子树上 
       }
};
template <class T>
struct compare1
{
       bool operator()(const T &a,const T &b) 
       {
          return a>b;//顺序，a大，放在右子树上 
       }
};
typedef compare<string> com;
typedef compare1<string> com1;

//自定义主键，并包含比较函数
struct key
{
       int info;
       string name;
       bool operator <(const key & a) const////////2：operator <(const T&a)函数的参数是const类型的~~~~~~~~~ 
       {
            return info<a.info;//逆序，a大，插入到左子树上 
       }
      // friend ostream & operator << (ostream &out,key &a) ;
};
       ostream& operator << (ostream &out,const key &a) //////3: operator <<(&out,const T &a)第二个参数是const类型的 
       {
            out<<a.info<<" "<<a.name<<" ";
            return out;
       }
////////////////////////////////////////////////////// 
int main()
{
    map<char,int> q;
    
    //插入 
    q['s']=323;
    q.insert(pair<char,int>('d',12222)); 
    out<<"q['d']="<<q['d']<<endl;
    out<<"q['s']="<<q['s']<<endl;
    q.erase('s');
    out<<"after erased,q['s']="<<q['s']<<endl;
    
    //周游 
    map<char,int>::reverse_iterator pointer;
    out<<"after travel:"<<endl;
    for(pointer= q.rbegin();pointer!= q.rend();pointer++)
    {
                 out<<pointer->first<<":"<<pointer->second<<endl;
    }
    
    ////////////自定义比较函数结构体后再次插入和周游 
    map<string,char,com1> ww;//com1：顺序，com：倒序 
    
    ww["dsd"]='s';
    ww["asd"]='f';
    ww["zhsd"]='u';
    ww["iou"]='w';
    map<string,char,com1>::reverse_iterator point;
    out<<"after travel:"<<endl;
    for(point= ww.rbegin();point!= ww.rend();point++)
    {
                 out<<point->first<<":"<<point->second<<endl;
    }
    
    //自定义比较函数的结构体
    map<key,char> aa; 
    key a1={12,"dsd"};
    key a2={23,"fgh"}; 
    key a3={3,"ouh"}; 
    aa[a1]='s';
    aa[a2]='f';
    aa[a3]='r';
    map<key,char>::reverse_iterator p;
    out<<"after travel:"<<endl;
    for(p= aa.rbegin();p!= aa.rend();p++)
    {
          out<<(p->first);
          out<<":"<<p->second<<endl;
    }
}
    
