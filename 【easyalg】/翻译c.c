#include <stdio.h> 
typedef struct{
  int nWeight; //����ƻ��������
}CApple;
int GetWeight(CApple T) { return T.nWeight;}

static int nTotalWeight=0; //����ƻ������
static GetTotalWeight()  
{  return nTotalWeight; }
int main()
{
 CApple a;
 GetWeight(a);   
 GetTotalWeight();
 GetTotalWeight(); 
 }
