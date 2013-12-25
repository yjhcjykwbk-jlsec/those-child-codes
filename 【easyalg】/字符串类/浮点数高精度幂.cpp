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

            //ÿһ�ֶ���an1��һλ��ȥ��an2��λ��ˣ���an1�ĸ�λ��ʼ

            for( i = 0;i < len2; i ++ )

            {                                             

                        //��ѡ����an1����һλ��ȥ��an2�ĸ�λ

                        for( j = 0; j < len1; j ++ )                                   

                                    //������i, jλ��ˣ��ۼӵ�����ĵ�i+jλ

                                    aResult[i+j] += an2[i]*an1[j];     

            }

            //�����ѭ��ͳһ�����λ����

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

            while(scanf(��%s%d��,szBase,&exponent)>0)

            {

                        basePointPos = -1;

                        baseDecimalDigits = 0;

                        memset( an1, 0, sizeof(an1));

                        memset( an2, 0, sizeof(an2));

                        memset( aResult, 0, sizeof(aResult));

                        len1 = strlen(szBase);

                        //����С����λ�ú�ĩβ0�ĳ��������������С��λ����ͬʱ�����ų�ĩβ0������ĳ���

                        p = strchr(szBase,��.');

                        if(p)

                        {

                                    basePointPos = p-szBase;

                                    for( i = len1 �C 1; szBase[i]==��0�� && i>basePointPos; i�C);

                                    baseDecimalDigits = i-basePointPos;

                                    len1 = i+1;

                        }

                        len2 = len1;

                        j = 0;

                        for( i = len1 �C 1;i >= 0 ; i�C)

                        {

                                    if(i==basePointPos)

                                                continue;

                                    an1[j] = szBase[i] �C ��0��;

                                    an2[j] = szBase[i] �C ��0��;

                                    aResult[j] = szBase[i] �C ��0��;//ָ��Ϊ1ʱ�Ľ��

                                    j++;

                        }

                        //ָ������1ʱ�������

                        for( i = 0; i < exponent-1; i++ )

                        {

                                    memset( aResult, 0, sizeof(aResult));

                                    multiply();

                                    for( j = MAX_LEN-1; aResult[j]==0 ; j�C );

                                    len2 = j+1;

                                    //�����Ϊ��һ�γ˷��ı�����

                                    for( j = 0; j < len2; j++ )

                                    {

                                                an2[j] = aResult[j];

                                    }

                        }

                        //��������С����Ӧ���ֵ�λ��

                        resultPointPos = baseDecimalDigits * exponent �C 1;

                        //�����������һλ�������е�λ��

                        resultEndPos = 0;

                        if(baseDecimalDigits > 0)

                        {

                                    for( i = 0; aResult[i]==0 && i<MAX_LEN; i++ );

                                    resultEndPos = i;

                        }

                        //�����������λ�������е�λ��

                        for( i = MAX_LEN-1; aResult[i]==0 && i>=0; i�C );

                        if(resultPointPos>i)

                                    resultBeginPos = resultPointPos;

                        else

                                    resultBeginPos = i;

                        for( i = resultBeginPos; i>=resultEndPos ; i�C )

                        {

                                    if( i == resultPointPos )

                                                printf(��.��);

                                    printf(��%d��, aResult[i]);

                        }

                        printf(��\n��);

            }

            return 0;

}
