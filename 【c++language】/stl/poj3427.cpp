#include<iostream>
#include<set>
#include<map>
#include<algorithm>
#include<iterator>
using namespace std;
typedef multiset<int ,less<int > > list;
typedef map<int,list *,less<int> > dirlist;


//      merge   
void    merge(dirlist &a,int id1,int id2)
{
        multiset<int>::iterator p=a[id2]->begin();
        while (p!=a[id2]->end())
        {
                 (*a[id1]).insert(*p);
                  ++p;
        }
        a[id2]->clear();
}
//      s×ª³ÉÊý×Ö 
int     getv(char *s)
{
        int temp=0;
        int i=0;
        while(s[i]==' ') i++;
        while(s[i]!='\0'&&s[i]!=' ') 
        {
                  temp*=10;
                  temp+=(s[i]-'0');
                  i++;
                  }
        return temp;
}
//      unique
void    unique(list &a)
{
        multiset<int>::iterator p=a.begin();
        multiset<int>::iterator q=p;
        int last=*p;
        p++;
        while(p!=a.end()){
        while(p!=a.end()&&*p!=last)
        {
                  last=*p;
                  q=p;
                  p++;
        }
        if(p!=a.end()){q=p;p++;a.erase(q);}
        }
}        
int     main()
{
        dirlist cc;
        ostream_iterator<int> output(cout," ");
        multiset<int>::iterator tp;
        int n,i=0,c,d;
        char temp[100],op[8],op1[8],op2[8];
        gets(temp);
        sscanf(temp,"%d",&n);
        while(i<n)
        {
            gets(temp);
            if(temp[0]=='n'||temp[0]=='o'||temp[0]=='u')
            {
                 sscanf(temp,"%s %s",op,op1);    
                 c=getv(op1);
                 if(temp[0]=='n')
                 {          
                     //delete cc[c];   
                     cc[c]=new list();
                 }
                 else if(temp[0]=='o')
                 {
                      if(cc[c]!=NULL) copy(cc[c]->begin(),cc[c]->end(),output);
                      else cout<<endl;
                 }
                 else
                 unique(*cc[c]);
            }     
            else 
            {
                 sscanf(temp,"%s %s %s",op,op1,op2);
                 c=getv(op1);
                 d=getv(op2);
                 if(temp[0]=='a')
                 (*cc[c]).insert(d);
                 else if(temp[0]=='m')
                 merge(cc,c,d);
            }
            i++;    
        }   
        return 1;
}
