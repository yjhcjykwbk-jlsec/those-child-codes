#include<iostream>
using namespace std;
void f(char *b,char *a,int k)
{
     int i,j,jin=0,n,res,r,c,d;
     strcpy(a,b);
     for(i=127;i>=5;i--)a[i]='0';
     char temp[128];
     for(n=1;n<k;n++){
     for(i=0;i<128;i++)temp[i]='0';
     for(i=0;i<5;i++)
     {
           jin=0;
           d=b[i]-'0';
           for(j=0;j<128;j++)
           {
              c=a[j]-'0';
              res=c*d;
              temp[i+j]+=jin+res%10;
              jin=res/10+(temp[i+j]-'0')/10;
              temp[i+j]=(temp[i+j]-'0')%10+'0';
           }
     }
     for(i=0;i<128;i++)a[i]=temp[i];
  }
}
int main()
{
   char g[7], a[7], b[128];
   int k,i,j,point=0,p=4;
   cin>>g>>k;           
   for(i=0;g[i]!='\0'&&i<=5;i++) {if(g[i]=='.')point=5-i; else {a[p]=g[i];p--;}}
   a[5]='\0';
   f(a,b,k);
   j=127;
   while(b[j]=='0'&&j>=point*k) j--;
   while(j>=point*k) {printf("%c",b[j]);j--;}
   for(i=0;i<=j;i++) {if(b[i]=='0')b[i]='\0';else break;}
   if(i<=j) 
       printf(".");
   while(j>=0&&b[j]!='\0'){printf("%c",b[j]);j--;}
}            
     
