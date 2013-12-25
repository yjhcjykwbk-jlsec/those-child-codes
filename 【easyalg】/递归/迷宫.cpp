#include <iostream> 
using namespace std;
char rect[102][102];
//返回从某点出发能否走到地点         
bool walkfrom(int Row, int Col,const int &dRow,const int &dCol) 
 {
       char a=rect[Row][Col];
	   char b=rect[dRow][dCol];
       if(a!='.'||b!='.') return false;//障碍或已经过 
       else 
       {
			rect[Row][Col]='*'; //标记
            if(Row==dRow&&Col==dCol)return true;
            if(walkfrom(Row,Col-1,dRow,dCol))return true;
            if(walkfrom(Row-1,Col,dRow,dCol))return true;
            if(walkfrom(Row,Col+1,dRow,dCol))return true;
            if(walkfrom(Row+1,Col,dRow,dCol))return true;
       }
       return false;
 }
int main()
{
    int n;
    cin>>n;
    bool *res=new bool[n];
    int i,j,k,size;
	int srow,scol;
	int drow,dcol;
    for(i=0;i<n;i++)
    {
       cin>>size;
       for(j=0;j<=size+1;j++)
          for(k=0;k<=size+1;k++)
            rect[j][k]='#';
       for(j=1;j<=size;j++)
            cin>>rect[j]+1;
       cin>>srow>>scol>>drow>>dcol;
	   if(walkfrom(srow+1,scol+1,drow+1,dcol+1)) 
		   res[i]=true;
	   else res[i]=false;
	}
	for(i=0;i<n;i++)
	{
	   if(res[i])
		cout<<"YES"<<endl;
	   else cout<<"NO"<<endl;
    }
	return 1;
}
