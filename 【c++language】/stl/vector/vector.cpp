#include<vector>
//#include<stdlb>
#include<algorithm>
#include<iostream>
#include<fstream>
using namespace std;
fstream out("out.txt",ios::out);
struct key
{
       int i;
       int j;
       bool operator < (key b)//注意1：在这里设置的比较函数并不会被用到最后的sort函数当中 
       { 
            return i>b.i;
       }
};

       bool com(const key &a,const key &b)
       {
            if((a.i*a.i)%3000<(b.i*b.i)%3000) return 1;//注意二：a<b的顺序是递增的顺序 
            else return 0;
       }

int main()
{ 
        vector <key> v(232);
        for(int i=0;i<v.size();i++)
        {
                v[i].i=i;
        }
        sort(v.begin(),v.end(),com);//注意三：com必须是函数不是结构体 
        
        for(int i=0;i<v.size();i++)
        {
               out<<v[i].i<<" ";
        }
}
