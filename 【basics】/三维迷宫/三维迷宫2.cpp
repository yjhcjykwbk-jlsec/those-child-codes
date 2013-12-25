//三维迷宫2.cpp
//提供类的函数详细定义

# include "三维迷宫.h"

//创建大迷宫，当然了，size代表你想走的迷宫范围
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
					Matrix[i][j][k]=rand()%2;//0代表障碍，1代表顺途，（2代表走过）
					cout<<Matrix[i][j][k]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
		}
	}


//边界判断
bool Labyr::insideborder(int i,int j,int k)
{
	if(i>=Size||i<0)return false;
	else if(j>=Size||j<0)return false;
	else if(k<0||j>=Size)return false;
	else 
		return true;
}

//寻找未访问的坐标，以节点形式返回
int step[3][2][3]={1,0,0,-1,0,0,0,1,0,0,-1,0,0,0,1,0,0,-1};//代表各种走法
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
				//走到边界外了，或走过的，或障碍物
			{
				x=p.X,y=p.Y,z=p.Z;
			}
		}
	}
	//未找到，返回原坐标
	return p;
}


//走迷宫
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
    
