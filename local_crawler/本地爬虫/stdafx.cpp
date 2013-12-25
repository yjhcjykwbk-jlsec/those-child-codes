// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ��������.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


//���ຯ��
Graph::Graph()
		{
			numVertex=0;
			numEdge=0;
			//Mark=new int[total];
			//Indegree=new int[total];
			//for(int i=0;i<total;i++)
			//{
				//Mark[i]=UNVISITED;
				//Indegree[i]=0;
			//}
		}

int Graph::getVertexNum()
		{
			return numVertex;
		}

bool Graph::isEdge(Edge a)
		{
			return (a.to>=0);
		}

//����ͼ�ĳ�Ա����

//��ԭMark����
void GraphL::clearMark()
	{
		for(int i=0;i<numVertex;i++)
		{
			Mark[i]=0;//��־δ����
		}
	}
//��һ��
Edge GraphL::firstEdge(int vertex)
		{
			Edge temp;
			Link *pointer=gralist[vertex].head->next;
			if(pointer!=NULL)
			{
				temp.from=vertex;
				temp.to=pointer->element.vertex;
				temp.weight=pointer->element.weight;
			}
			return temp;
		}

//��һ��
Edge GraphL::nextEdge(Edge prev)
		{
			int vertex=prev.from;
			Edge temp;
			Link *pointer=gralist[vertex].head->next;
			while(pointer->element.vertex!=prev.to&&pointer->next!=NULL)
			{
				pointer=pointer->next;
			}
			pointer=pointer->next;
			if(pointer!=NULL)
			{
				temp.from=vertex;
				temp.to=pointer->element.vertex;
				temp.weight=temp.weight;
			}
			return temp;
		}

//��ӱ�
void GraphL::setEdge(int from,int to,int weight)
		{
			if(from>=0&&from<numVertex)
			{
				Link *insertpointer=gralist[from].head;
				while(insertpointer->next!=NULL)
				{
					insertpointer=insertpointer->next;
				}
				insertpointer=gralist[from].head;
				if(to>=0&&to<numVertex&&weight>0&&weight<9999)
				{
					Link *newlink=new Link;
					Link *pointer=insertpointer->next;

					newlink->element.vertex=to;
					newlink->element.weight=weight;

					while(pointer!=NULL)
					{
						if(pointer->element.vertex<to)
						{
							insertpointer=pointer;
							pointer=pointer->next;
							
						}
						else break;
					}

					newlink->next=insertpointer->next;
					insertpointer->next=newlink;

					Indegree[to]++;		//���
					numEdge++;

					pointer=NULL;
				}
				insertpointer=NULL;
			}		
		}

void GraphL::deleteEdge(Edge e)
{
			int vertex=e.from;
			Link *prepointer=gralist[vertex].head;
			Link *pointer=gralist[vertex].head->next;
			while(pointer->element.vertex!=e.to)
			{
				prepointer=pointer;
				pointer=pointer->next;
			}
			prepointer->next=pointer->next;
			
			Indegree[e.to]--;	//��ȼ���
			delete  pointer;
			numEdge--;

			pointer=prepointer=NULL;
}

bool GraphL::setVertex(string info)
{
	//if(numVertex>=total) return false;//��������
	numVertex++;
	LLink newVertex(info);
	gralist.push_back(newVertex);
	Mark.push_back(0);					//�����¶���
	Indegree.push_back(0);

	//gralist[numVertex-1].setInfo(info);
	return true;
}

//�������
void GraphL::BFS(int v)
	{
		cout<<"BFS:"<<endl;
		using std::queue;
		queue<int>Q;
		Q.push(v);
		Mark[v]=1;
		cout<<"visited:"<<v<<endl;

		while(!Q.empty())
		{
			int a=Q.front();
			Q.pop();
			
			for(Edge e=firstEdge(a);isEdge(e);e=nextEdge(e))
			{
				if(Mark[e.to]==0)
				{
					Mark[e.to]=1;
					Q.push(e.to);
					cout<<"visited:"<<e.to<<endl;
				}
			}
		}
		for(int i=0;i<numVertex;i++)
			Mark[i]=0;

	}

//�����������
void GraphL::DFS(int v)
	{
		Mark[v]=1;		//VISITED
		cout<<"visited:"<<v<<endl;
		for(Edge e=firstEdge(v);isEdge(e);e=nextEdge(e))
		{
			if(Mark[e.to]==0)//UNVISITED
			{
				DFS(e.to);
			}
			
		}
	}