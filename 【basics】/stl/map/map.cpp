//stl
#include<iostream>
#include<string>
#include<map>
#include<fstream> 
using namespace std;
fstream out("out.txt",ios::out); 

//�Զ���ȽϽṹ�� 
template <class T>
struct compare/////////////1��ע���ǽṹ�� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
       bool operator()(const T &a,const T &b) 
       {
          return a<b;//����b�󣬲嵽�������� 
       }
};
template <class T>
struct compare1
{
       bool operator()(const T &a,const T &b) 
       {
          return a>b;//˳��a�󣬷����������� 
       }
};
typedef compare<string> com;
typedef compare1<string> com1;

//�Զ����������������ȽϺ���
struct key
{
       int info;
       string name;
       bool operator <(const key & a) const////////2��operator <(const T&a)�����Ĳ�����const���͵�~~~~~~~~~ 
       {
            return info<a.info;//����a�󣬲��뵽�������� 
       }
      // friend ostream & operator << (ostream &out,key &a) ;
};
       ostream& operator << (ostream &out,const key &a) //////3: operator <<(&out,const T &a)�ڶ���������const���͵� 
       {
            out<<a.info<<" "<<a.name<<" ";
            return out;
       }
////////////////////////////////////////////////////// 
int main()
{
    map<char,int> q;
    
    //���� 
    q['s']=323;
    q.insert(pair<char,int>('d',12222)); 
    out<<"q['d']="<<q['d']<<endl;
    out<<"q['s']="<<q['s']<<endl;
    q.erase('s');
    out<<"after erased,q['s']="<<q['s']<<endl;
    
    //���� 
    map<char,int>::reverse_iterator pointer;
    out<<"after travel:"<<endl;
    for(pointer= q.rbegin();pointer!= q.rend();pointer++)
    {
                 out<<pointer->first<<":"<<pointer->second<<endl;
    }
    
    ////////////�Զ���ȽϺ����ṹ����ٴβ�������� 
    map<string,char,com1> ww;//com1��˳��com������ 
    
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
    
    //�Զ���ȽϺ����Ľṹ��
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
    
