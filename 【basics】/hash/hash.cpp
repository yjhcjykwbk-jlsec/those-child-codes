//hash
#define TOMB 10;
#define EXIST 1; 
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
fstream out("out.txt",ios::out); 
//���Ŷ�ַ����
template <typename Key,  //��ֵ����
typename Func> //�����Ƿº�����
class OpenAddressPolicy
{
public:
	OpenAddressPolicy();
	~OpenAddressPolicy();
	void Init(int size);  //��ʼ��ɢ�б��С
	void Clear();         //���ɢ�б�
	int Count() const;    //���㵱ǰɢ�б���Ԫ�ظ���
	bool Insert (const Key& k);  //�����ֵ
	bool Lookup (const Key& k);  //�����Ƿ���ڼ�ֵ
	void Remove(const Key& k);
private:
	//���ڿ��Ŷ�ַ���Ե����ݽṹ
	Key* m_pData;   //һ����ż�ֵ������
	short* m_bUsage; //һ����־��Ӧλ���Ƿ�ʹ�õ�����
	int m_nSize;    //ɢ�б��С
};

template <typename Key, typename Func>
OpenAddressPolicy<Key, Func>::OpenAddressPolicy()
{
	m_pData=NULL;
	m_bUsage=NULL;
	m_nSize=0;
}

template <typename Key, typename Func>
OpenAddressPolicy<Key, Func>::~OpenAddressPolicy()
{
	if ( m_pData!=NULL )
	{
		delete[] m_pData;
		m_pData=NULL;
	}
	if ( m_bUsage!=NULL )
	{
		delete[] m_bUsage;
		m_bUsage=NULL;
	}
	m_nSize=0;
}

template <typename Key, typename Func>
void OpenAddressPolicy<Key, Func>::Init(int size)
{
	m_pData=new Key[size];
	m_bUsage=new short[size];
	m_nSize=size;
	Clear();
}

template <typename Key, typename Func>
void OpenAddressPolicy<Key, Func>::Clear()
{	
	//��ʹ�ñ�־дΪ��
	for ( int i=0; i<m_nSize; ++i )
		m_bUsage[i]=false;
}

template <typename Key, typename Func>
int OpenAddressPolicy<Key, Func>::Count() const
{
	int count=0;
	//ͳ��ʹ��λ�ø���
	for ( int i=0; i<m_nSize; ++i )
	{
		if ( m_bUsage[i] )
			++count;
	}
	return count;
}
//�������ظ�Ԫ��ʱ��Ҫע���鲻���ظ� 
template <typename Key, typename Func>
bool OpenAddressPolicy<Key, Func>::Insert(const Key &k)
{
    if(Lookup(k)) return true; 
	int pos=Func()(k); //�õ�ɢ��λ��
	if ( m_bUsage[pos]==1 )//������ͻ
	{
		int i=(pos+1)%m_nSize; //��ͻ��һ��λ��
		//����ҵ�һ��û��ʹ�õ�λ��
		while ( i!=pos )
		{
			if ( m_bUsage[i]!=1 )
			{
				m_bUsage[i]=EXIST;
				m_pData[i]=k;
				return true;
			}
			i=((1+i)%m_nSize);
		};
		//�޷��ҵ���λ��
		return false;
	}
	else //û�г�ͻ
	{
		m_bUsage[pos]=EXIST;
		m_pData[pos]=k;
	}
	return true;
}
template <typename Key, typename Func>
void OpenAddressPolicy<Key, Func>::Remove(const Key &k)
{
     int pos=Func()(k);
     while(m_bUsage[pos]) 
     {
         if(m_pData[pos]==k) {m_bUsage[pos]=TOMB;return;}
         pos=(pos+1)%m_nSize;
     }
}                                              

template <typename Key, typename Func>
bool OpenAddressPolicy<Key, Func>::Lookup(const Key &k)
{
	int pos=Func()(k); //�õ�ɢ��λ��///////////////////
	if ( m_bUsage[pos] )  //���ܴ��ڻ��ͻ
	{
		if ( m_bUsage[pos]==1 &&m_pData[pos]==k ) //ֱ��ӳ��ɹ�
			return true;
		else //���ܳ�ͻ
		{
			int i=(pos+1)%m_nSize; 
			//������ͻλ���Ժ�
			while ( i!=pos )
			{
                if ( !m_bUsage[i] ) return false;
				if ( 1 == m_bUsage[i])
				{
					if ( m_pData[i]==k )
						return true;
				}
			    i=(i+1)%m_nSize;
             } 
			 return false;
		}
	}
	return false;
}



