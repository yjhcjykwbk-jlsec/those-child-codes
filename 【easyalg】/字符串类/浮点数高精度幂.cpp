#include <stdio.h>

#include <string.h>

#define MAX_LEN 150

unsigned an1[6];

unsigned an2[MAX_LEN];

unsigned aResult[MAX_LEN];

char szBase[7];

int exponent,len1,len2;

void multiply()

{

            int i, j;

            //每一轮都用an1的一位，去和an2各位相乘，从an1的个位开始

            for( i = 0;i < len2; i ++ )

            {                                             

                        //用选定的an1的那一位，去乘an2的各位

                        for( j = 0; j < len1; j ++ )                                   

                                    //两数第i, j位相乘，累加到结果的第i+j位

                                    aResult[i+j] += an2[i]*an1[j];     

            }

            //下面的循环统一处理进位问题

            for( i = 0; i < MAX_LEN-1; i ++ )

            {

                        if( aResult[i] >= 10 )

                        {

                                    aResult[i+1] += aResult[i] / 10;

                                    aResult[i] %= 10;

                        }

            }

}

int main()

{

            int i,j,basePointPos,baseDecimalDigits,resultPointPos,resultEndPos,resultBeginPos;

            char* p;

            while(scanf(“%s%d”,szBase,&exponent)>0)

            {

                        basePointPos = -1;

                        baseDecimalDigits = 0;

                        memset( an1, 0, sizeof(an1));

                        memset( an2, 0, sizeof(an2));

                        memset( aResult, 0, sizeof(aResult));

                        len1 = strlen(szBase);

                        //根据小数点位置和末尾0的出现来计算底数的小数位数，同时计算排除末尾0后底数的长度

                        p = strchr(szBase,’.');

                        if(p)

                        {

                                    basePointPos = p-szBase;

                                    for( i = len1 – 1; szBase[i]==’0′ && i>basePointPos; i–);

                                    baseDecimalDigits = i-basePointPos;

                                    len1 = i+1;

                        }

                        len2 = len1;

                        j = 0;

                        for( i = len1 – 1;i >= 0 ; i–)

                        {

                                    if(i==basePointPos)

                                                continue;

                                    an1[j] = szBase[i] – ‘0′;

                                    an2[j] = szBase[i] – ‘0′;

                                    aResult[j] = szBase[i] – ‘0′;//指数为1时的结果

                                    j++;

                        }

                        //指数大于1时迭代相乘

                        for( i = 0; i < exponent-1; i++ )

                        {

                                    memset( aResult, 0, sizeof(aResult));

                                    multiply();

                                    for( j = MAX_LEN-1; aResult[j]==0 ; j– );

                                    len2 = j+1;

                                    //结果作为下一次乘法的被乘数

                                    for( j = 0; j < len2; j++ )

                                    {

                                                an2[j] = aResult[j];

                                    }

                        }

                        //计算结果中小数点应出现的位置

                        resultPointPos = baseDecimalDigits * exponent – 1;

                        //计算结果的最后一位在数组中的位置

                        resultEndPos = 0;

                        if(baseDecimalDigits > 0)

                        {

                                    for( i = 0; aResult[i]==0 && i<MAX_LEN; i++ );

                                    resultEndPos = i;

                        }

                        //计算结果的最高位在数组中的位置

                        for( i = MAX_LEN-1; aResult[i]==0 && i>=0; i– );

                        if(resultPointPos>i)

                                    resultBeginPos = resultPointPos;

                        else

                                    resultBeginPos = i;

                        for( i = resultBeginPos; i>=resultEndPos ; i– )

                        {

                                    if( i == resultPointPos )

                                                printf(“.”);

                                    printf(“%d”, aResult[i]);

                        }

                        printf(“\n”);

            }

            return 0;

}
