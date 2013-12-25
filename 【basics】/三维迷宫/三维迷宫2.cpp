//��ά�Թ�2.cpp
//�ṩ��ĺ�����ϸ����

# include "��ά�Թ�.h"

//�������Թ�����Ȼ�ˣ�size���������ߵ��Թ���Χ
Labyr::Labyr(int size)
	{
        srand(time(0));
		assert(size<=MaxSize);
		Size=size;
		for(int i=0;i<MaxSize;i++)
		{
			for(int j=0;j<MaxSize;j++)
			{
				for(int k=0;k<size;k++)
				{
					Matrix[i][j][k]=rand()%2;//0�����ϰ���1����˳;����2�����߹���
					cout<<Matrix[i][j][k]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
		}
	}


//�߽��ж�
bool Labyr::insideborder(int i,int j,int k)
{
	if(i>=Size||i<0)return false;
	else if(j>=Size||j<0)return false;
	else if(k<0||j>=Size)return false;
	else 
		return true;
}

//Ѱ��δ���ʵ����꣬�Խڵ���ʽ����
int step[3][2][3]={1,0,0,-1,0,0,0,1,0,0,-1,0,0,0,1,0,0,-1};//��������߷�
Node  Labyr::search(Node p)
{
	Node temp;
	int x=p.X;
	int y=p.Y;
	int z=p.Z;
	for(int i=0;i<3;i++)
	{	
		for(int j=0;j<2;j++)
		{
			x+=step[i][j][0];
			y+=step[i][j][1];
			z+=step[i][j][2];
			if(insideborder(x,y,z)&&Matrix[x][y][z]==1)
			{
				cout<<"\n"<<x<<"  "<<y<<"  "<<z;
				temp.X=x,temp.Y=y,temp.Z=z;
				return temp;
			}
			else 
				//�ߵ��߽����ˣ����߹��ģ����ϰ���
			{
				x=p.X,y=p.Y,z=p.Z;
			}
		}
	}
	//δ�ҵ�������ԭ����
	return p;
}


//���Թ�
bool Labyr::find()
{	

	cout<<"\nplease enter the position you want to go\n";
	int i,j,k;
	cin>>i>>j>>k;
	while(!insideborder(i,j,k)||Matrix[i][j][k]!=1)
	{
		if(!insideborder(i,j,k)) cout<<"\nout of border!";
		if(Matrix[i][j][k]!=1) cout<<"\nthe position you entered can not be get through!its value is "<<Matrix[i][j][k];
		cout<<"\nplease enter again:";
		cin>>i>>j>>k;
	}
	Node door={i,j,k};
	Node p1={0,0,0};
	Node p2,temp;
	int a,b,c;
	while(!equal(p1,door))
	{
		a=p1.X;
		b=p1.Y;
		c=p1.Z;
		Matrix[a][b][c]=2;
		p2=search(p1);
		if(!equal(p1,p2))
		{
			temp=p1;
			S.push(temp);
			p1=p2;
		}
		else
		{
			if(!S.isEmpty())
			{
				p1=S.pop();
			}
			else return false;
		}
	}
	return true;			
}
    
