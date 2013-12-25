  #include <iostream>
      #include <vector>
      #include <string>
      #include <map>
      #include<fstream> 
      using std::vector;
      using std::map;
      //using std::cin;////
      //using std::cout;////
      using std::string;
      using std::ostream;
      using std::endl;
      using std::fstream;// 
      const bool RED=false;
      const bool BLUE=true;
      const short NEUTRAL=3;
      const string COLOR[2]={"red","blue"};
      fstream cout("4.txt");//
      fstream  cin("war.in");// 
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

      enum WorriorEnum{_Dragon,_ninja,_Iceman,_Lion,_Wolf};

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
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " reached blue headquarter" <<  " with "<<HP<<" elements and force "<<ATK<<endl;
      			else
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " marched to city " << inWitchCity << " with "<<HP<<" elements and force "<<ATK<<endl;
      		}
      		else
      		{
      			--inWitchCity;
      			if(inWitchCity==0)
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " reached red headquarter" << " with "<<HP<<" elements and force "<<ATK<<endl;
      			else
      				cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " marched to city " << inWitchCity << " with "<<HP<<" elements and force "<<ATK<<endl;
      		}
      		return;
      	}

      	virtual void attack(CWorrior *enemy,int n)
      	{
      		cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " attacked " << COLOR[enemy->side] << ' '
      			 << enemy->monType << ' '<< enemy->bornnum << " in city "<< n << " with "<<HP<<" elements and force "<<ATK<<endl;
      		enemy->hurted(ATK);
      		return;
      	}

      	virtual void strikeback(CWorrior *enemy,int n)
      	{
      		cout << gTime << COLOR[side] << ' '<< monType << ' '<< bornnum << " fought back against " << COLOR[enemy->side]
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

      	virtual void killed()
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
      		cout << gTime << COLOR[side] << " dragon " << bornnum << " yelled in city " << inWitchCity << endl;
      		return;
      	}
      public:
      	CDragon(MonProperty setting,bool color,unsigned int num,const string & montype,int totalcitynum):
      	  CWorrior(setting.HPset[_Dragon],setting.ATKset[_Dragon],color,num,montype,totalcitynum),FirstAttack(false) {	}

      	void attack(CWorrior *enemy,int n)
      	{
          	FirstAttack=true;
          	CWorrior::attack(enemy,n);
      		return;
      	}    
      	void lastAffair(CWorrior *enemy)
      	{
      		if(ifalive()&&FirstAttack)//dragon yelled
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
         
      	void move()//iceman moves and changes his hp and atk
      	{
      		if(steps==1)
      		{
      			steps=0;
      			ATK+=20;
      			HP=(HP-9)>0?(HP-9):1;
      		}
      		else
      			++steps;
      		CWorrior::move();
      		return;
      	}
      };

      class CLion:public CWorrior
      {
      private:
      	int HPleft;//when lion dead ,he will give his previous hp to the killer. 
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
      		if(HP>0)
      			HPleft=HP;//lion's previous hp before be hurted
      		HP-=damage;
      		return;
      	}
      };

      class Cninja:public CWorrior
      {
      public:
      	Cninja(MonProperty setting,bool color,unsigned int num,const string & montype,int totalcitynum):
      	  CWorrior(setting.HPset[_ninja],setting.ATKset[_ninja],color,num,montype,totalcitynum) {	}
      	
      	void strikeback(CWorrior *enemy,int n)
      	{
      		return;//clinja never fight back,so he has to override this function 
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
      	   CWorrior::attack(enemy,n);
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
      	unsigned int AfterBattle_LifeEle;
      	bool Color;
      	unsigned int Population;
      	unsigned short CityNum;
      	const MonProperty Setting;
      public:
      	CHeadquarter(unsigned int lifeele,bool color,MonProperty data,unsigned short citynum):
      	  LifeEle(lifeele),Color(color),Setting(data),CityNum(citynum),Population(0) {AfterBattle_LifeEle=LifeEle;	}
      	
      	CWorrior *creatMonster();
        void setLifeEle()
        {    
            LifeEle=AfterBattle_LifeEle;
        }
        void tellLifeEle()
        {
            setLifeEle();
            cout<<gTime<<LifeEle<<" elements in "<<COLOR[Color]<<" headquarter"<<endl;
        }
        void setAfterBattle_LifeEle()
        {
             AfterBattle_LifeEle=LifeEle;
        }
        ////////////////奖励本方胜者 
      	void wardMonster(CWorrior * mon)
      	{
      		if(LifeEle>=8&&(mon->side==Color))
      		{
      			mon->getHP(8);
      			LifeEle-=8;
      			AfterBattle_LifeEle-=8;////////
      		}
      		return;
      	}

      	friend void getElements(const CWorrior *,CCity *,CHeadquarter &,CHeadquarter &);
      };
       ///////////制造怪兽 
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
      			if(LifeEle<Setting.HPset[_ninja])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_ninja];
      				++Population;
      				return new Cninja(Setting,Color,Population,"ninja",CityNum);
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
      			if(LifeEle<Setting.HPset[_ninja])
      				return NULL;
      			else
      			{
      				LifeEle-=Setting.HPset[_ninja];
      				++Population;
      				return new Cninja(Setting,Color,Population,"ninja",CityNum);
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
      	int ward; //奖励方，red=true=1；blue=false=0；none=-1 
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
        CWorrior *mon[2];
      	CCity(unsigned short n):
      	  num(n),elements(0),flag(NEUTRAL),semiflag(NEUTRAL)
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
      	
        int getward(){return ward;}
      	void activateBattle(CHeadquarter & redhead,CHeadquarter & bluehead)
      	{
            ward=-1;
      		if(mon[RED]!=NULL&&mon[BLUE]!=NULL)
      		{   //first is the first to attack 
      			bool first=judgeATKorder();
      			bool second=!first;
      			mon[first]->attack(mon[second],num);
      			if(mon[second]->ifalive()==false)
      			{
                    ward=first; //second dead ,ward first
                }
                else 
                {
                     mon[second]->strikeback(mon[first],num);
      			     if(mon[first]->ifalive()==false)
      			   {
                      ward=second;///////first dead,ward second
                   }
                }
                
                ///someone be killed
                if(ward!=-1)  //one worrior dead in the battle 
      		    {             
                    mon[1-ward]->killed();
    			    ///yelled
      			    mon[ward]->lastAffair(mon[1-ward]);
      			    ///lion give his hp to the killer
      			    mon[1-ward]->lastAffair(mon[ward]);
                    //liver earned elements for his headquater 
    			    getElements(mon[ward],this,redhead,bluehead); 
                    ///flag maybe changed because of a death    
                    if(semiflag==ward) 
                    {
                        if(flag!=ward) 
                        {
                           flag=ward;
    					   cout << gTime << COLOR[ward] << " flag raised in city " << num << endl;
                        }
                    }	
    				semiflag=ward;	
      				mon[1-ward]=NULL;//the loser dead
      			}
      			else semiflag=NEUTRAL;
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
      		redside.AfterBattle_LifeEle+=temp;
      		city->elements=0;
      		break;
      	case BLUE:
      		blueside.AfterBattle_LifeEle+=temp;
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
            if(Invader[RED]==2&&Invader[BLUE]==2)
                return NEUTRAL;
      		if(Invader[RED]==2)
      			return RED;
      		else if(Invader[BLUE]==2)
      			return BLUE;
      		else
      			return -1;
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
        int i;
      	CWorrior *temp_1=RedBase.creatMonster();
      	CWorrior *temp_2=BlueBase.creatMonster();
      	CWorrior *newmonblue=temp_2;
      	if(temp_1!=NULL)
      		RedMon.push_back(temp_1);
      	if(temp_2!=NULL)
      		BlueMon.push_back(temp_2);
    	///////////////////////////第十秒 
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
   		//蓝队temp2到达红队司令部 
      	temp_2=TownCluster[1]->MonsterOut(BLUE);
      	if(temp_2!=NULL)
      		Victory.MonsterArrive(temp_2);
      	//0和n+1代表总部。1-n代表城市 
      	for(i=1;i<CWorrior::totalCityNum;++i)
      	{
      		temp_2=TownCluster[i]->MonsterOut(RED);//红队temp2从第i个城市出来 
      		TownCluster[i]->MonsterIn(temp_1);//红队temp1到达第i个city 
      		temp_1=temp_2;
      		temp_2=TownCluster[i+1]->MonsterOut(BLUE);//蓝队temp2从i+1出来，进入i 
      		TownCluster[i]->MonsterIn(temp_2);
      	}
      	temp_2=TownCluster[CWorrior::totalCityNum]->MonsterOut(RED);//红队temp2到达蓝队司令部 
      	TownCluster[CWorrior::totalCityNum]->MonsterIn(temp_1);//红队temp1到达最后一个city 
      	TownCluster[CWorrior::totalCityNum]->MonsterIn(newmonblue);//蓝队新兵进入第一个city 
      	if(temp_2!=NULL)
      		Victory.MonsterArrive(temp_2);
      	switch(Victory.getStatus())
      	{
        case NEUTRAL://双方司令部都被占领 
        {
            cout << gTime << "red headquarter was taken" << endl; 
            cout << gTime << "blue headquarter was taken"<<endl;
            return false;
        }
      	case RED:
      		cout << gTime << "blue headquarter was taken"<<endl;
      		return false;
      	case BLUE:
      		cout << gTime << "red headquarter was taken"<<endl;
      		return false;
      	default:break;
      	}
      	RedBase.setAfterBattle_LifeEle();
      	BlueBase.setAfterBattle_LifeEle();
        //////////////////////////第二十秒 
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
      	for(i=1;i<=CWorrior::totalCityNum;++i)
      		TownCluster[i]->creatElements();
        //////////////////////////第三十秒 
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
      	//在每个小时的第30分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，
        //并立即将这些生命元传送到其所属的司令部 
      	for(i=1;i<=CWorrior::totalCityNum;++i)
      	{
      		if((TownCluster[i]->getMon(RED)!=NULL)&&(TownCluster[i]->getMon(BLUE)==NULL))
      			getElements(TownCluster[i]->getMon(RED),TownCluster[i],RedBase,BlueBase);
      		else if((TownCluster[i]->getMon(RED)==NULL)&&(TownCluster[i]->getMon(BLUE)!=NULL))
      			getElements(TownCluster[i]->getMon(BLUE),TownCluster[i],RedBase,BlueBase);
      	}
      	RedBase.setLifeEle();//更新生命元数量 
   		BlueBase.setLifeEle();
      	///////////////////////////第四十秒 
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
   		//战斗开始了 
      	for(i=1;i<=CWorrior::totalCityNum;++i)
      		TownCluster[i]->activateBattle(RedBase,BlueBase);
      	/////奖励战胜的武士们
      	//奖励是按照此次战斗以前总部的生命元数量来计算的。 
      	for(i=1;i<=CWorrior::totalCityNum;++i)
      		if(TownCluster[i]->getward()==BLUE)
            {
      			  BlueBase.wardMonster(TownCluster[i]->mon[BLUE]);   
            }   
        for(i=CWorrior::totalCityNum;i>=1;--i)
      		if(TownCluster[i]->getward()==RED)
            {
      			  RedBase.wardMonster(TownCluster[i]->mon[RED]);   
            }                
         //////////////////////////第五十秒 
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
      	RedBase.tellLifeEle();//报告总部生命元
        BlueBase.tellLifeEle(); 
        ///////////////////////////第六十秒  
      	gTime.nextphase();
      	if(gTime>T)
      		return false;
      	return true;
      }

      int main()
      {
          
        int cases,p,i;
        cin>>cases;
        unsigned int m[1000],n[1000],t[1000];
        unsigned int M,N,T;
        unsigned int HPSET[1000][5];
        unsigned int ATKSET[1000][5];
        for(p=0;p<cases;p++)
        {
            cin >> m[p] >> n[p] >> t[p];   
            for(i=0;i<5;++i) cin >> HPSET[p][i];
            for(i=0;i<5;++i) cin >> ATKSET[p][i];
        }             
        for(p=1;p<=cases;p++)
        { 
        M=m[p-1],N=n[p-1],T=t[p-1];
      	gTime.reset();
      	cout<<"Case:"<<p<<endl;
      	CWorrior::totalCityNum=N;
      	for(i=0;i<5;++i)
      		gMonProperty.HPset[i]=HPSET[p-1][i];
      	for(i=0;i<5;++i)
      		gMonProperty.ATKset[i]=ATKSET[p-1][i];
      		
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
        }

      	return 0;
      }