////////////////////////////////////////////////////////////////////////////////////////////////

//���������
template <typename Key,    //��ֵ����
typename Func>   //�����Ƿº�����
class OverflowChainPolicy
{
protected:
	//�ڲ����ݽṹ
	struct Node  //Ͱ
	{
		Key m_k;      //��ֵ
		Node* m_next; //��һ��Ͱ
	};
	struct Chain //��
	{
		Chain (bool use=false, Node* p=NULL ):m_bUsage(use), m_list(p) {}
		bool m_bUsage;  //��λ�Ƿ�ʹ�ñ�־
		Node* m_list;   //Ͱ��
	};
	void DestroyAllNode(); //ɾ������Ͱ�ڵ�
public:
	OverflowChainPolicy();   
	~OverflowChainPolicy(); 
	void Init(int size);       //��ʼ��ɢ�б��С
	void Clear();              //���ɢ�б�
	int Count() const;         //���㵱ǰɢ�б���Ԫ�ظ���
	bool Insert (const Key& k);  //�����ֵ
	bool Lookup (const Key& k);  //�����Ƿ���ڼ�ֵ
	void Remove(const Key& k);
private:
	//������������Ե����ݽṹ
	Chain* m_pData; //��
	int m_nSize;    //ɢ�б��С
};

template <typename Key, typename Func>
OverflowChainPolicy<Key, Func>::OverflowChainPolicy()
{
	m_pData=NULL;
	m_nSize=0;
}

template <typename Key, typename Func>
OverflowChainPolicy<Key, Func>::~OverflowChainPolicy()
{
	if ( m_pData!=NULL )
	{
		DestroyAllNode();  //��ɾ��Ͱ�ڵ�
		delete[] m_pData;
		m_pData=NULL;
		m_nSize=0;
	}
}

template <typename Key, typename Func>
void OverflowChainPolicy<Key, Func>::DestroyAllNode()
{
	Node* p=NULL;
	Node* q=NULL;
	for ( int i=0; i<m_nSize; ++i )
	{
		if ( m_pData[i].m_bUsage ) //����ӳ��
		{
			p=m_pData[i].m_list;
			if(p==NULL) exit(0);//
			//ɾ�����й���Ͱ
			while ( p->m_next!=NULL )
			{
				q=p->m_next;
				p->m_next=q->m_next;
				delete q;
			}
			delete p;
			m_pData[i].m_list=NULL;
			m_pData[i].m_bUsage=false;
		}
	}
}

template <typename Key, typename Func>
void OverflowChainPolicy<Key, Func>::Init(int size)
{
	m_pData=new Chain[size];
	m_nSize=size;
}

template <typename Key, typename Func>
void OverflowChainPolicy<Key, Func>::Clear()
{
	DestroyAllNode();
}

template <typename Key, typename Func>
int OverflowChainPolicy<Key, Func>::Count() const
{
	int count=0;
	Node* p=NULL;
	for ( int i=0; i<m_nSize; ++i )
	{
		if ( m_pData[i].m_bUsage ) //����ӳ��
		{
			p=m_pData[i].m_list;
			//ͳ��Ͱ������ӳ���Ԫ�ظ���
			while ( p!=NULL )
			{
				++count;
				p=p->m_next;
			}
		}
	}
	return count;
}

template <typename Key, typename Func>
bool OverflowChainPolicy<Key, Func>::Insert(const Key& k)
{
	int pos=Func()(k);  //���ӳ���ַ
	if ( m_pData[pos].m_bUsage ) //��ͻ
	{
		Node* p=new Node;
		p->m_k=k;
		p->m_next=m_pData[pos].m_list;
		m_pData[pos].m_list=p;
	}
	else //û�г�ͻ
	{
		m_pData[pos].m_bUsage=true;
		Node* p=new Node;
		p->m_k=k;
		p->m_next=NULL;
		m_pData[pos].m_list=p;
	}
	return true; //�ܻ�ɹ�
}

template <typename Key, typename Func>
bool OverflowChainPolicy<Key, Func>::Lookup(const Key &k)
{
	int pos=Func()(k); //���ӳ��λ��
	if ( m_pData[pos].m_bUsage )  //����ӳ��
	{
		Node* p=m_pData[pos].m_list;
		//�ڹ���Ͱ���������ض���ֵ
		while ( p!=NULL )
		{
			if ( p->m_k==k )
			{
				return true;
			}
			p=p->m_next;
		}
	}
	return false;
}

