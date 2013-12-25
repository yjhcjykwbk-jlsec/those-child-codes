#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;



int rBorn[5]= {2 , 3 , 4 , 1 , 0};
int bBorn[5]= {3 , 0 , 1 , 2 , 4};
char nameOfWorriers[5][10]={"dragon" , "renzhe", "iceman", "lion", "wolf"};
char nameOfColor[2][10]={"red" , "blue"};
int iRedBorn=0;
int iBlueBorn=0;
int l[5],d[5];
int M,N,T;

int bHeadQuarter = 0, rHeadQuarter = 0;
class Worriers{
public:
	int numOfWorriers;
	int life;
	int damage;
	int color;
	int everKilled;
	int kindOfWorriers;
	int nSteps;
	int tempLife;
	virtual void attack(Worriers*,int ,int){}		
	virtual void fightBack(Worriers* ){}
	virtual void damaged(int){}
	virtual void move(){}
	virtual void putFlag(){}
	virtual void special(int city=0,int t=0){}
	virtual int isDeath(int ,int,Worriers *){return 0;}
	void getAward( Worriers * a,int t);
	void getElements(int,int);
	
	Worriers(int l=0,int d=0,int c=0){
		life=l;
		damage=d;
		color=c;
		everKilled=0;
		kindOfWorriers=0;
		nSteps = 0;
		tempLife = 0;
	}
	void operator =(Worriers a){
		life = a.life;
		damage = a.damage;
		color = a.color;
		everKilled = a.everKilled;
		kindOfWorriers = a.kindOfWorriers;
		numOfWorriers = a.numOfWorriers;
		nSteps = a.nSteps;
		tempLife = a.tempLife;
	}
};
class City{
public:
	int nCity;
	int flag;
	int setFlag;
	Worriers *w1;
	Worriers *w2;
	int elements;
	int constant;
	City(){
		w1 = new Worriers;
		w2 = new Worriers;
		nCity = 0;
		flag = 0;
		elements = 0;
		setFlag = 0;
		constant = 0;
	}
};
City *c;


