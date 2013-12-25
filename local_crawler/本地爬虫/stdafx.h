// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
#pragma once

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
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

//��
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

//ͼ����
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

//�ڽӱ�
	struct ListUnit
	{
		int vertex;
		int weight;
	};

//�ڽӱ�����Ԫ��
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
	
//�ڽӱ���������
	class LLink
	{
	private:
		string info;//��¼�ڵ��Ӧ�ļ�����
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

//����ͼ��
	class GraphL:public Graph{
	private:
		//LLink *gralist;//�߱�����
		vector<LLink> gralist;
		//const int total;//��¼�������С

	public:

		GraphL():Graph()//:total(2000),Graph(total)
	{
			//gralist=new LLink[total];
		}
	void clearMark();//��ԭMark����
	
	Edge firstEdge(int vertex);
		
	Edge nextEdge(Edge prev);

	void deleteEdge(Edge e);

	void setEdge(int from,int to,int weight);

	bool setVertex(string info);

	void DFS(int v);
	
	void BFS(int v);
	
};


