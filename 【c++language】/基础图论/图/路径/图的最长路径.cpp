#include <iostream>
#include <cassert>
#include<algorithm>
#include<iostream>
#include<fstream>
using namespace std;
fstream out("out.txt",ios::out);
using namespace std;
#define far 99;
template<int T>
class Graph
{
	private:
		short (*G)[T];
		const int numOfVertice;
	public:
		Graph(short (*data)[T]):numOfVertice(T),G(data){}
		void Func()
		{
			for(int i=0;i<numOfVertice;i++)
			{	  for(int j=0;j<numOfVertice;j++)
				{
					out<<G[i][j]<<" ";
				}
				out<<endl;
			}
		}  
		//最大最小路径长度
		//矩阵算法 
		void getmaxlength()
		{
			for(int k=0;k<numOfVertice;k++)
			{
				for(int i=0;i<numOfVertice;i++)
				{
					for(int j=0;j<numOfVertice;j++)
					{
						if(G[i][k]+G[k][j]>G[i][j]&&G[i][k]>0&&G[k][j]>0) 
							G[i][j]=G[i][k]+G[k][j];
					}
				}
			}
			Func();
		}  

		void getminlength()
		{
			for(int k=0;k<numOfVertice;k++)
			{
				for(int i=0;i<numOfVertice;i++)
				{
					for(int j=0;j<numOfVertice;j++)
					{
						if(G[i][k]+G[k][j]<G[i][j]&&G[i][k]<99&&G[k][j]<99) 
							G[i][j]=G[i][k]+G[k][j];
					}
				}
			}
			Func();
		}  
		//2 dilistra算法 
		int getmin(int * d,bool *visited) const 
		{
			int min=far;
			int index=-1;
			for(int i=0;i<numOfVertice;i++)
			{
				if(d[i]<min&&!visited[i]) {index=i;min=d[i];}
			}
			return index;
		}
		void dilistra(int f)
		{
			int d[T],i,min;
			bool visited[T];
			for(i=0;i<T;i++)
			{
				d[i]=G[f][i];
				visited[i]=0;
			}
			for(i=0;i<T;i++)
			{//注意一个大括号写成小括号以后会非常难以查出来 
				min=getmin(d,visited);
				if(min<0){out<<"isolated"<<endl;	  return;}
				visited[min]=1;
				out<<d[min]<<" ";
				for(int j=0;j<T;j++)
				{
					if(!visited[j]&&G[min][j]+d[min]<d[j]){d[j]=G[min][j]+d[min];}
				}
			}
			for(i=0;i<T;i++)out<<d[i]<<" ";
		}	

}; 



static short data[9][9]=
{
	{0, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};
static short DaTa[9][9]=
{
	{99, 1, 99, 99, 99, 99, 99, 99, 99},
	{99, 99, 1, 99, 99, 99, 99, 99, 99},
	{99, 99, 99, 1, 99, 99, 99, 99, 99},
	{99, 99, 99, 99, 1, 99, 1, 99, 99},
	{99, 99, 99, 99, 99, 1, 99, 99, 1},
	{99, 99, 99, 99, 99, 99, 1, 99, 99},
	{99, 99, 99, 99, 99, 99, 99, 1, 1},
	{99, 99, 99, 99, 99, 99, 99, 99, 1},
	{99, 99, 99, 99, 99, 99, 99, 99, 99}
};

static short DATA[9][9]=
{
	{0, 3, 99, 99, 99, 99, 99, 99, 99},
	{99, 0, 4, 99, 99, 99, 99, 99, 99},
	{99, 99, 0, 1, 99, 99, 99, 99, 99},
	{99, 99, 99, 0, 2, 99, 30, 99, 99},
	{99, 99, 99, 99, 0, 3, 99, 99, 1},
	{99, 99, 99, 99, 99, 0, 4, 99, 99},
	{99, 99, 99, 99, 99, 99, 0, 5, 4},
	{99, 99, 99, 99, 99, 99, 99, 0, 3},
	{99, 99, 99, 99, 99, 99, 99, 99, 0}
};
short (*d)[9]=data;
short (*e)[9]=DaTa;
short (*y)[9]=DATA;
int main()
{
	Graph<9> g(d);
	g.getmaxlength();

	Graph<9> h(e);
	out<<endl;
	h.getminlength();

	Graph<9> r(y);
	out<<endl;
	r.dilistra(0);
	return 1;
}

