#include<fstream>
#include<iostream>
#include<queue>
#define FAR 99;
//#include<heap.h>////////////////// 
using namespace std;
fstream out("out.txt",ios::out);
//�� 
struct dt
{
       int f;
       int t;
       int len;
};
//�Ƚϱ߳��� 
struct cmp
{
       bool operator()(const dt& a,const dt&b)
       {
            if(a.len>b.len) return 1;
            else return 0;
            } 
};
//���鼯�Ĳ��� 
int getown(int v[],int f)
{
    if(v[f]==f) return f;
    return (v[f]=getown(v,v[f]));
}
bool judge(int v[],int f,int t)
{
     return (getown(v,f)==getown(v,t));
}
void merge(int v[],int f,int t)
{
     v[getown(v,f)]=v[getown(v,t)];
}

template<int T>
class Graph
{
      private:
             short (*G)[T];
             const int numOfVertice;
      public:
             Graph(short (*data)[T]):numOfVertice(T),G(data){}
             //��С�������㷨 
             int mintree()
             {
                 int own[T];
                 dt temp;
                 int i,j;
                 //���첢�鼯 
                 for(i=0;i<T;i++)
                 {
                                 own[i]=i;
                 }
                 //���ȶ��� 
                priority_queue<dt,vector<dt>,cmp> q;
                //������� 
                for(i=0;i<T;i++)
                {
                    for(j=i+1;j<T;j++)
                    {
                        if(G[i][j]<99)
                         { 
                             temp.f=i; temp.t=j; temp.len=G[i][j];
                             out<<temp.f<<" "<<temp.t<<" "<<temp.len<<" "<<"inserted"<<endl;
                             q.push(temp);
                         }
                    }
                }
                out<<endl;
                for(i=1;i<T;i++)
                {
                    if(q.empty()) out<<"error"<<endl;
                    temp=q.top();
                    q.pop(); 
                    //�ҵ�һ���߿�Խ������ͬ����Ϊֹ 
                    while(judge(own,temp.f,temp.t)){temp=q.top();q.pop();}
                    out<<temp.f<<" "<<temp.t<<endl;
                    //���鲢��������Ϊһ�� 
                    merge(own,temp.f,temp.t);
                }
                //������鼯 
                out<<endl; 
                for(i=0;i<T;i++)  getown(own,i); //���򲢲��� 
                for(i=0;i<T;i++)  out<<"own["<<i<<"]="<<own[i]<<endl;
             }
};
short data[5][5]=
{
      {0,2,4,1,5},
      {0,0,3,99,99},
      {0,0,0,6,4},
      {0,0,0,0,7},
      {0,0,0,0,0}
};
short (*d)[5]=data;
int main()
{
    Graph<5> q(d);
    q.mintree();
}
