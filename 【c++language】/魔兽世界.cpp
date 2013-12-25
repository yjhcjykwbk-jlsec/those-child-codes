      #include <iostream>
      #include <vector>
      #include <string>
      #include <map>

      using std::vector;
      using std::map;
      using std::cin;
      using std::cout;
      using std::string;
      using std::ostream;
      using std::endl;

      const bool RED=false;
      const bool BLUE=true;
      const short NEUTRAL=3;
      const string COLOR[2]={"red","blue"};

      class CTime
      {
      private:
      	int mm;
      	int hhh;
      public:
      	CTime():mm(0),hhh(0) {	}

      	void reset()
      	{
      		mm=0;
      		hhh=0;
      		return;
      	}

      	void nextphase()
      	{
      		++mm;
      		if(mm==6)
      		{
      			++hhh;
      			mm=0;
      		}
      		return;
      	}

      	bool operator > (int T)
      	{
      		return hhh*60+mm*10>T;
      	}

      	friend ostream & operator << (ostream & os,CTime x)
      	{
      		if(x.hhh<10)
      			os << "00" << x.hhh << ':' << x.mm << "0 ";
      		else if(x.hhh<100)
      			os << '0' << x.hhh << ':' << x.mm << "0 ";
      		else
      			os << x.hhh << ':' << x.mm << "0 ";
      		return os;
      	}
      };

      enum WorriorEnum{_Dragon,_Renzhe,_Iceman,_Lion,_Wolf};

      struct MonProperty
      {
      	unsigned short HPset[5];
      	unsigned short ATKset[5];
      }gMonProperty;

      CTime gTime;

      class CWorrior
      {
      protected:
      	short HP;
      	short ATK;
      	short inWitchCity;
      public:
      	static short totalCityNum;
      	const unsigned int bornnum;
      	const string monType;
      	const bool side;
      	CWorrior(short initialHP,short initialATK,bool color,short num,const string & montype,int totalcitynum):
      	  HP(initialHP),ATK(initialATK),side(color),bornnum(num),monType(montype)
      	{
      		if(color==RED)
      			inWitchCity=0;
      		else
      			inWitchCity=totalcitynum+1;
      		cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " born" << endl;
      	}

      	virtual void move()
      	{
      		if(side==RED)
      		{
      			++inWitchCity;
      			if(inWitchCity==totalCityNum+1)
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " reached blue headquarter" << endl;
      			else
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " marched to city " << inWitchCity << endl;
      		}
      		else
      		{
      			--inWitchCity;
      			if(inWitchCity==0)
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " reached red headquarter" << endl;
      			else
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " marched to city " << inWitchCity << endl;
      		}
      		return;
      	}

      	virtual void attack(CWorrior *enemy,int n)
      	{
      		cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " attacked " << COLOR[enemy->side] << ' '
      			 << enemy->monType << ' '<< enemy->bornnum << " in city "<< n << endl;
      		enemy->hurted(ATK);
      		return;
      	}

      	virtual void strikeback(CWorrior *enemy,int n)
      	{
      		cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " fight back against " << COLOR[enemy->side]
      			 << ' '<< enemy->monType << ' '<< enemy->bornnum << " in city "<< n << endl;
      		enemy->hurted(ATK/2);
      		return;
      	}

      	virtual void hurted(short damage)
      	{
      		HP-=damage;
      		return;
      	}

      	bool ifalive()
      	{
      		if(HP>0)
      			return true;
      		else
      			return false;
      	}

      	virtual void afterbattle(CWorrior *enemy)
      	{
      		if(!ifalive())
      			cout << gTime << COLOR[side] << ' ' << monType << ' '<< bornnum <<" was killed in city "<< inWitchCity << endl;
      		return;
      	}

      	virtual void lastAffair(CWorrior *enemy)
      	{
      		return;
      	}

      	virtual void getHP(int HPgot)
      	{
      		HP+=HPgot;
      		return;
      	}

      };

      short CWorrior::totalCityNum=0;

      class CDragon:public CWorrior
      {
      private:
      	bool FirstAttack;
      	void yield()
      	{
      		cout << gTime << COLOR[side] << " dragon " << bornnum << " yielded in city " << inWitchCity << endl;
      		return;
      	}
      public:
      	CDragon(MonProperty setting,bool color,unsigned int num,const string & montype,int totalcitynum):
      	  CWorrior(setting.HPset[_Dragon],setting.ATKset[_Dragon],color,num,montype,totalcitynum),FirstAttack(false) {	}

      	void attack(CWorrior *enemy,int n)
      	{
      		cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " attacked " << COLOR[enemy->side] << ' '
      			 << enemy->monType << ' '<< enemy->bornnum << " in city "<< n << endl;
      		FirstAttack=true;
      		enemy->hurted(ATK);
      		return;
      	}

      	void lastAffair(CWorrior *enemy)
      	{
      		if(ifalive()&&FirstAttack)
      			yield();
      		FirstAttack=false;
      		return;
      	}

      };

      class CIceman:public CWorrior
      {
      private:
      	short steps;
      public:
      	CIceman(MonProperty setting,bool color,unsigned int num,const string & montype,int totalcitynum):
      	  CWorrior(setting.HPset[_Iceman],setting.ATKset[_Iceman],color,num,montype,totalcitynum),steps(0) {	}

      	void move()
      	{
      		if(steps==1)
      		{
      			steps=0;
      			ATK+=20;
      			HP=(HP-10)>0?(HP-10):1;
      		}
      		else
      			++steps;
      		if(side==RED)
      		{
      			++inWitchCity;
      			if(inWitchCity==totalCityNum+1)
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " reached blue headquarter" << endl;
      			else
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " marched to city " << inWitchCity << endl;
      		}
      		else
      		{
      			--inWitchCity;
      			if(inWitchCity==0)
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " reached red headquarter" << endl;
      			else
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " marched to city " << inWitchCity << endl;
      		}
      		return;
      	}
      };

      class CLion:public CWorrior
      {
      private:
      	int HPleft;
      public:
      	CLion(MonProperty setting,bool color,unsigned int num,const string & montype,int totalcitynum):
      	  CWorrior(setting.HPset[_Lion],setting.ATKset[_Lion],color,num,montype,totalcitynum),HPleft(setting.HPset[_Lion]) {	}

      	void lastAffair(CWorrior *enemy)
      	{
      		if(!ifalive())
      			enemy->getHP(HPleft);
      		return;
      	}

      	void hurted(short damage)
      	{
      		HP-=damage;
      		if(HP>0)
      			HPleft=HP;
      		return;
      	}

      	void getHP(int HPgot)
      	{
      		HP+=HPgot;
      		HPleft=HP;
      		return;
      	}
      };

      class CRenzhe:public CWorrior
      {
      public:
      	CRenzhe(MonProperty setting,bool color,unsigned int num,const string & montype,int totalcitynum):
      	  CWorrior(setting.HPset[_Renzhe],setting.ATKset[_Renzhe],color,num,montype,totalcitynum) {	}
      	
      	void strikeback(CWorrior *enemy,int n)
      	{
      		return;
      	}
      };

      class CWolf:public CWorrior
      {
      private:
      	short kills;
      public:
      	CWolf(MonProperty setting,bool color,unsigned int num,const string & montype,int totalcitynum):
      	  CWorrior(setting.HPset[_Wolf],setting.ATKset[_Wolf],color,num,montype,totalcitynum),kills(0) {	}

      	void attack(CWorrior *enemy,int n)
      	{
      		cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " attacked " << COLOR[enemy->side] << ' '
      			 << enemy->monType << ' '<< enemy->bornnum << " in city "<< n << endl;
      		enemy->hurted(ATK);
      		if(!enemy->ifalive())
      		{
      			if(kills==1)
      			{
      				HP*=2;
      				ATK*=2;
      				kills=0;
      			}
      			else
      				++kills;
      		}
      		return;
      	}
      };

      class Myless 
      {
      public:
      	bool operator()(const CWorrior *a, const CWorrior *b)
      	{
      		if(a==NULL)
      			return true;
      		else if(b==NULL)
      			return false;
      		else
      			return a->bornnum<b->bornnum;
      	}
      };
      class CCity;

      class CHeadquarter
      {
      private:
      	unsigned int LifeEle;
      	bool Color;
      	unsigned int Population;
      	unsigned short CityNum;
      	const MonProperty Setting;
      public:
      	CHeadquarter(unsigned int lifeele,bool color,MonProperty data,unsigned short citynum):
      	  LifeEle(lifeele),Color(color),Setting(data),CityNum(citynum),Population(0) {	}
      	
      	CWorrior *creatMonster();


      	void wardMonster(CWorrior * mon)
      	{
      		if(LifeEle>=10&&(mon->side==Color))
      		{
      			mon->getHP(10);
      			LifeEle-=10;
      		}
      		return;
      	}

      	friend void getElements(const CWorrior *,CCity *,CHeadquarter &,CHeadquarter &);
      };

      CWorrior * CHeadquarter::creatMonster()
      {
      	switch(Color)
      	{
      	case RED:
      		switch((Population+1)%5)
      		{
      		case 1:
      			if(LifeEle<Setting.HPset[_Iceman])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Iceman];
      				++Population;
      				return new CIceman(Setting,Color,Population,"iceman",CityNum);
      			}
      		case 2:
      			if(LifeEle<Setting.HPset[_Lion])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Lion];
      				++Population;
      				return new CLion(Setting,Color,Population,"lion",CityNum);
      			}
      		case 3:
      			if(LifeEle<Setting.HPset[_Wolf])	
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Wolf];
      				++Population;
      				return new CWolf(Setting,Color,Population,"wolf",CityNum);
      			}
      		case 4:
      			if(LifeEle<Setting.HPset[_Renzhe])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Renzhe];
      				++Population;
      				return new CRenzhe(Setting,Color,Population,"renzhe",CityNum);
      			}
      		case 0:
      			if(LifeEle<Setting.HPset[_Dragon])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Dragon];
      				++Population;
      				return new CDragon(Setting,Color,Population,"dragon",CityNum);
      			}
      		}
      	case BLUE:
      		switch((Population+1)%5)
      		{
      		case 1:
      			if(LifeEle<Setting.HPset[_Lion])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Lion];
      				++Population;
      				return new CLion(Setting,Color,Population,"lion",CityNum);
      			}			
      		case 2:
      			if(LifeEle<Setting.HPset[_Dragon])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Dragon];
      				++Population;
      				return new CDragon(Setting,Color,Population,"dragon",CityNum);
      			}			
      		case 3:
      			if(LifeEle<Setting.HPset[_Renzhe])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Renzhe];
      				++Population;
      				return new CRenzhe(Setting,Color,Population,"renzhe",CityNum);
      			}
      		case 4:
      			if(LifeEle<Setting.HPset[_Iceman])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Iceman];
      				++Population;
      				return new CIceman(Setting,Color,Population,"iceman",CityNum);
      			}
      		case 0:
      			if(LifeEle<Setting.HPset[_Wolf])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_Wolf];
      				++Population;
      				return new CWolf(Setting,Color,Population,"wolf",CityNum);
      			}
      		}
      	}
      	return NULL;
      }

      class CCity
      {
      private:
      	short num;
      	int elements;
      	int flag;
      	int semiflag;
      	int promote;
      	CWorrior *mon[2];
      	bool judgeATKorder()
      	{
      		if(flag==RED)
      			return RED;
      		else if(flag==NEUTRAL&&num%2==1)
      			return RED;
      		else
      			return BLUE;
      	}
      public:
      	CCity(unsigned short n):
      	  num(n),elements(0),flag(NEUTRAL),semiflag(NEUTRAL),promote(0)
      	{
      		mon[0]=NULL;
      		mon[1]=NULL;
      	}
      	
      	CWorrior *getMon(bool color)
      	{
      		return mon[color];
      	}

      	void creatElements()
      	{
      		elements+=10;
      		return;
      	}

      	void activateBattle(CHeadquarter & redhead,CHeadquarter & bluehead)
      	{
      		if(mon[RED]!=NULL&&mon[BLUE]!=NULL)
      		{
      			bool first=judgeATKorder();
      			bool second=!first;
      			mon[first]->attack(mon[second],num);
      			if(mon[second]->ifalive()==false)
      			{
      				mon[RED]->afterbattle(mon[BLUE]);
      				mon[BLUE]->afterbattle(mon[RED]);
      				redhead.wardMonster(mon[first]);
      				bluehead.wardMonster(mon[first]);
      				mon[first]->lastAffair(mon[second]);
      				mon[second]->lastAffair(mon[first]);
      				getElements(mon[first],this,redhead,bluehead);
      				if((int)first==semiflag||semiflag==NEUTRAL)
      				{
      					++promote;
      					semiflag=first;
      					if(promote>=2)
      					{
      						flag=first;
      						cout << gTime << COLOR[first] << " flag raised in city " << num << endl;
      					}
      				}
      				else if((int)second==semiflag||semiflag==NEUTRAL)
      				{
      					promote=1;
      					semiflag=first;
      				}
      				mon[second]=NULL;
      				return;
      			}
      			mon[second]->strikeback(mon[first],num);
      			if(mon[first]->ifalive()==false)
      			{
      				mon[RED]->afterbattle(mon[BLUE]);
      				mon[BLUE]->afterbattle(mon[RED]);
      				redhead.wardMonster(mon[second]);
      				bluehead.wardMonster(mon[second]);
      				mon[first]->lastAffair(mon[second]);
      				mon[second]->lastAffair(mon[first]);
      				getElements(mon[second],this,redhead,bluehead);
      				if((int)second==semiflag||semiflag==NEUTRAL)
      				{
      					++promote;
      					semiflag=second;
      					if(promote>=2)
      					{
      						flag=second;
      						cout << gTime << COLOR[second] << " flag raised in city " << num << endl;
      					}
      				}
      				else if((int)first==semiflag||semiflag==NEUTRAL)
      				{
      					promote=1;
      					semiflag=second;
      				}
      				mon[first]=NULL;
      				return;
      			}
      			mon[RED]->afterbattle(mon[BLUE]);
      			mon[BLUE]->afterbattle(mon[RED]);
      			mon[first]->lastAffair(mon[second]);
      			mon[second]->lastAffair(mon[first]);
      			semiflag=NEUTRAL;
      			promote=0;
      		}
      		return;
      	}

      	CWorrior *MonsterOut(bool color)
      	{
      		CWorrior *temp=mon[color];
      		mon[color]=NULL;
      		return temp;
      	}

      	void MonsterIn(CWorrior * m)
      	{
      		if(m!=NULL)
      		{
      			mon[m->side]=m;
      			m->move();
      		}
      		return;
      	}

      	friend void getElements(const CWorrior *,CCity *,CHeadquarter &,CHeadquarter &);
      };

      void getElements(const CWorrior *mon,CCity * city,CHeadquarter & redside,CHeadquarter &blueside)
      {
      	int temp=city->elements;
      	switch(mon->side)
      	{
      	case RED:
      		redside.LifeEle+=temp;
      		city->elements=0;
      		break;
      	case BLUE:
      		blueside.LifeEle+=temp;
      		city->elements=0;
      		break;
      	}
      	cout << gTime << COLOR[mon->side] << ' '<< mon->monType << ' '<< mon->bornnum << " earned "
      		 << temp << " elements for his headquarter" << endl;
      	return;
      }

      class CJudgeVictory
      {
      private:
      	int Invader[2];
      public:
      	CJudgeVictory()
      	{
      		Invader[0]=0;
      		Invader[1]=0;
      	}

      	int getStatus()
      	{
      		if(Invader[RED]==2)
      			return RED;
      		else if(Invader[BLUE]==2)
      			return BLUE;
      		else
      			return NEUTRAL;
      	}

      	void MonsterArrive(CWorrior *x)
      	{
      		++Invader[x->side];
      		x->move();
      		return;
      	}
      };

      bool Turn(CHeadquarter & RedBase,CHeadquarter & BlueBase,map<int,CCity *> & TownCluster,CJudgeVictory & Victory,vector<CWorrior *> & RedMon,vector<CWorrior *> & BlueMon,const int & T)
      {
      	CWorrior *temp_1=RedBase.creatMonster();
      	CWorrior *temp_2=BlueBase.creatMonster();
      	CWorrior *newmonblue=temp_2;
      	if(temp_1!=NULL)
      		RedMon.push_back(temp_1);
      	if(temp_2!=NULL)
      		BlueMon.push_back(temp_2);
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
      	temp_2=TownCluster[1]->MonsterOut(BLUE);
      	if(temp_2!=NULL)
      		Victory.MonsterArrive(temp_2);
      	for(int i=1;i<CWorrior::totalCityNum;++i)
      	{
      		temp_2=TownCluster[i]->MonsterOut(RED);
      		TownCluster[i]->MonsterIn(temp_1);
      		temp_1=temp_2;
      		temp_2=TownCluster[i+1]->MonsterOut(BLUE);
      		TownCluster[i]->MonsterIn(temp_2);
      	}
      	temp_2=TownCluster[CWorrior::totalCityNum]->MonsterOut(RED);
      	TownCluster[CWorrior::totalCityNum]->MonsterIn(temp_1);
      	TownCluster[CWorrior::totalCityNum]->MonsterIn(newmonblue);
      	temp_1=temp_2;
      	if(temp_1!=NULL)
      		Victory.MonsterArrive(temp_1);
      	switch(Victory.getStatus())
      	{
      	case RED:
      		cout << gTime << "blue headquarter was taken" << endl;
      		return false;
      	case BLUE:
      		cout << gTime << "red headquarter was taken" << endl;
      		return false;
      	default:break;
      	}
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
      	for(int i=1;i<=CWorrior::totalCityNum;++i)
      		TownCluster[i]->creatElements();
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
      	for(int i=1;i<=CWorrior::totalCityNum;++i)
      	{
      		if((TownCluster[i]->getMon(RED)!=NULL)&&(TownCluster[i]->getMon(BLUE)==NULL))
      			getElements(TownCluster[i]->getMon(RED),TownCluster[i],RedBase,BlueBase);
      		else if((TownCluster[i]->getMon(RED)==NULL)&&(TownCluster[i]->getMon(BLUE)!=NULL))
      			getElements(TownCluster[i]->getMon(BLUE),TownCluster[i],RedBase,BlueBase);
      	}
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
      	for(int i=1;i<=CWorrior::totalCityNum;++i)
      		TownCluster[i]->activateBattle(RedBase,BlueBase);
      	gTime.nextphase();
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
      	return true;
      }

      int main()
      {
      	gTime.reset();
      	unsigned int M,N,T,i;
      	cin >> M >> N >> T;
      	CWorrior::totalCityNum=N;
      	for(int i=0;i<5;++i)
      		cin >> gMonProperty.HPset[i];
      	for(i=0;i<5;++i)
      		cin >> gMonProperty.ATKset[i];
      	CHeadquarter RedBase(M,RED,gMonProperty,N),BlueBase(M,BLUE,gMonProperty,N);
      	map<int,CCity *> TownCluster;
      	vector<CWorrior *> RedMon,BlueMon;
      	CJudgeVictory Victory;
      	for(i=1;i<=N;++i)
      		TownCluster[i]=new CCity(i);
      	while(Turn(RedBase,BlueBase,TownCluster,Victory,RedMon,BlueMon,T));
      	for(i=1;i<=N;++i)
      		delete TownCluster[i];
      	for(vector<CWorrior *>::iterator j=RedMon.begin();j!=RedMon.end();++j)
      		delete *j;
      	for(vector<CWorrior *>::iterator j=BlueMon.begin();j!=BlueMon.end();++j)
      		delete *j;
      		
      		int ggg;
              cin>>ggg; 
      	return 0;
      }
