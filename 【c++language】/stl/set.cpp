#include <set>
#include <iostream>
#include<ostream_iterator>
using namespace std;
//using std::ostream_iterator; 
main()  {
	typedef set<double,less<double> > double_set;
	const int SIZE = 5;
	double a[SIZE] = {2.1,4.2,9.5,2.1,3.7 };
	double_set doubleSet(a,a+SIZE);
	ostream_iterator <double> output(cout," ");
	cout << "1) ";
	copy(doubleSet.begin(),doubleSet.end(),output);
	cout << endl;
}
