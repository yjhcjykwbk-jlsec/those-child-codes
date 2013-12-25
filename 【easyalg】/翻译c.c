#include <stdio.h> 
typedef struct{
  int nWeight; //单个苹果的重量
}CApple;
int GetWeight(CApple T) { return T.nWeight;}

static int nTotalWeight=0; //所有苹果总重
static GetTotalWeight()  
{  return nTotalWeight; }
int main()
{
 CApple a;
 GetWeight(a);   
 GetTotalWeight();
 GetTotalWeight(); 
 }
