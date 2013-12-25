
#include<iostream>
using namespace std;
class student
{
 private:
   char name[30];
   int age;
   int number;
   int score[4];
   float averScore;
 public:
  student(char temp[],int a,int b,int *c)
 {
  strcpy(name,temp);
  age=a;number=b;
  int i;
  for(i=0;i<4;i++) {score[i]=c[i];}
  }
  float getAverageScore()
  {
   int i=0;
   float s=0;
   for(i=0;i<4;i++) {s+=score[i];}
   averScore=s/4;
   return averScore;
  }
  void putOut()
 {
  printf("%s,%d,%d,%f\n",name,age,number,getAverageScore());
 }
};

int main()
{
 char temp[40];
 gets(temp);
 char name[20];
 int a[4];
 int age,number;
 int i=0;
 while(temp[i]!=',')name[i]=temp[i++]; name[i++]=0;
 sscanf(temp+i,"%d,%d,%d,%d,%d,%d",&age,&number,&a[0],&a[1],&a[2],&a[3]);
 student g(name,age,number,a);
 g.putOut();
 return 1;
}
