///////////////
//HugeInt.cpp//
///////////////
#include<iostream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
const int MAX = 110;

class CHugeInt
{
    private:
           char info[MAX];
           int Num;
    public:
           CHugeInt(){Num=0;}
           CHugeInt(char *temp)
           {
              int i=0;
              while(temp[i]!=0) {info[i]=temp[i];i++;}
              info[i]='\0';
              Num=i;
           }
           CHugeInt(int a)
           {
              int temp=a,i=0;
              while(temp>9){temp=temp/10;i++;}
              Num=i+1; 
			  info[Num]=0;
              temp=a;
              while(temp!=0)
              {
                info[i--]=temp%10+'0';
                temp=(temp/10);
              }
           }
           CHugeInt & operator =(CHugeInt &a)
           {
                Num=a.Num;
                for(int i=0;i<=Num;i++)
                {   
                    info[i]=a.info[i];
                }
                return *this;
           }  
          CHugeInt  operator + (const CHugeInt &b) const
           {
               int num,i,m,n=0,l,r;
               char left,right;
               CHugeInt temp;
               num=Num;
               if(num<b.Num) {num=b.Num;}
               l=Num-1;r=b.Num-1;
               for(i=num-1;i>=0;i--,l--,r--)
               {   
                   if(l>=0) left=info[l]; else left='0';
                   if(r>=0) right=b.info[r]; else right='0';
                   m=n+left+right-'0'*2;
                   temp.info[i]=(m%10+'0');
                   n=m/10;
               }
               if(n>0) 
               {
                  num++;
                  if(num>=MAX) {throw("out of index");}
                  for(i=num-1;i>0;i--) temp.info[i]=temp.info[i-1];
                  temp.info[0]='1';
               }
               temp.Num=num;
			   temp.info[num]=0;
               return temp;
           } 
           CHugeInt   operator + (int a) const
           {
              CHugeInt temp(a);
              return *this + temp;
           } 
           void  operator += (int a)
           {
              CHugeInt temp=*this + a;
              *this=temp;
           }
          
           friend ostream& operator <<(ostream &output,const CHugeInt &a); 
           friend CHugeInt operator +(int a,const  CHugeInt &b);
           friend CHugeInt& operator ++(CHugeInt &b);
};

CHugeInt   operator + (int a, const CHugeInt b) 
{
           return CHugeInt(a)+b;
}

CHugeInt&   operator ++(CHugeInt &b)
{
           b+=1;
		   return b;
}
ostream& operator <<(ostream &output,const CHugeInt &a) 
{
	       output<<a.info;
           return output;
} 

int main()
{
    
CHugeInt a("1234545436342424354354365289899834234235");
CHugeInt d(9999);

CHugeInt temp = CHugeInt("100000088888888") + 111112;
CHugeInt temp2 = 111112 + CHugeInt("100000088888888");

cout << "1)" << temp << endl;
cout << "2)" << temp2 << endl;
cout << "3)"<<++d << endl;
cout << "4)" << d++ << endl;
cout << "5)" << d << endl;

d+=5;
cout << "6)" << d << endl;
cout << "7)" << d + temp;

}
