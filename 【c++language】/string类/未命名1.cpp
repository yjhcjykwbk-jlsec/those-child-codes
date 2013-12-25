#include <iostream>
using namespace std;
template <class D>
class Node {
public:	
	D data;
	Node * next;
};
template<class D>
class CLinkList 
{
	private:
		Node<D> * pHead;
	public:
		CLinkList();
		void AppendNode( D data);
		void PrintList();
};
template<class D>
CLinkList<D>::CLinkList() 
{
	pHead = new Node<D>;
	pHead->next = NULL;
}
template<class D>
void CLinkList<D>::AppendNode(D data)
{
    Node<D> *p=this->pHead;
    while(p->next!=NULL)
    {
       p=p->next;
    }
    p->next=new Node<D>();
    p->next->data=data;
    p->next->next=NULL;
    p=NULL;
}
template<class D>
void CLinkList<D>::PrintList()
{
    Node<D> *pointer=this->pHead;
    while(pointer->next!=NULL)
    {
       cout<<pointer->next->data<<" ";
       pointer=pointer->next;
    }
    pointer=NULL;
}


main()
{
	CLinkList<int> l;
	int i;
	for(i = 0;i < 4;i ++)
		l.AppendNode(i);
	l.PrintList();
	cout << endl;
	for( i = 9;i < 12;i ++)
		l.AppendNode(i);
	l.PrintList();
	int j;cin>>j;
}
