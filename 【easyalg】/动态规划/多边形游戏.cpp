#include <iostream>
using namespace std;
int Max[50][50];//��¼ij֮������ֵ
int Min[50][50];
int  op[50];//������ 
char cl[50];//����� 
int n; 

//���㺯��
//k��Ӧ�����cl[k] 
int function(int aop,int k,int bop)
{ 
    if(cl[k]=='x')return (aop*bop);
    else return (aop+bop);
}
//��ʼ�������Сֵ���� 
int initialize()
{     
      int i,j,k; 
      int max=0,min=0,temp1,temp2; 
      int a,b; 
      for(i=0;i<n;i++) 
      {
          Max[i][0]=Min[i][0]=op[i]; 
          Max[i][1]=Min[i][1]=function(op[i],(i+1)%n,op[(i+1)%n]);//�����i����i+1�ߵ�ֵ
      }
      for(i=2;i<n;i++)//��j�� j+i֮�����ֵ��Сֵ 
      {
        for(j=0;j<n;j++)
        {
           for(k=1;k<=i;k++) //i���зַ�ʽ 
           {
             temp1=function(Max[j][k-1],(j+k)%n,Max[(j+k)%n][i-k]);//��j--��j+k-1__��j+k--��j+i 
             temp2=function(Min[j][k-1],(j+k)%n,Min[(j+k)%n][i-k]);
             //���������Сֵ 
             if(k==1) {max=((temp1>temp2)?temp1:temp2);min=((temp2>temp1)?temp1:temp2);}
             else {
                  if(temp1>temp2) {a=temp1;b=temp2;} 
                  else            {a=temp2;b=temp1;}
                  if(max<a) max=a;
                  if(min>b) min=b;
                  }
           }
           Max[j][i]=max;Min[j][i]=min;
         }
      }
}
                
                                      
int main()
{
    cin>>n;
    int i;
    for(i=0;i<n;i++)
    {
       cin>>cl[i]>>op[i];
    }
    initialize();
    int temp=Max[1][n-1];
    int j=-1;
    int a[30];
    for(i=0;i<n;i++)
    {//Max[i][n-1]��Ӧ������i+1��ĶΣ���i����i-1) 
       if(Max[i][n-1]>temp)
       {
           temp=Max[i][n-1];
           j=0;
           a[j]=i+1;//���±��1���Ǳߵı�� 
       }
       else if(Max[i][n-1]==temp)
       {
           a[++j]=i+1;
       }
    }
    cout<<temp<<endl;
    for(i=0;i<j;i++)
    {
       cout<<a[i]<<" ";
    } 
    cout<<a[j];
    return 1;
}
     
       
    
