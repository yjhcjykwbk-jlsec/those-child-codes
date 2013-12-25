#include <iostream>
#include <cstdlib.h>
using namespace std;
#define MAXN 10000
int a[MAXN];
void swap(int l,int r){
	if(l!=r) {
		int tmp=a[l];
		a[l]=a[r];a[r]=tmp;
	}
}
void qsort(int l,int r){
	if(l>=r) return;
	srand(time(NULL));
	int s=rand()%(r-l+1)+l;
	if(s!=l) swap(s,l);//
	int lp=l+1,rp=r;
	while(lp<=rp){
		while(lp<=r&&a[lp]<=a[l]) lp++;
		while(rp>=l&&a[rp]>a[l]) rp++;
		swap(lp,rp);
	}
	swap(l,rp);
	qsort(l,rp);
	qsort(rp+1,r);
}
int main(){
	a={9,8,7,6,5,4,3,2};
	qsort(0,7);
	rep0(i,8) cout<<a[i]<<" ";
	return 0;
}
