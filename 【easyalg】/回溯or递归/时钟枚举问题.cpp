///////////////完美ac，一次通过，ohyeah 
#include <iostream>
using namespace std;
void f(int *s,int d[][9],int *choice,int *cho,int n,int &minTime,int Time);
int main()
{
    int i,j;
    int choice[9]={0};
    int cho[9]={0};
    static int d[9][9]={{1,1,0,1,1,0,0,0,0},{1,1,1,0,0,0,0,0,0},{0,1,1,0,1,1,0,0,0},{1,0,0,1,0,0,1,0,0},{0,1,0,1,1,1,0,1,0},{0,0,1,0,0,1,0,0,1},{0,0,0,1,1,0,1,1,0},{0,0,0,0,0,0,1,1,1},{0,0,0,0,1,1,0,1,1}};
    int s[9];
    int minTime=50,Time=0;
    for(j=0;j<9;j++)
    {
           cin>>s[j];
           s[j]=(4-s[j])%4; 
    }
    f(s,d,choice,cho,8,minTime,Time);
    for(i=0;i<9;i++)
    {
           if(choice[i]>0)  
           {
                for(j=0;j<choice[i];j++)
                    cout<<i+1<<" ";
           }
    }
}
 //回溯递归进行move   
void f(int *s,int d[][9],int choice[],int *cho,int n,int &minTime,int Time)
{
    if(n==-1) return;
    int i,j,k,temp,check,reach;
    int t=Time;
    for(i=0;i<4;i++)
    {
           t=Time+i;
           if(t>=minTime) break;
           cho[n]=i;
           temp=0;
           check=0;
           
           for(j=0;j<9;j++)
           {
                s[j]=(s[j]-d[n][j]*i+4)%4;
                temp+=s[j];
                if(s[j]+t>=minTime)
                { check=1;}
           }
           reach=0;
           //move成功 
           if(temp==0) 
           {
                if(t<minTime)
                {
                                minTime=t;
                                for(k=8;k>=n;k--) choice[k]=cho[k]; 
                                reach=1;
                                
                }
           }
           else if(!check)  f(s,d,choice,cho,n-1,minTime,t);
           //还原数据，回溯 
           for(j=0;j<9;j++)
           {
                s[j]=(s[j]+d[n][j]*i+4)%4;
           }
           //已经超过目前已有最少次数 
           if(reach) break;
    }
}
           
    
