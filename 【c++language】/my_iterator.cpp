#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
template<class T>
class CMyostream_iterator
{
      private:
              ostream &output;
              string tag;
      public:
             CMyostream_iterator(ostream &a,string b):output(a),tag(b){}
             CMyostream_iterator(ostream &a):output(a),tag(""){}
             void operator ++(){}
             void operator =(T value)
             {
                  output<<value<<tag;
             }
             CMyostream_iterator& operator *(){return *this;}
};

main()
{
 int a[5] = {1,2,3,4,5};
 CMyostream_iterator<int> output(cout,"*");
 vector<int> v(a,a+5);
 copy(v.begin(),v.end(),output);
 int i;
 cin>>i;
}
