#include<iostream>
using namespace std;
#define  SIZE 1000
struct btree
{
int size;
int v[SIZE];
int rank[SIZE];
};

void init(btree & t,int n)
{
	for (int i=1; i<=n; ++i)
	{
		t.v[i]=i;
		t.rank[i]=0;
	}
	t.size=n;
}

int find(btree &t,int p)
{
	if (t.v[p]==p)
		return p;
	else
	{
		t.v[p]=find(t,t.v[p]);
		return t.v[p];
	}
}

void judge(btree &t,int a, int b)
{
	int fa, fb;
	fa=find(t,a);
	fb=find(t,b);
	if (fa==fb)
		return;
	if (t.rank[fa]>t.rank[fb])
	{
      	t.v[fb]=fa;
      	t.rank[fa]+=t.rank[fb];
    }
	else
	{
		t.v[fa]=fb;
		t.rank[fb]+=t.rank[fa];
	}
}
int mintwo(btree &t,int value[],int &fir,int &sec)
{
     int i;
     fir=sec=-1;
     for(i=0;i<t.size;i++)
     {
           if(t.v[i]!=i)
             continue;
           if(fir<0||value[i]<value[fir]) { sec=fir;fir=i;}
           else if(sec<0||value[i]<value[sec]) sec=i;
     }
}
int huffman( btree &t,int value[])
{
     int j=t.size;
     int a,b;
     int cost=0;
     for(int i=1;i<j;i++)
     { 
     mintwo(t,value,a,b);
     judge(t,a,b);
     cout<<value[a]<<" "<<value[b]<<endl;
     value[t.v[a]]=value[a]+value[b];
     cost+=value[t.v[a]];
     
     }
     return cost;
}     
int main()
{
    btree t;
    init(t,5);
    int value[10]={2,4,6,7,3};   
    cout<<huffman(t,value);
    int i;cin>>i;
}
