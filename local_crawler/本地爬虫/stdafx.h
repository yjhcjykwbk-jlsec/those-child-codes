// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
#pragma once

// TODO: 在此处引用程序需要的其他头文件
#include<iostream>
#include<queue>
#include<string>
#include <fstream>
#include <vector>
using std::vector;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
using std::string;

#define INFINITY 9999;
#define UNVISITED 0;
#define VISITED 1;

//边
class Edge
{
public:
	int from;
	int to;
	int weight;
	Edge(int a,int b,int c){from=a;to=b;weight=c;}
	Edge(){
	from=-1;to=-1;weight=0;}
};

//图基类
class Graph
{
public:
	int numVertex;
	int numEdge;
	vector<int> Mark;
	vector<int>Indegree;

	Graph();
	
	int getVertexNum();

	bool isEdge(Edge a);
	
	~Graph(){//delete Mark;delete Indegree;
	}
};

//邻接边
	struct ListUnit
	{
		int vertex;
		int weight;
	};

//邻接边链表元素
	class Link
	{
	public:
		ListUnit element;
		Link *next;

		Link(){
			next=0;
		}
		Link(ListUnit &temp)
		{
			element=temp;
			next=0;
		}
	};
	
//邻接边链表类型
	class LLink
	{
	private:
		string info;//记录节点对应文件名称
	public:
		Link *head;

		LLink()
		{
			head=new Link;
		}
		LLink(string a)
		{
			head=new Link;
			info=a;
		}
		void setInfo(string temp)
		{
			info=temp;
		}
	};

//派生图类
	class GraphL:public Graph{
	private:
		//LLink *gralist;//边表数组
		vector<LLink> gralist;
		//const int total;//记录总数组大小

	public:

		GraphL():Graph()//:total(2000),Graph(total)
	{
			//gralist=new LLink[total];
		}
	void clearMark();//还原Mark数组
	
	Edge firstEdge(int vertex);
		
	Edge nextEdge(Edge prev);

	void deleteEdge(Edge e);

	void setEdge(int from,int to,int weight);

	bool setVertex(string info);

	void DFS(int v);
	
	void BFS(int v);
	
};


