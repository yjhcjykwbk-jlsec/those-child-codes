#include<deque>
#include<algorithm>
#include<fstream>
using namespace std;
fstream out("out.txt",ios::out);
int main()
{
    deque<string> s;
    //���뷽ʽ����ͷ���� 
    s.push_front("sfdf");
    s.push_back("gf");
    deque<string>::iterator p;
    //���ʷ�ʽ 
    for(p=s.begin();p!=s.end();p++)
    {
        out<<*p<<endl;
    }
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl;
    //ɾ��Ԫ��
    s.pop_front();
    out<<"after erased:"<<endl;
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl; 
    
    s[1]="dsdsdsfsdfsd";//�޷�����Ԫ�� ֻ���滻Ԫ�� 
    out<<"after added:"<<endl;
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl; 
    
    s[0]="dsdsdsfsdfsd";//�޷�����Ԫ�� ֻ���滻Ԫ��
    out<<"after added:"<<endl;
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl; 
    
    //���
    out<<"after clear:"<<endl;
    s.clear();
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl;  
    
    //sort
    out<<"after sort:"<<endl;
    s.push_front("zjgfhjgdf");
    s.push_back("ddseas");
    s.push_back("aaw");
    sort(s.begin(),s.end());
    for(int i=0;i<s.size();i++)
    out<<s[i]<<endl;
} 
