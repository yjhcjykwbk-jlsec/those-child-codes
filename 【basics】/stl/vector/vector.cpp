#include<vector>
//#include<stdlb>
#include<algorithm>
#include<iostream>
#include<fstream>
using namespace std;
fstream out("out.txt",ios::out);
struct key
{
       int i;
       int j;
       bool operator < (key b)//ע��1�����������õıȽϺ��������ᱻ�õ�����sort�������� 
       { 
            return i>b.i;
       }
};

       bool com(const key &a,const key &b)
       {
            if((a.i*a.i)%3000<(b.i*b.i)%3000) return 1;//ע�����a<b��˳���ǵ�����˳�� 
            else return 0;
       }

int main()
{ 
        vector <key> v(232);
        for(int i=0;i<v.size();i++)
        {
                v[i].i=i;
        }
        sort(v.begin(),v.end(),com);//ע������com�����Ǻ������ǽṹ�� 
        
        for(int i=0;i<v.size();i++)
        {
               out<<v[i].i<<" ";
        }
}
