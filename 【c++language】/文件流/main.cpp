#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

struct data
{
       char name[20];
       int beginpos;
       int endpos;
};
ostream & operator <<(ostream& out,data &a)
{
      out.write((const char*)(&a),sizeof(data));
      return out;
}
istream & operator >>(istream& in,data &a)
{
      in.read(( char*)(&a),sizeof(data));
      return in;
}
void merge_e (int argc, char *argv[])
{
      if(argc<3 || strcmp(argv[1],"-e")!=0) return;
      cout<<argv[argc-1]<<endl;
      fstream a[20]; 
      char t;
      data temp;
      char tempstr[30];
      strcpy(tempstr,argv[argc-1]);
      ofstream b(tempstr,ios::out);
      b.seekp(0);
      
      int num=argc-3;

      b.write((char* )(&num),sizeof(int));
      int pos=sizeof(int);

      int beginpos=pos+(argc-3)*sizeof(data),endpos=0;
      for(int i=2;i<argc-1;i++)
      {
            a[i].open( argv[i],ios::in); 
            a[i].seekg(0);
            b.seekp(beginpos);
            cout<<beginpos<<" ";
            while( a[i].get(t))
            {
                  b.put(t);
            }
            a[i].close();
            endpos=b.tellp();
            cout<<endpos<<endl;
            strcpy(temp.name,argv[i]);
            temp.beginpos=beginpos;
            temp.endpos=endpos;
            
            b.seekp(pos);
            b<<temp;
            pos=b.tellp();
  
            beginpos=endpos;
      }
      b.close();
}
void merge_x (int argc, char *argv[])      
{
     if(argc<3|| strcmp(argv[1],"-x")!=0) return;
     int num;
     fstream a(argv[2]);
     fstream b[20];
     a.seekg(0);
     a.read((char *)(&num),sizeof(int));
     int pos=4;
     int beginpos,endpos,i,j;char t;
     data temp[20]; 
     for(i=0;i<num;i++)
       {  
        a>>temp[i];
        cout<<temp[i].name<<" "<<temp[i].beginpos<<" "<<temp[i].endpos<<endl;
       }
     for(i=0;i<num;i++)
     {
          b[i].open(temp[i].name,ios::out);
          b[i].seekp(0);
          a.seekg(temp[i].beginpos);
          j=temp[i].beginpos;
          endpos=temp[i].endpos;
          while(j<endpos)
          {
                a.get(t);
                b[i].put(t);
                j++;
          }
          b[i].close();
     }
     a.close();
}
                                 
int main(int argc, char *argv[])
{
    system("PAUSE");
    merge_e(argc,argv);
    merge_x(argc,argv);
    return EXIT_SUCCESS;
}
