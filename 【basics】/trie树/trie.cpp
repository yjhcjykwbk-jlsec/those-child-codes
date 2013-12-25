//1315
#include<iostream>
using namespace  std;
//trie树节点 
template <class T,int n>
class node
{public:
       T info;
       bool tag;
       node *link[n];
       node()
       {
             for(int i=0;i<n;i++) link[i]=NULL;
             tag=false;
       }
};
//trie树 
template <class T,int n>  
class trie
{
  public:     
              node<T,n> * root;
              trie(){root=new node<T,n>();}
};
//key加入到tried树 
template <class T,int n>
void add(trie<T,n> t,T a[],T orin,int m)
{
     node <T,n> *p=(t.root),q;
     int s;
     for(int i=0;i<m;i++)
     {
         s=a[i]-orin;
         if(s>=n) exit(0);
         if(p->link[s]==NULL) p->link[s]=new node<T,n>();
         p=p->link[s];
     }
     p->tag=true;
}
//判断是否T[]是否是key 
template <class T,int n>
bool judge(trie<T,n> t,T a[],T orin,int m)    
{
     node <T,n> *p=(t.root);
     int s;
     for(int i=0;i<m;i++)
     {
        s=a[i]-orin;
        if(s>=n) return false;
        p=p->link[s];
        if(p==NULL) return false;
     }
     return p->tag;
}   
int main()
{
     trie<char,26> t;
     int m=3,n=2,i,j,k;
     char key[100][20], dialog[100][100]; 
     int length[100];char tstr[100];
     cin>>m>>n;
     cin.getline(key[0],20);
//输入keys 
     for(i=0;i<m;i++)
     {
        cin.getline(key[i],20);
        cout<<key[i]<<endl;
        add(t,key[i],'a',strlen(key[i]));
     }
     int num=0;char *p;
     cout<<endl;
//输入excuses 
     for(i=0;i<n;i++)
     {
        cin.getline(dialog[i],99);
        p=dialog[i];
        
        num=0;j=0;
        bool last=0,tend=0;
        while(true)
        {
              while(p[j]==' ') j++;
              if(p[j]=='\0')break;
              else
              {
                  k=j;
                  while(p[k]!=' '&&p[k]!='\0') 
                  {
                                tstr[k-j]=p[k];
                                if(p[k]>='A'&&p[k]<='Z') 
                                tstr[k-j]+=32;
                                k++;
                  }
                  tstr[k-j]='\0';
//统计出现次数 
                  if(k-j==1&&((p[j]>='A'&&p[j]<='Z')||(p[j]>='a'&&p[j]<='z'))) {tend=0;last=1;}
                  else 
                  {
                       last=0;
                       if(tend) {num++;tend=0;}
                  }
                  if(judge(t,tstr,'a',k-j)) //判断是否是keyword 
                  {
                        if(!last) tend=1;
                  } 
                   
              }
              j=k;
        }
        if(tend) num++;
        length[i]=num;
     } 
//计算最大出现次数的那些字符串 
     int max=0,index=-1;
     int get[10];
     for(i=0;i<n;i++)
     {
         if(length[i]>max) 
         {
             get[0]=i;
             index=0;
             max=length[i];
         }
         else if(length[i]==max)
         {
              get[++index]=i;
         }
     }
//输出最大出现次数的字符串 
     for(i=0;i<=index;i++)
     {
          cout<<dialog[get[i]]<<"  :"<<length[i]<<endl;
     }
             
   cin>>i;
     } 
