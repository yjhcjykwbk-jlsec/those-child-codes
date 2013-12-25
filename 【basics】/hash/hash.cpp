//hash
#define TOMB 10;
#define EXIST 1; 
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
fstream out("out.txt",ios::out); 
//开放定址策略
template <typename Key,  //键值类型
typename Func> //必须是仿函数类
class OpenAddressPolicy
{
public:
	OpenAddressPolicy();
	~OpenAddressPolicy();
	void Init(int size);  //初始化散列表大小
	void Clear();         //清空散列表
	int Count() const;    //计算当前散列表中元素个数
	bool Insert (const Key& k);  //插入键值
	bool Lookup (const Key& k);  //查找是否存在键值
	void Remove(const Key& k);
private:
	//用于开放定址策略的数据结构
	Key* m_pData;   //一个存放键值的数组
	short* m_bUsage; //一个标志对应位置是否使用的数组
	int m_nSize;    //散列表大小
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
	//将使用标志写为假
	for ( int i=0; i<m_nSize; ++i )
		m_bUsage[i]=false;
}

template <typename Key, typename Func>
int OpenAddressPolicy<Key, Func>::Count() const
{
	int count=0;
	//统计使用位置个数
	for ( int i=0; i<m_nSize; ++i )
	{
		if ( m_bUsage[i] )
			++count;
	}
	return count;
}
//当插入重复元素时候，要注意检查不能重复 
template <typename Key, typename Func>
bool OpenAddressPolicy<Key, Func>::Insert(const Key &k)
{
    if(Lookup(k)) return true; 
	int pos=Func()(k); //得到散列位置
	if ( m_bUsage[pos]==1 )//发生冲突
	{
		int i=(pos+1)%m_nSize; //冲突后一个位置
		//向后找第一个没有使用的位置
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
		//无法找到空位置
		return false;
	}
	else //没有冲突
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
	int pos=Func()(k); //得到散列位置///////////////////
	if ( m_bUsage[pos] )  //可能存在或冲突
	{
		if ( m_bUsage[pos]==1 &&m_pData[pos]==k ) //直接映射成功
			return true;
		else //可能冲突
		{
			int i=(pos+1)%m_nSize; 
			//遍历冲突位置以后
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

//溢出链策略
template <typename Key,    //键值类型
typename Func>   //必须是仿函数类
class OverflowChainPolicy
{
protected:
	//内部数据结构
	struct Node  //桶
	{
		Key m_k;      //键值
		Node* m_next; //下一个桶
	};
	struct Chain //链
	{
		Chain (bool use=false, Node* p=NULL ):m_bUsage(use), m_list(p) {}
		bool m_bUsage;  //该位是否使用标志
		Node* m_list;   //桶链
	};
	void DestroyAllNode(); //删除所有桶节点
public:
	OverflowChainPolicy();   
	~OverflowChainPolicy(); 
	void Init(int size);       //初始化散列表大小
	void Clear();              //清空散列表
	int Count() const;         //计算当前散列表中元素个数
	bool Insert (const Key& k);  //插入键值
	bool Lookup (const Key& k);  //查找是否存在键值
	void Remove(const Key& k);
private:
	//用于溢出链策略的数据结构
	Chain* m_pData; //链
	int m_nSize;    //散列表大小
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
		DestroyAllNode();  //先删除桶节点
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
		if ( m_pData[i].m_bUsage ) //存在映射
		{
			p=m_pData[i].m_list;
			if(p==NULL) exit(0);//
			//删除所有关联桶
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
		if ( m_pData[i].m_bUsage ) //存在映射
		{
			p=m_pData[i].m_list;
			//统计桶数，即映射后元素个数
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
	int pos=Func()(k);  //获得映射地址
	if ( m_pData[pos].m_bUsage ) //冲突
	{
		Node* p=new Node;
		p->m_k=k;
		p->m_next=m_pData[pos].m_list;
		m_pData[pos].m_list=p;
	}
	else //没有冲突
	{
		m_pData[pos].m_bUsage=true;
		Node* p=new Node;
		p->m_k=k;
		p->m_next=NULL;
		m_pData[pos].m_list=p;
	}
	return true; //总会成功
}

template <typename Key, typename Func>
bool OverflowChainPolicy<Key, Func>::Lookup(const Key &k)
{
	int pos=Func()(k); //获得映射位置
	if ( m_pData[pos].m_bUsage )  //存在映射
	{
		Node* p=m_pData[pos].m_list;
		//在关联桶链表中找特定键值
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
             if(p==m_pData[pos].m_list) //头结点 
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

//集合哈希表
template <typename Key,  //键值类型
typename Func, //键值类型到位置的映射仿函数类型
template< typename, typename> class ManagerPolicy > //冲突避免策略
class Hash_Set : protected ManagerPolicy<Key, Func>
{
public:
	explicit Hash_Set (int size);  //初始化散列表大小
	int Count() const;  //统计已经散列的元素个数
	void Clear();       //清空散列表
	bool Insert(const Key& k);  //插入关键值
	bool Lookup(const Key& k);  //找特定关键值是否已经映射
	void Remove(const Key& k);
protected:
	//不可访问函数
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
    void Init(int size);       //初始化散列表大小
	void Clear();              //清空散列表
	int Count() const;         //计算当前散列表中元素个数
	bool Insert (const Key& k);  //插入键值
	bool Lookup (const Key& k);  //查找是否存在键值
	void Remove (const Key& k);  //删除k 
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
 
