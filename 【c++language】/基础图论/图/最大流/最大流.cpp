#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
fstream out("out.txt",ios::out);
#define max 999;

template<int num> 
struct stGraph
{
       int s;
       int t;
       short G[num][num];//��ǰȡֵ
       short (*M)[num];//���ȡֵ
       short R[num][num];//ʣ������
       short T[num][num];//��������֮��ľ���
       //��ʼ�� 
       void init()
       {
            s=0,t=num-1;
            int i,j;
            for(i=0;i<num;i++)
            {
               for(j=0;j<num;j++)
               {
                   G[i][j]=0; 
                   if(M[i][j]>0){R[i][j]=M[i][j];T[i][j]=1;}
                   else {R[i][j]=0;T[i][j]=max;}
               }
            }
       }
       //��������ͼ 
       void play()
       {
            int i,j;
            for(i=0;i<num;i++)
            {
               for(j=0;j<num;j++)
               {
                   out<<G[i][j]<<" ";
               }
               out<<endl;
            }
       }
       //dilistra �������������·�� 
       int getmin(short *v,bool *visited)
       {
           int res=max;
           int index=-1;
           int i=0;
           for(i=0;i<num;i++)
           {
               if(v[i]<res&&!visited[i])
               {
                  res=v[i];index=i;
               }
           }
           return index;
       }
       bool findnearestpath(int before[])
       {
            int i,j,min;
            short v[num];
            bool visited[num];
            for(i=0;i<num;i++)
            {
                v[i]=T[s][i];
                visited[i]=0;
                before[i]=s;
            }
            min=getmin(v,visited);
            while(min!=t&&min!=-1)
            {
               visited[min]=1;
               for(i=0;i<num;i++)
               {
                  if(T[min][i]==1&&!visited[i]&&1+v[min]<v[i])
                  {
                      v[i]=T[min][i]+v[min];
                      before[i]=min;
                  }
               }
               min=getmin(v,visited);
            }
            if(min==-1) return false;
            return true;
       }     
       //����     
       int expand(int before[])
       {
            int j=t,i=before[t];
            int x=max;
            while(true)
            {
                if(R[i][j]<x) x=R[i][j];
                if(i==s) break;
                j=i;
                i=before[j];
            }
            j=t;i=before[t];
            while(true)
            {
                if(M[i][j]>0)
                {
                   G[i][j]+=x;
                   R[i][j]-=x;
                   if(i!=s&&j!=t)R[j][i]+=x;//////////////////////////////////////////////////////ʮ����Ҫ 
                }//s��t���޷����� 
                else 
                {
                     G[j][i]-=x;
                     R[i][j]-=x;
                     R[j][i]+=x;
                }
                if(R[i][j]>0) T[i][j]=1;
                else T[i][j]=max;
                if(R[j][i]>0) T[j][i]=1;
                else T[j][i]=max;
                if(i==s) break;
                else {j=i;i=before[j];}
            }
            return x;
       }
        
       void maxflow()
       {
             int d[num];
             init();
             int total=0;
             while(true)
             {
                        if(findnearestpath(d))
                        total+=expand(d);
                        else break;
             }
             out<<total<<endl;//������� 
       }
                        

};

    
int main()
{
    stGraph<8> st;
    short data[8][8] = {
          {0,1,2,4,0,0,0,0},
          {0,0,0,0,1,0,0,0},
          {0,0,0,0,1,1,0,0},
          {0,0,0,0,2,0,2,0},
          {0,0,0,0,0,2,0,2},
          {0,0,0,0,0,0,0,4},
          {0,0,0,0,0,4,0,1},
          {0,0,0,0,0,0,0,0}
          };   
    st.M=data;
    st.init();
    st.maxflow();
    st.play();
}
              
        
