// sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<process.h>
#include<time.h>
UINT uId;
using namespace std;
    HANDLE FinishSem=NULL;  
    UINT _stdcall ThreadSort(LPVOID);//排序线程入口函数
	void sort(int [],int,int);
	void swap(int [],int,int);
	void merge(int [],int,int,int);
    struct sT{
           int a,b;
           int *s;
		   HANDLE SEM;
           };
           
    int main()
    {
    	int s[1000002];
    	fstream file;
		char *fileName="input";
		file.open(fileName); 
    	file.seekg(0);
		int j=0;
		int tmp;
		int yy=0;
		while(true)
		{
			if(j>1000000) break;
			file.seekg(yy);
			if(file.read((char*) &tmp, sizeof(int))<0)  break;
			s[j++]=tmp;
			yy+=sizeof(int);
		}
    	FinishSem=CreateSemaphore(NULL,0,1,NULL);
		sT t={0,j-1,s,FinishSem};
    	HANDLE Thread=(HANDLE)::_beginthreadex
				(NULL,0,(unsigned int (__stdcall *)(void *))ThreadSort,LPVOID(&t),0,&uId);
    	WaitForSingleObject(FinishSem,INFINITE);
		fstream fileout;
		fileout.open("output.txt",ios::out);
		int i=0;
		while(i<j)
			fileout<<(s[i++])<<endl;
		file.clear();
		file.close();
		fileout.clear();
		fileout.close();
		return 1;
    }
    
    UINT _stdcall ThreadSort(LPVOID lp)
    {
		sT a= *(sT *)lp;/*需要传多个参数的时候，使用结构体*/
		int l=a.a,r=a.b;int *s=a.s;
		HANDLE SEM=a.SEM;
		if(l-r>2000)
		{
			if (r > l) {
			int o1 = s[r];
			int i = l - 1;
			int j = r;
			while (true) {
				while (s[++i] < o1);
				while (j > 0)
					if (s[--j] <= o1)
						break; 
				if (i >= j)
					break;
				swap(s,i, j);}
			swap(s,i, right);

			sT t1={l,i-1,s,SEM};
			sT t2={i+1,r,s,SEM};
			HANDLE LFinishSem=CreateSemaphore(NULL,0,1,NULL); 
			HANDLE LThread=(HANDLE)::_beginthreadex(NULL,0,ThreadSort,(LPVOID)&t1,0,&uId);
			HANDLE RFinishSem=CreateSemaphore(NULL,0,1,NULL);  
			HANDLE RThread=(HANDLE)::_beginthreadex(NULL,0,ThreadSort,(LPVOID)&t2,0,&uId);
			WaitForSingleObject(LFinishSem,INFINITE);
			WaitForSingleObject(RFinishSem,INFINITE);
		}
		else{
		sort(s,l,r);
		}
	   ReleaseSemaphore(SEM,1,NULL);
	   
       return 0;
	}
	void sort(int *s, int left, int right){
    if (right > left) {
		int o1 = s[right];
		int i = left - 1;
		int j = right;
		while (true) {
			while (s[++i] < o1);
			while (j > 0)
				if (s[--j] <= o1)
					break; 
			if (i >= j)
				break;
			swap(s,i, j);
		}
		swap(s,i, right);
		sort(s,left, i - 1);
		sort(s,i + 1, right);}
    }
    void swap(int* s,int loc1, int loc2) {
	    int tmp = s[loc1];
	    s[loc1]=s[loc2];
	    s[loc2]=tmp;
    }
    void merge(int* s, int a, int middle, int b)
    {
        int* temp = new int[b - a + 1];
        int p1 = a, p2 = middle + 1,p3=0;
        while (p1 <= middle && p2 <= b)
        {
            if (s[p2] > s[p1]) temp[p3++] = s[p1++];
            else temp[p3++] = s[p2++];
        }
        while (p1 <= middle) temp[p3++] = s[p1++];
        while (p2 <= b) temp[p3++] = s[p2++];
        for (p3 = a; p3 <= b; p3++) s[p3] = temp[p3-a];
		free(temp);
    }