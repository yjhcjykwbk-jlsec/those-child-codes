#include <iostream> 
using namespace std;
const int  MAX=52; 
//�������ܼӿ飬ȥ���߽��жϣ�
int rect[MAX][MAX]; //���� 
//-1�����߹� 
//���ش�ĳ��������ߵ��ĸ�����
int walkfrom(int Row, int Col);
void go(int i,int j, int &num,int &maxnum);
int main()
{
   int row,col;
   cin>>row>>col;
   int i=0,j=0;;
   for (i=0;i<MAX;i++)
      for(j=0;j<MAX;j++)
         rect[i][j]=-1; 
   for (i=1;i<=row;i++)
      for(j=1;j<=col;j++)
         cin>>rect[i][j]; 
   int num=0,maxnum=0;
   go(row,col,num,maxnum);
   cout<<num<<endl;
   cout<<maxnum<<endl;
   return 1;
} 
           
int walkfrom(int Row, int Col) 
 {
       int a=rect[Row][Col];
       int res=0; 
       if(a==-1) return 0;//�¾����ķ������
       else 
       {//�� 
            res+=1;//���� 
			rect[Row][Col]=-1; 
            if(!(a&1)) res+=walkfrom(Row,Col-1);
            if(!((a>>1)&1)){res+=walkfrom(Row-1,Col);}
            if(!((a>>2)&1)){res+=walkfrom(Row,Col+1);}
            if(!((a>>3)&1))res+=walkfrom(Row+1,Col);
       }
       return res;
 }
            
void go(int i,int j, int &num,int &maxnum)
{
       num=0,maxnum=0;
       int  a=1,b=1,c; 
       for(a=1;a<=i;a++)
       for(b=1;b<=j;b++)
       {
           if(rect[a][b]!=-1) 
           {
                  num++;
				  c=walkfrom(a,b);
				  if(c>maxnum) {maxnum=c;}
           }
       }
}                                  

