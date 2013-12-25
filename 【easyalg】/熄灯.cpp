#include<iostream>
using namespace std;
bool f(int a[][8],int temp[][8])
{
  int i=0,j=0;
  //从第2行开始 
  for(i=2;i<6;i++)
  {
    for(j=1;j<7;j++)
	{
		temp[i][j]=(temp[i-2][j]+temp[i-1][j-1]+temp[i-1][j]+temp[i-1][j+1]+a[i-1][j])%2;
	}
  }
  i=6;
  for(j=1;j<7;j++){if((temp[i-2][j]+temp[i-1][j-1]+temp[i-1][j]+temp[i-1][j+1]+a[i-1][j])%2!=0)return false;}
  return true;
} 


int main()
{
  int a[50][6][8];
  int temp[6][8];
  int n,i,j,k,p;
  cin>>n;
  for(i=0;i<6;i++){temp[i][0]=temp[i][7]=0;}
  for(i=0;i<8;i++)temp[0][i]=0;
  
  for(i=0;i<n;i++)
  {
    for(j=0;j<30;j++)
     cin>>a[i][j/6+1][j%6+1];
  }
  for(i=0;i<n;i++)
  {
     for(j=0;j<6;j++)
       for(k=0;k<8;k++)
         temp[j][k]=0;
     for(j=0;j<64;j++)
	 {
        for(k=5;k>=0;k--)
		{ 
          temp[1][k+1]=(j>>k)&1;
		}
        if(f(a[i],temp)){for(p=0;p<30;p++){a[i][p/6+1][p%6+1]=temp[p/6+1][p%6+1];}break;}
	 }
  } 
  for(i=0;i<n;i++)
  {
    printf("PUZZLE #%d\n",i+1);              
    for(j=1;j<6;j++)
	{ for(k=1;k<6;k++)
	{ printf("%d ",a[i][j][k]);}
   printf("%d\n",a[i][j][6]);}
  }
  return 1;
}
