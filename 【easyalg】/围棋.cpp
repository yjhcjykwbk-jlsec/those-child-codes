//Χ��
#include <iostream>
using namespace std;
int n;
char Board[200][200];
void FloodFill(int i,int j)
{
if( Board[i][j] == 'B' || Board[i][j] == '.' ) {
Board[i][j] = 'Y'; //���弰�������Ϊ��Y��
FloodFill( i +1,j);
FloodFill( i-1,j);
FloodFill( i ,j + 1);
FloodFill( i ,j - 1);
}
}

int main()
{
int i,j,k;
cin >> n;
memset( Board,'W',sizeof(Board));
for( i = 1;i <= n;i ++ )
for( j = 1; j <= n; j ++ )
cin >> Board[i][j];
for( i = 1;i <= n;i ++ ) //��ɫ
for( j = 1; j <= n; j ++ )
if( Board[i][j] == 'B' )
FloodFill(i,j);
int nTotalB = 0;
for( i = 1;i <= n;i ++ ) //ͳ��
for( j = 1; j <= n; j ++ )
if( Board[i][j] == 'Y' )
nTotalB ++;
cout << nTotalB << " " << n * n - nTotalB;
return 0;
} 
