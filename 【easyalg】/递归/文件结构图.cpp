#include <iostream>
#include <string.h>
using namespace std;
char Array[100][20];
char tab[7]="|     ";
const int max=100;
void f(int &ptr,int gride)//gride为第几级目录 ，ptr为info下标 
{
    //char info[20][20];
    int info[20];
    char temp[20];
    int i,j=0,k=0,m,t;
    for( i=0;i<gride;i++)
      printf("%s",tab);
    printf("%s\n",Array[ptr]);
    while(sscanf(Array[++ptr],"%s",temp))
    {
         if(strcmp(temp,"]")==0||strcmp(temp,"*")==0) break;
         if(temp[0]=='d')
         {
             f(ptr,gride+1);
         }
         if(temp[0]=='f')
         {
             //strcpy(info[j++],temp);
             info[j++]=ptr;
         }  
    }             
     for(k=0;k<=j-1;k++)
     {
         for(m=j-1;m>k;m--)
         {
             if(strcmp(Array[info[m]],Array[info[m-1]])<0)
              {
                    t=info[m];info[m]=info[m-1];info[m-1]=t;                                      
                  // strcpy(temp,Array[info[m]);
                  // strcpy(info[m],info[m-1]);
                  //strcpy(info[m-1],temp);
              }
         }
     }                              
    for(k=0;k<=j-1;k++)
    {
       for( i=0;i<gride;i++)
         printf("%s",tab);
       printf("%s\n",Array[info[k]]);
    }
}

        
int main()
{ 
    char temp[20];
    int i=0;
    while(cin>>Array[i++])
    {
        if(strcmp(Array[i-1],"*")==0) break;
    }
    int ptr=0;
    f(ptr,0);
    cin>>i;
}
