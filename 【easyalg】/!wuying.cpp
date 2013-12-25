#include<iostream>
#include<math.h>
using namespace std;
int month[12]={31,28,31,30,31,30,31,31,30,31,30,31}; 
bool isRun(int a)
{
     if(a%100==0) {if(a%400==0) return true;}
     else if(a%4==0)return true;
     return false;
}
void f(unsigned long m)
{
     int n=24*3600;
     int days=(m/n);
     int miao=(m%n);
     int years=days/365;
     days=days%365;
     
     int sum=years/4+1;//闰年个数 (1970也是） 
     if(years>=130){ int more=(years-30)/400;int kk=((years-30)%400)/100;  sum-=(3*more+kk);}
     if(years>0)days-=sum;      //得到这一年的天数 

     bool isRunNian=false;
     if(days<0) 
     {
        years=1970+years-1;
        if(isRun(years)) {days+=366;isRunNian=true;}
        else days+=365;
      }
      else 
      {
           years=1970+years;
           if(isRun(years)) isRunNian=true;
      }
      int i=0;
      int day;
      for(i=0;i<12;i++)
      {
        day=month[i];
        if(i==1&&isRunNian) day++;
        if(days>=day) days-=day;
        else break;
      }
      int Month=i+1;
      int Date=days+1;
      int xiaoshi=miao/3600;
      int fenzhong=(miao%3600)/60;
      int miaoshu=(miao%3600)%60;
      
       cout<<years<<"-";
       if(Month<10) cout<<"0";
       cout<<Month<<"-";
       if(Date<10) cout<<"0";
       cout<<Date<<" ";
       if(xiaoshi<10) cout<<"0";
       cout<<xiaoshi<<":";
       if(fenzhong<10)cout<<"0";
       cout<<fenzhong<<":";
       if(miaoshu<10) cout<<"0";
       cout<<miaoshu<<endl;
     }
     int main()
     {
         unsigned long m;
         while(true)
         { 
         cin>>m;
         if(m<0||m>=(1<<31))break;
         f(m);
         }
        return 1;
         }

          //2000nian
          
          
      
