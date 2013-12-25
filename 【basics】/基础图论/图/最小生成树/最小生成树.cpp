#include<fstream>
#include<iostream>
#include<queue>
#define FAR 99;
//#include<heap.h>////////////////// 
using namespace std;
fstream out("out.txt",ios::out);
//边 
struct dt
{
       int f;
       int t;
       int len;
};
//比较边长度 
struct cmp
{
       bool operator()(const dt& a,const dt&b)
       {
            if(a.len>b.len) return 1;
            else return 0;
            } 
};
//并查集的操作 
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
             //最小生成树算法 
             int mintree()
             {
                 int own[T];
                 dt temp;
                 int i,j;
                 //构造并查集 
                 for(i=0;i<T;i++)
                 {
                                 own[i]=i;
                 }
                 //优先队列 
                priority_queue<dt,vector<dt>,cmp> q;
                //插入各边 
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
                    //找到一条边跨越两个不同集合为止 
                    while(judge(own,temp.f,temp.t)){temp=q.top();q.pop();}
                    out<<temp.f<<" "<<temp.t<<endl;
                    //并归并两个集合为一个 
                    merge(own,temp.f,temp.t);
                }
                //输出并查集 
                out<<endl; 
                for(i=0;i<T;i++)  getown(own,i); //精简并查树 
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