class Iceman:public Worriers{
public:
	Iceman(int l,int d,int c):Worriers(l,d,c){}
	virtual void attack(Worriers* a , int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		//cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" attacked "
			<<nameOfColor[a->color-1]<<" "<<nameOfWorriers[a->kindOfWorriers]<<" "<<a->numOfWorriers<<" in city "<<city<<endl;
		a->damaged(this->damage);
		if(a->isDeath(city , t , this)==0){
			fightBack(a,city,t);
			isDeath(city,t,a);
		}
		

	}
	virtual void fightBack(Worriers* a,int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[a->color-1]<<" "<<nameOfWorriers[a->kindOfWorriers]<<" "<<a->numOfWorriers<<" fought back against "
			<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" in city "<<city<<endl;
		this->damaged(0.5*a->damage);
	}
	virtual void damaged(int power){
		this->life -= power;
	}
	virtual void move(){
		this->nSteps++;
		special();
	}
	virtual int isDeath(int city,int t,Worriers *a){
		if(this->life <= 0){
			cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
			cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers
				<<" was killed in city "<<city<<endl;
			a->everKilled++;
			a->getAward(a,t);
			if(a->kindOfWorriers==0)a->special(city,t);
			if(c[city].elements>0)	a->getElements(city,t);
			if(c[city].setFlag==1&&a->color==1&&c[city].constant == 1){
				c[city].flag = 1;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[0]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 2 && a->color == 2&&c[city].constant == 1){
				c[city].flag = 2;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[1]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 0)c[city].setFlag = a->color;
			else if(c[city].setFlag!=a->color)	c[city].setFlag = 0;
			delete this;

			return 1;
		}
		else return 0;
	}
	virtual void special(){
		if(this->nSteps%2 == 0){
			this->life-=10;
			this->damage+=20;
			if(this->life<=0)this->life=1;
		}
	}

};
class Dragon:public Worriers{
public:
	Dragon(int l,int d,int c):Worriers(l,d,c){}
	virtual void attack(Worriers* a , int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" attacked "
			<<nameOfColor[a->color-1]<<" "<<nameOfWorriers[a->kindOfWorriers]<<" "<<a->numOfWorriers<<" in city "<<city<<endl;
		a->damaged(this->damage);
		if(a->isDeath(city , t , this)==0){
			fightBack(a,city,t);
			isDeath(city,t,a);
			special(city,t);
		}
			
	}
	virtual void fightBack(Worriers* a,int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[a->color-1]<<" "<<nameOfWorriers[a->kindOfWorriers]<<" "<<a->numOfWorriers<<" fought back against "
			<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" in city "<<city<<endl;
		this->damaged(0.5*a->damage);
	}
	virtual void damaged(int power){
		this->life -= power;
	}
	virtual void move(){
		this->nSteps++;

	}
	virtual int isDeath(int city,int t,Worriers *a){
		if(this->life <= 0){
			cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
			cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers
				<<" was killed in city "<<city<<endl;
			a->everKilled++;
			a->getAward(a,t);
			if(a->kindOfWorriers==0)a->special(city,t);
			if(c[city].elements>0)	a->getElements(city,t);
			if(c[city].setFlag==1&&a->color==1&&c[city].constant == 1){
				c[city].flag = 1;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[0]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 2 && a->color == 2&&c[city].constant == 1){
				c[city].flag = 2;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[1]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 0)c[city].setFlag = a->color;
			else if(c[city].setFlag!=a->color)	c[city].setFlag = 0;
			delete this;
			return 1;
		}
		else return 0;
	}
	virtual void special(int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers
			<<" yielded in city "<<city<<endl;
	}
};
class Wolf:public Worriers{
public:
	Wolf(int l,int d,int c):Worriers(l,d,c){}
	virtual void attack(Worriers* a , int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" attacked "
			<<nameOfColor[a->color-1]<<" "<<nameOfWorriers[a->kindOfWorriers]<<" "<<a->numOfWorriers<<" in city "<<city<<endl;
		a->damaged(this->damage);
		if(a->life<=0&&(this->everKilled>0&&this->everKilled%2==0)) special();
		if(a->isDeath(city , t , this)==0){
			fightBack(a,city,t);
			isDeath(city,t,a);
		}
		else{
			if(everKilled>0 && everKilled %2 == 0){
				this->special();
			}
		}
	}
	virtual void fightBack(Worriers* a,int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[a->color-1]<<" "<<nameOfWorriers[a->kindOfWorriers]<<" "<<a->numOfWorriers<<" fought back against "
			<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" in city "<<city<<endl;
		this->damaged(0.5*a->damage);
	}
	virtual void damaged(int power){
		this->life -= power;
	}
	virtual void move(){
		this->nSteps++;
	}
	virtual int isDeath(int city,int t,Worriers *a){
		if(this->life <= 0){
			cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
			cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers
				<<" was killed in city "<<city<<endl;
			a->everKilled++;
			a->getAward(a,t);
			if(a->kindOfWorriers==0)a->special(city,t);
			if(c[city].elements>0)	a->getElements(city,t);
			if(c[city].setFlag==1&&a->color==1&&c[city].constant == 1){
				c[city].flag = 1;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[0]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 2 && a->color == 2&&c[city].constant == 1){
				c[city].flag = 2;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[1]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 0)c[city].setFlag = a->color;
			else if(c[city].setFlag!=a->color)	c[city].setFlag = 0;
			delete this;
			return 1;
		}
		else return 0;
	}
	virtual void special(){
		this->life *= 2;
		this->damage *= 2;
	}
};
class Lion:public Worriers{
public:
	Lion(int l,int d,int c):Worriers(l,d,c){}
	virtual void attack(Worriers* a , int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" attacked "
			<<nameOfColor[a->color-1]<<" "<<nameOfWorriers[a->kindOfWorriers]<<" "<<a->numOfWorriers<<" in city "<<city<<endl;
		int temp = this->life;
		a->damaged(this->damage);
		if(a->isDeath(city , t , this)==0){
			fightBack(a,city,t);
			isDeath(city,t,a);
		}
		
	}
	virtual void fightBack(Worriers* a,int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[a->color-1]<<" "<<nameOfWorriers[a->kindOfWorriers]<<" "<<a->numOfWorriers<<" fought back against "
			<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" in city "<<city<<endl;
		this->damaged(0.5*a->damage);
	}
	virtual void damaged(int power){
		this->tempLife = this->life;
		this->life -= power;
	}
	virtual void move(){
		this->nSteps++;
	}
	virtual int isDeath(int city,int t,Worriers *a){
		if(this->life <= 0){
			cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
			cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers
				<<" was killed in city "<<city<<endl;
			a->everKilled++;
			a->getAward(a,t);
			this->special(a,this->tempLife);
			if(a->kindOfWorriers==0)a->special(city,t);
			if(c[city].elements>0)	a->getElements(city,t);
			if(c[city].setFlag==1&&a->color==1&&c[city].constant == 1){
				c[city].flag = 1;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[0]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 2 && a->color == 2&&c[city].constant == 1){
				c[city].flag = 2;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[1]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 0)c[city].setFlag = a->color;
			else if(c[city].setFlag!=a->color)	c[city].setFlag = 0;
			delete this;
			return 1;
		}
		else return 0;
	}
	void special(Worriers *a, int temp){
		a->life+=temp;
	}
};
class Renzhe:public Worriers{
public:
	Renzhe(int l,int d,int c):Worriers(l,d,c){}
	virtual void attack(Worriers* a , int city , int t){
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" attacked "
			<<nameOfColor[a->color-1]<<" "<<nameOfWorriers[a->kindOfWorriers]<<" "<<a->numOfWorriers<<" in city "<<city<<endl;
		a->damaged(this->damage);
		if(a->isDeath(city , t , this)==0){
			fightBack(a,city,t);
			isDeath(city,t,a);
		}
		
	}
	virtual void damaged(int power){
		this->life -= power;
	}
	virtual void fightBack(Worriers* a,int city,int i){}