template <typename Key, typename Func>
void OverflowChainPolicy<Key, Func>::Remove(const Key &k)
{
     int pos=Func()(k);
     if( m_pData[pos].m_bUsage )
     {
        Node *p=m_pData[pos].m_list,* q=p;
        while(true)
        {
             while(p!=NULL&&p->m_k!=k)
             {
                  q=p;
                  p=p->m_next;
             } 
             if(p==NULL) return;     
             if(p==m_pData[pos].m_list) //ͷ��� 
             {
                  m_pData[pos].m_list=p->m_next;
                  delete p;
                  p=m_pData[pos].m_list;
             }                       
             else 
             {
                  q->m_next=p->m_next;
                  delete p;
                  p=q->m_next;
             }
        }
       if(m_pData[pos].m_list==NULL) m_pData[pos].m_bUsage=false;
     }   
}                                              

//���Ϲ�ϣ��
template <typename Key,  //��ֵ����
typename Func, //��ֵ���͵�λ�õ�ӳ��º�������
template< typename, typename> class ManagerPolicy > //��ͻ�������
class Hash_Set : protected ManagerPolicy<Key, Func>
{
public:
	explicit Hash_Set (int size);  //��ʼ��ɢ�б��С
	int Count() const;  //ͳ���Ѿ�ɢ�е�Ԫ�ظ���
	void Clear();       //���ɢ�б�
	bool Insert(const Key& k);  //����ؼ�ֵ
	bool Lookup(const Key& k);  //���ض��ؼ�ֵ�Ƿ��Ѿ�ӳ��
	void Remove(const Key& k);
protected:
	//���ɷ��ʺ���
	Hash_Set (const Hash_Set& other);
	Hash_Set& operator= (const Hash_Set& rbs);
};

template <typename Key,typename Func,template< typename, typename> class ManagerPolicy >
Hash_Set<Key, Func, ManagerPolicy>::Hash_Set(int size)
{
	ManagerPolicy<Key, Func>::Init(size);
}

template <typename Key,typename Func,template< typename, typename> class ManagerPolicy >
int Hash_Set<Key, Func, ManagerPolicy>::Count() const
{
	return ManagerPolicy<Key, Func>::Count();
}

template <typename Key,typename Func,template< typename, typename> class ManagerPolicy >
void Hash_Set<Key, Func, ManagerPolicy>::Clear()
{
	ManagerPolicy<Key, Func>::Clear();
}

template <typename Key,typename Func,template< typename, typename> class ManagerPolicy >
bool Hash_Set<Key, Func, ManagerPolicy>::Insert(const Key &k)
{
	return ManagerPolicy<Key, Func>::Insert(k);
}

template <typename Key,typename Func,template< typename, typename> class ManagerPolicy >
bool Hash_Set<Key, Func, ManagerPolicy>::Lookup(const Key& k)
{
	return ManagerPolicy<Key, Func>::Lookup(k);
}

template <typename Key,typename Func,template< typename, typename> class ManagerPolicy >
void Hash_Set<Key, Func, ManagerPolicy>::Remove(const Key& k)
{
	ManagerPolicy<Key, Func>::Remove(k); 
}

template<int N>
class Cmp
{
public:
	int operator() (int k)
	{
		return k%N;
	}
};
template <int N>
class strCmp
{
public:
	int operator() (const string &k)
	{
        int res=0;
        for(int i=0;i<k.length();i++)
        {
             res+=(i+1)*abs(k[i]-'a');
        }   
		return res%N;
	}
};
/*
    void Init(int size);       //��ʼ��ɢ�б��С
	void Clear();              //���ɢ�б�
	int Count() const;         //���㵱ǰɢ�б���Ԫ�ظ���
	bool Insert (const Key& k);  //�����ֵ
	bool Lookup (const Key& k);  //�����Ƿ���ڼ�ֵ
	void Remove (const Key& k);  //ɾ��k 
	*/
int main()
{
    /*OverflowChainPolicy<int,Cmp<2> > q;
    q.Init(2);
    q.Insert(46);
    q.Insert(34);
    out<<q.Lookup(45)<<endl;//
    q.Insert(34);
    q.Insert(34);
    out<<q.Lookup(34)<<endl;//
    q.Remove(34);               
    out<<q.Lookup(34)<<endl;//
    out<<q.Lookup(46)<<endl;//
    */
    OpenAddressPolicy<string,strCmp<20> > q;
    q.Init(20);
    string a="46";
    q.Insert(a);
    q.Insert("34");
    out<<q.Lookup("45")<<endl;//
    q.Insert("34");
    q.Insert("34");
    out<<q.Lookup("34")<<endl;//
    q.Remove("34");  
    out<<q.Lookup("34")<<endl;//
    }
 
