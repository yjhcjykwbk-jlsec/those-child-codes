#include<iostream>
#include<stdlib.h>
using namespace std;
class String
{
private:
        int Size;
        char c_str[100];
public:
       String()
       {
				   c_str[0]='\0';
                   Size=0;
       }
       
       String(const char *temp)
       {
                   int i,j=strlen(temp);
                   Size=j;
                   i=0;
                   while(i<=Size){c_str[i]=temp[i];i++;}
       }
       String(const String &s)
       {
		   Size=s.GetSize();
		   int i;
           for(i=0;i<=Size;i++) c_str[i]=s[i];
       }
       int GetSize() const
       {
            return Size;
       }
       const char * GetStr()
       {
            return c_str;
       }
       ////////////////////////////////////////////////////////////////////////////
       const char operator [](int i) const
       {
            if(i>Size) {cout<<"out of range!\n";   return 0;}
            else return c_str[i];
       }  
       char &operator [](int i)
       {
            if(i>Size) {cout<<"out of range!\n";   return c_str[0];}
            else return c_str[i];
       }   
       void copy(const  String &s,int k,int i,int j)//i-i+j->k
       {
            int l=i,r=k;
            while(l<i+j) 
			{
				c_str[r]=s[l];
				l++;r++;
				if(r>Size) cout<<"Out of range!\n";
			}
			if(r>=Size) c_str[r]='\0';
       }     
       void operator = (const String &s)    
       {
            Size=s.GetSize();
            copy(s,0,0,s.GetSize());        
       }    
       void operator +=(const char *s)
       {
		   int k=strlen(s);
		   int j,i=Size;
           Size+=k;
           for(j=i;j<=Size;j++) c_str[j]=s[j-i];
       }
	   void operator +=(String &s)
       {
            *this+=s.GetStr();
       }
       String  operator +( String &s) const
       {
            String temp(*this);
            temp+=s;
            return temp;
       } 
	   String  operator +(const char * s) const
       {
            String temp(*this);
            temp+=s;
            return temp;
       } 

        const char * operator()(int i,int j) const
       {
            char * temp=new char(j+1);
            int k;
			for( k=0;k<j;k++) temp[k]=(*this)[i+k];
			temp[k]='\0';
            return temp;
       }
      
       friend ostream & operator <<(ostream &t,String s)
       {
            printf("%s",s.GetStr());
            return t;
       }  
	   	   ////比较大小/////
	   bool operator >( String &s)
	   {
		    if(1==strcmp(GetStr(),s.GetStr())) return true;
			return false;
	   }
	   bool operator ==( String &s)
	   {   
		    if(0==strcmp(GetStr(),s.GetStr())) return true;
            return false;
	   }
	   bool operator <( String &s)
	   {
		    if(-1==strcmp(GetStr(),s.GetStr())) return true;
			return false;
	   }
};

String operator + (char *l,String &r)
       {
            String temp(l);
            temp+=r;
            return temp;
       } 

class MyString:public  String
{
public:
	   MyString():String(){}
       MyString(const String &s):String(s){}
       MyString(const char *s):String(s){}
	   
	   //子串（i开始j个字符）
      
	   const MyString & operator=(char *s)
	   {
		   String temp=s;
		   *this=temp;
		   return *this;
	   }
	   friend int CompareString( const void * e1, const void * e2) 
	   { 
		    MyString * s1 = (MyString * ) e1; 
			MyString * s2 = (MyString * ) e2; 
			if( * s1 < *s2 ) return -1; 
			else if( *s1 == *s2) return 0; 
			else if( *s1 > *s2 ) return 1; 
	   }
	   //friend void qort(MyStrin *s,int 
}; 


       
int main()
{
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1); 
    MyString SArray[4] = {"big","me","about","take"}; 
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3; s3 = s1 + s3; 
    cout << "2. " << s1 << endl; 
    cout << "3. " << s2 << endl; 
    cout << "4. " << s3 << endl; 
    cout << "5. " << s4 << endl; 
    cout << "6. " << s1[2] << endl; 
    s2 = s1; s1 = "ijkl-"; s1[2] = 'A' ; 
    cout << "7. " << s2 << endl; 
    cout << "8. " << s1 << endl; 
    s1 += "mnop"; 
    cout << "9. " << s1 << endl; 
    s4 = "qrst-" + s2; 
    //cout<<s4<<endl;
    cout << "10. " << s4 << endl; 
    s1 = s2 + s4 + " uvw " + "xyz"; 
    cout << "11. " << s1 << endl; 
    qsort(SArray,4,sizeof(MyString),CompareString); 
    for( int i = 0;i < 4;i ++ ) cout << SArray[i] << endl; //输出s1的下标为0的字符开始长度为4的子串 
    cout << s1(0,4) << endl; //输出s1的下标为5的字符开始长度为10的子串 
    cout << s1(5,10) << endl;
int i;
cin>>i;
	return 0;
}   