	virtual void move(){
		this->nSteps++;
	}
	virtual int isDeath(int city,int t,Worriers *a){
		if(this->life <= 0){
			cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
			cout<<nameOfColor[this->color-1]<<" "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers
				<<" was killed in city "<<city<<endl;
			a->everKilled++;
			a->getAward(a,t);
			if(a->kindOfWorriers==0)a->special(city,t);
			if(c[city].elements>0)	a->getElements(city,t);
			if(c[city].setFlag==1&&a->color==1&&c[city].constant == 1){
				c[city].flag = 1;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[0]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 2 && a->color == 2&&c[city].constant == 1){
				c[city].flag = 2;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<nameOfColor[1]<<" "<<"flag raised in city "<<city<<endl;
			}
			else if(c[city].setFlag == 0)c[city].setFlag = a->color;
			else if(c[city].setFlag!=a->color)	c[city].setFlag = 0;
			delete this;
			return 1;
		}
		else return 0;
	}
};


//移动函数
void redMove(int n){
	c[n].w1->move();
	switch(c[n].w1->kindOfWorriers){
	case 0:c[n+1].w1 = new Dragon(l[0],d[0],1);break;
	case 1:c[n+1].w1 = new Renzhe(l[1],d[1],1);break;
	case 2:c[n+1].w1 = new Iceman(l[2],d[2],1);break;
	case 3:c[n+1].w1 = new Lion(l[3],d[3],1);break;
	case 4:c[n+1].w1 = new Wolf(l[4],d[4],1);break;
	}
	(*c[n+1].w1) = (*c[n].w1);
	delete c[n].w1;c[n].w1=NULL;
}
void blueMove(int n){
	c[n].w2->move();
	switch(c[n].w2->kindOfWorriers){
	case 0:c[n-1].w2 = new Dragon(l[0],d[0],2);break;
	case 1:c[n-1].w2 = new Renzhe(l[1],d[1],2);break;
	case 2:c[n-1].w2 = new Iceman(l[2],d[2],2);break;
	case 3:c[n-1].w2 = new Lion(l[3],d[3],2);break;
	case 4:c[n-1].w2 = new Wolf(l[4],d[4],2);break;
	}
	(*c[n-1].w2) = (*c[n].w2);
	delete c[n].w2;c[n].w2=NULL;
}


