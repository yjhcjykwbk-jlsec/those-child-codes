#include <iostream>
using namespace std;
char a[8][8];
int used[8]={0};
int n,num;//numΪ����Ŀ 
int number=0;//�ŷŷ����� 
void f(int m,int k)//�ӵ�m�п�ʼ�ŵ�k���� ��
{   
    if(k>num){ number++;return;}
    int i,j;
    for(j=m;j<n-(num-k);j++)
    { 
        for(i=0;i<n;i++)
        {
            if(a[j][i]=='#'&&0==used[i])
            {
               used[i]=1;
               f(j+1,k+1);
               used[i]=0;
            }
        }
    }
} 
int main()
{
    int i;
    while(cin>>n>>num&&(n!=-1||num!=-1))
    {
      for(i=0;i<n;i++)
      { 
          scanf("%s",a[i]);
      }
      number=0;
      f(0,1);//��0�п�ʼ�ŵ�һ����
      printf("%d\n",number);
    }
    return 1; 
    
} 
