//��С��������� 
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
fstream out("out.txt",ios::out);
#define max 999;
template<int num> 
struct stGraph
{
    int s;
    int t;
    short G[num][num];//��ǰȡֵ
    short (*M)[num];//���ȡֵ
    short R[num][num];//ʣ������
    short (*C)[num];//���� 
    short T[num][num];//��������֮��ľ���
    //��ʼ�� 
    void init()
    {
        s=0,t=num-1;
        int i,j;
        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
                G[i][j]=0; 
                if(M[i][j]>0){R[i][j]=M[i][j];T[i][j]=C[i][j];}
                else {R[i][j]=0;T[i][j]=max;}
            }
        }
    }
    //��������ͼ 
    void play()
    {
        int i,j;
        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
                out<<G[i][j]<<" ";//
            }
            out<<endl;
        }
        out<<endl;
    }
    //������·�� 
    bool findnearestpath(int (*before)[num])
    {
        int i,j,k;
        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
                before[i][j]=i;
                if(R[i][j]>0) T[i][j]=C[i][j];
                else T[i][j]=max;
            }
        }

        for(k=0;k<num;k++)
        {
            for(i=0;i<num;i++)
            {
                for(j=0;j<num;j++)
                { 
                    if(T[i][j]>T[i][k]+T[k][j]&&(T[i][k]<999&&T[k][j]<999))
                    {
                        T[i][j]=T[i][k]+T[k][j];
                        before[i][j]=before[k][j];/////�ؼ��Ե�һ�� 
                    }   
                }
            }
        }
        if(T[s][t]>=999) return false;
        return true;
    }	 
    //����	 
    int expand(int (*before)[num])
    {
        int j=t,i=before[s][t];
        int x=max;
        while(true)
        {
            if(R[i][j]<x) x=R[i][j];
            if(i==s) break;
            j=i;
            i=before[s][j];
        }
        j=t;i=before[s][t];
        while(true)
        {
            if(M[i][j]>0)
            {
                G[i][j]+=x;
                R[i][j]-=x;
                R[j][i]+=x;//////�������� 
            }
            else 
            {
                G[j][i]-=x;
                R[i][j]-=x;
                R[j][i]+=x;
            }
            if(i==s) break;
            else {j=i;i=before[s][j];}
        }
        return x;
    }

    void maxflow()
    {
        int d[num][num];
        init();
        while(true)
        {
            if(findnearestpath(d))
                expand(d);
            else break; 
        }
        //��С����
        int total=0; 
        for(int i=0;i<num;i++)
        {
            total+=(C[0][i]*G[0][i]);
        }
        out<<total<<endl;
    }


};


int main()
{
    stGraph<4> st;
    short data[4][4] = {
        {0,2,1,0},
        {0,0,3,1},
        {0,0,0,2},
        {0,0,0,0}
    }; 
    short cost[4][4]={
        {0,1,3,0},
        {-1,0,1,3},
        {-3,-1,-3,1},
        {0,0,0,0}	 
    };				 
    st.M=data;
    st.C=cost; 
    st.init();
    st.maxflow();
    st.play();
}