int main()
{
	
	int i, t,x=0;
	int everPut1=0,everPut2=0;

	Worriers *temp1,*temp2;
	temp1 = new Worriers;
	temp2 = new Worriers;

	cin>>M>>N>>T;
	for( i = 0 ; i < 5 ; i ++)cin >> l[i];
	for( i = 0 ; i < 5 ; i ++)cin >> d[i];

	c = new City [N+2];
	for(i = 0 ; i <= N+1 ; i++) c[i].nCity = i;
	c[0].elements = M;
	c[N+1].elements = M;
	for( t = 0 ; t <= T ; t += 10){
		if( t % 60 == 0){
			if(c[0].elements >= l[rBorn[iRedBorn%5]]){
				switch(rBorn[iRedBorn%5]){
				case 0:c[0].w1 = new Dragon(l[rBorn[iRedBorn%5]],d[rBorn[iRedBorn%5]],1);c[0].w1->kindOfWorriers=0;break;
				case 1:c[0].w1 = new Renzhe(l[rBorn[iRedBorn%5]],d[rBorn[iRedBorn%5]],1);c[0].w1->kindOfWorriers=1;break;
				case 2:c[0].w1 = new Iceman(l[rBorn[iRedBorn%5]],d[rBorn[iRedBorn%5]],1);c[0].w1->kindOfWorriers=2;break;
				case 3:c[0].w1 = new Lion(l[rBorn[iRedBorn%5]],d[rBorn[iRedBorn%5]],1);c[0].w1->kindOfWorriers=3;break;
				case 4:c[0].w1 = new Wolf(l[rBorn[iRedBorn%5]],d[rBorn[iRedBorn%5]],1);c[0].w1->kindOfWorriers=4;break;
				}
				c[0].elements -= l[rBorn[iRedBorn%5]];
				iRedBorn ++;
				c[0].w1->numOfWorriers = iRedBorn;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<"red "<<nameOfWorriers[c[0].w1->kindOfWorriers]<<" "<<c[0].w1->numOfWorriers<<" born"<<endl;
			}
			if(c[N+1].elements >= l[bBorn[iBlueBorn%5]]){
				switch(bBorn[iBlueBorn%5]){
				case 0:c[N+1].w2 = new Dragon(l[bBorn[iBlueBorn%5]],d[bBorn[iBlueBorn%5]],2);c[N+1].w2->kindOfWorriers=0;break;
				case 1:c[N+1].w2 = new Renzhe(l[bBorn[iBlueBorn%5]]	,d[bBorn[iBlueBorn%5]],2);c[N+1].w2->kindOfWorriers=1;break;
				case 2:c[N+1].w2 = new Iceman(l[bBorn[iBlueBorn%5]],d[bBorn[iBlueBorn%5]],2);c[N+1].w2->kindOfWorriers=2;break;
				case 3:c[N+1].w2 = new Lion(l[bBorn[iBlueBorn%5]],d[bBorn[iBlueBorn%5]],2);c[N+1].w2->kindOfWorriers=3;break;
				case 4:c[N+1].w2 = new Wolf(l[bBorn[iBlueBorn%5]],d[bBorn[iBlueBorn%5]],2);c[N+1].w2->kindOfWorriers=4;break;
				}
				c[N+1].elements -= l[bBorn[iBlueBorn%5]];
				iBlueBorn ++;
				c[N+1].w2->numOfWorriers = iBlueBorn;
				
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<"blue "<<nameOfWorriers[c[N+1].w2->kindOfWorriers]<<" "<<c[N+1].w2->numOfWorriers<<" born"<<endl;
			}
		}

//先按顺序输出将会移动的
		if(t % 60 == 10){
			if(c[1].w2!=NULL&&c[1].w2 ->life>0 ){
				switch(c[1].w2->kindOfWorriers){
				case 0:temp2 = new Dragon(l[0],d[0],2);break;
				case 1:temp2 = new Renzhe(l[1],d[1],2);break;
				case 2:temp2 = new Iceman(l[2],d[2],2);break;
				case 3:temp2 = new Lion(l[3],d[3],2);break;
				case 4:temp2 = new Wolf(l[4],d[4],2);break;
				}
				(*temp2) = (* c[1].w2);
				everPut2=0;
			}

			if(c[N].w1!=NULL&&&c[N].w1 ->life>0){
				switch(c[N].w1->kindOfWorriers){
					case 0:temp1 = new Dragon(l[0],d[0],1);break;
					case 1:temp1 = new Renzhe(l[1],d[1],1);break;
					case 2:temp1 = new Iceman(l[2],d[2],1);break;
					case 3:temp1 = new Lion(l[3],d[3],1);break;
					case 4:temp1 = new Wolf(l[4],d[4],1);break;
				}
				(*temp1) = (* c[N].w1);
				everPut1=0;

			}
			if(temp2->life>0&&everPut2==0){
				everPut2=1;
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<"blue "<<nameOfWorriers[temp2->kindOfWorriers]<<" "<<temp2->numOfWorriers<<" reached red headquarter"<<endl;
			}
			if(c[0].w1!=NULL&&c[0].w1->life>0&&c[0].w1!=NULL){
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<"red "<<nameOfWorriers[c[0].w1->kindOfWorriers]<<" "<<c[0].w1->numOfWorriers<<" marched to city 1"<<endl;
			}
			for(i = 1 ; i <= N ; i++){
				if(c[i-1].w1!=NULL && c[i-1].w1->life!=0 && i-1 != 0){
					cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
					cout<<"red "<<nameOfWorriers[c[i-1].w1->kindOfWorriers]<<" "<<c[i-1].w1->numOfWorriers<<" marched to city "<<i<<endl;
				}
				if(c[i + 1].w2 !=NULL &&c[i+1].w2->life!=0 && i+1 != N+1){
					cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
					cout<<"blue "<<nameOfWorriers[c[i+1].w2->kindOfWorriers]<<" "<<c[i+1].w2->numOfWorriers<<" marched to city "<<i<<endl;
				}
			}
			if(c[N+1].w2!=NULL&&c[N+1].w2 ->life>0&&c[N+1].w2!=NULL){
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<<"blue "<<nameOfWorriers[c[N+1].w2->kindOfWorriers]<<" "<<c[N+1].w2->numOfWorriers<<" marched to city "<<N<<endl;
			}
				if(temp1->life>0&&everPut1==0){
					everPut1=1;
					cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
					cout<<"red "<<nameOfWorriers[temp1->kindOfWorriers]<<" "<<temp1->numOfWorriers<<" reached blue headquarter"<<endl;
				}
//判定能否赢
			if(c[0].w2!=NULL&&c[0].w2->life>0&&c[1].w2!=NULL&&c[1].w2->life>0){
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<< "red headquarter was taken"<<endl;
				x=1;
			}
			else if(c[N+1].w1!=NULL&&c[N+1].w1->life>0&&c[N].w1!=NULL&&c[N].w1->life>0){
				cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
				cout<< "blue headquarter was taken"<<endl;
				x=1;
			}
			if(x==1)break;



//全体进行移动
			for(i = 0 ; i < N+2 ; i++){
				if(c[i].w2!=NULL&&c[i].w2 ->life>0 && i != 0) blueMove(i);
			}
			for(i = N+1 ; i >= 0 ;i--){
				if(c[i].w1!=NULL&&c[i].w1 ->life>0 && i != N+1) redMove(i);
			}
			
		}
//增加生命元
		if(t % 60 == 20){
			for(i = 1 ; i < N + 1 ; i ++ )	c[i].elements += 10;
		}	
//取生命元
		if(t % 60 == 30){
			for(i = 1 ; i <= N ; i++){
				if(c[i].elements > 0 ){
					if((c[i].w1!=NULL&&c[i].w1->life>0) && (c[i].w2==NULL||c[i].w2->life <= 0)){
						c[i].w1->getElements(i,t);
					}
					else if((c[i].w2!=NULL&&c[i].w2->life>0) && (c[i].w1==NULL||c[i].w1->life <= 0)){
						c[i].w2->getElements(i,t);
					}
				}
			}
		}
//战斗
		if(t % 60 == 40){
			for( i = 1 ; i <= N ; i ++){
				if(c[i].w1!=NULL&&c[i].w2!=NULL&&c[i].w1->life > 0 && c[i].w2->life > 0){
					if(c[i].flag == 1 || (c[i].flag!=2 && i % 2 == 1)){
						c[i].w1->attack(c[i].w2,i,t);					
					}
					else{
						if(c[i].w1!=NULL&&c[i].w2!=NULL&&c[i].w1->life>0&&c[i].w2->life>0){
							c[i].w2->attack(c[i].w1,i,t);

						}
					}
					if(c[i].w1!=NULL&&c[i].w1->life<=0)c[i].w1=NULL;
					if(c[i].w2!=NULL&&c[i].w2->life<=0)c[i].w2=NULL;
					if(c[i].w1!=NULL&&c[i].w2!=NULL){
						c[i].constant = 0;	
					}
					else c[i].constant = 1;
				}
			}
		}


	}

	return 0;
}
void Worriers::getAward( Worriers * a,int t){
		if(this->color == 1 && c[0].elements >= 10){
			c[0].elements -= 10;
			this->life += 10;
		}
		else if(this -> color == 2 && c[N+1].elements >= 10){
			c[N+1].elements -= 10;
			this->life += 10;
		}
}
void Worriers::getElements(int city,int t){
	if(this->color == 1){
		c[0].elements += c[city].elements;
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout << "red "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" earned "<<c[city].elements<<" elements for his headquarter"<<endl;
        c[city].elements = 0;
	}
	else if(this->color == 2){
		c[N+1].elements += c[city].elements;
		cout<<setfill('0')<<setw(3)<<t/60<<":"<<setw(2)<<t%60<<" ";
		cout << "blue "<<nameOfWorriers[this->kindOfWorriers]<<" "<<this->numOfWorriers<<" earned "<<c[city].elements<<" elements for his headquarter"<<endl;
		c[city].elements = 0;
	}
}
