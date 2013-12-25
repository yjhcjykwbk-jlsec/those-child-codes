#include <iostream>
using namespace std;
void f(bool a[][20],bool b[][20],int n,int contem,int &num);//
void paint(bool a[][20],int i,int j)
{
     int k;
     for(k=i-1;k<=i+1;k++) a[k][j]=(!a[k][j]);
     for(k=j-1;k<=j+1;k++) a[i][k]=(!a[i][k]);
     a[i][j]=(!a[i][j]);
}
//主调函数
//n为真实的行列数 
//对第一行paint方式进行枚举
//然后调用f，推算下面几行
void get(bool a[][20],bool b[][20],int n,int k,int contem,int &num)
{
    if(k==0) { f(a,b,n,contem,num);return;}
	//不paint 1k
    get(a,b,n,k-1,contem,num);
	//paint 1k
    paint(a,1,k);
    get(a,b,n,k-1,contem+1,num); 
    paint(a,1,k);//还原paint 
    return ;
}
    
void f(bool a[][20],bool b[][20],int n,int contem,int &num)//
{
     int i=0,j=0;
     int success=1;
	 int temp=contem;
     for(i=1;i<=n;i++)
     {
       for(j=1;j<=n;j++)
       {
           b[i][j]=a[i][j];
       }
     }
     for(i=2;i<=n;i++)
     {
       for(j=1;j<=n;j++)
	   {
		   if(b[i-1][j]) {paint (b,i,j);temp++;}
	   }
     }
     for(i=1;i<=n;i++){ if(b[n][i]) {success=0;break;}}
     if(success) 
     {
                if(num>temp){num=temp;}
     }
}

int main()
{
    int n,m;int *res;
    cin>>n;
    res=new int(n);
    int i,j,k;
    char t[20];
    bool a[20][20],b[20][20];
    for(i=0;i<n;i++)
    {
       cin>>m;
       for(j=0;j<=m+1;j++)
        { for(k=0;k<=m+1;k++)
           {
               a[j][k]=true;
           } 
        }
       for(j=1;j<=m;j++)
        { 
           cin>>t;
           for(k=1;k<=m;k++)
           {
			   if(t[k-1]=='w'){a[j][k]=true;}
               else a[j][k]=false;
           } 
        }
      res[i]=401;
      get(a,b,m,m,0,res[i]);
    }
    for(i=0;i<n;i++){printf("%d\n",res[i]);}
}
       
                    
                    

