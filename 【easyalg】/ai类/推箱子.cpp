/*
������
���ߣ�MasterRay
ʱ�䣺2007-10-18
����Visual C++����
*/
#include <windows.h>
#include <conio.h>

#define ENTER 13
#define ESC 27
#define SPACE 32
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ARROW 224

HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE); //��ñ�׼������
COORD TopLeft={0, 0}, MainPos={0, 5};
FILE *f;
char map[720], FileName[256]={"box\\"};
int x, y, //�����ߵ�����
DirectionX[20], DirectionY[20], //Ŀ�������
maxx, maxy, level=1;

char *DecToStr(char *str, int dec)
{
char ch, *left=str, *right=str, *p;
do
{
*right++=dec%10|'0';
}while (dec/=10);
p=right--;
while (left<right)
{
ch=*left;
*left++=*right;
*right--=ch;
}
*p++='.';
*p++='t';
*p++='x';
*p++='t';
*p='\0';
return str;
}

//�����ͼ
void ClearMap()
{
FillConsoleOutputCharacter(hOut, ' ', 1600, MainPos, 0);
}

//����ͼ
void DrawMap()
{
COORD pos={0, 7};
short i=0, j, p=0;
char ch;
ClearMap();
SetConsoleCursorPosition(hOut, pos);
for (; i<maxy; i++)
{
for (j=0; j<maxx; j++)
{
switch (map[i*maxx+j])
{
case 'B': //����
SetConsoleTextAttribute(hOut, FOREGROUND_BLUE|FOREGROUND_INTENSITY); //��ɫ
WriteConsoleA(hOut, "��", 2, 0, 0);
break;
case 'D': //Ŀ��
DirectionX[p]=j;
DirectionY[p++]=i;
SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //��ɫ
WriteConsoleA(hOut, "��", 2, 0, 0);
break;
case 'F': //Ŀ��+����
map[i*maxx+j]='B';
DirectionX[p]=j;
DirectionY[p++]=i;
SetConsoleTextAttribute(hOut, FOREGROUND_BLUE|FOREGROUND_INTENSITY); //��ɫ
WriteConsoleA(hOut, "��", 2, 0, 0);
break;
case 'P': //������
x=j;
y=i;
SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_INTENSITY); //��ɫ
WriteConsoleA(hOut, "��", 2, 0, 0);
break;
case 'W': //ǽ
SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //��ɫ
WriteConsoleA(hOut, "��", 2, 0, 0);
break;
default:
SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //��ɫ
WriteConsoleA(hOut, "��", 2, 0, 0);
}
}
pos.Y++;
SetConsoleCursorPosition(hOut, pos);
}
DirectionX[p]=DirectionY[p]=0;
SetConsoleCursorPosition(hOut, MainPos);
SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //��ɫ
}

//�µ�ͼ
void NewMap()
{
int ch;
char *p=map, flag=1;
DecToStr(FileName+4, level);
if ((f=fopen(FileName, "r"))==0) TerminateProcess(GetCurrentProcess(), 0);
maxy=1;
while ((ch=fgetc(f))!=EOF)
{
if (ch!='\r' && ch!='\n') *p++=ch;
else {maxx=p-map; break;}
}
while ((ch=fgetc(f))!=EOF)
{
if (ch!='\r' && ch!='\n')
{
if (flag)
{
maxy++;
flag=0;
}
*p++=ch;
}
else if (ch=='\n') flag=1;
}
DrawMap();
}

//ʤ��
void NextMap()
{
SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //��ɫ
SetConsoleCursorPosition(hOut, MainPos);
WriteConsoleA(hOut, "��Ӯ�ˣ�\n", 8, 0, 0);
level++;
getch();
NewMap();
}

//�ж��Ƿ�ʤ��
void JudgeMap()
{
char win=1;
short p=0;
COORD pos;
SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //��ɫ
while (DirectionX[p])
{
if (map[DirectionY[p]*maxx+DirectionX[p]]!='B')
{
win=0;
if (DirectionX[p]!=x || DirectionY[p]!=y)
{
pos.X=DirectionX[p]<<1;
pos.Y=DirectionY[p]+7;
SetConsoleCursorPosition(hOut, pos);
WriteConsoleA(hOut, "��", 2, 0, 0);
}
}
p++;
}
SetConsoleCursorPosition(hOut, MainPos);
if (win) NextMap();
SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}

//ѡ���ͼ
void SelectMap()
{
int i, n=3;
char szLevel[1];
SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //��ɫ
SetConsoleCursorPosition(hOut, MainPos);
WriteConsoleA(hOut, "�ؿ���\n", 6, 0, 0);
level=0;
while ((i=getch())!='\r')
{
if (i>='0' && i<='9')
{
level*=10;
level+=i&15;
szLevel[0]=i;
WriteConsoleA(hOut, szLevel, 1, 0, 0);
if (n--==0) break;
}
}
NewMap();
}

//��ʼ��Ϸ
void StartGame()
{
SetConsoleTextAttribute(hOut, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
SetConsoleCursorPosition( 
 
 
  
 ���ߣ� 221.217.151.*  2009-9-5 15:06 ��  
 
--------------------------------------------------------------------------------
 
2 ������Visual C++Դ����  
 hOut, TopLeft);
WriteConsoleA(hOut, "������ ����������\n", 18, 0, 0);
SetConsoleTextAttribute(hOut, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
WriteConsoleA(hOut, "ENTER����ѡ�ء���\nSPACE�������¿�ʼ\nESC�������˳�������", 53, 0, 0);
}

//�����������ƶ�
void move(short heading)
{ 
COORD pos={x<<1 ,y+7};
SMALL_RECT rc={x<<1, y+7, (x<<1)+1, y+7};
CHAR_INFO chFill;
chFill.Attributes=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
chFill.Char.AsciiChar=' ';
switch (heading)
{
case UP:
if (y>0)
{
if (map[(y-1)*maxx+x]!='B' && map[(y-1)*maxx+x]!='W')
{
y--;
pos.Y--;
}
else if (y>1 && map[(y-1)*maxx+x]=='B' && map[(y-2)*maxx+x]!='B' && map[(y-2)*maxx+x]!='W')
{
map[(y-1)*maxx+x]='P';
map[(y-2)*maxx+x]='B';
y--;
pos.Y-=2;
rc.Top--;
}
}
else return;
break;
case LEFT:
if (x>0)
{
if (map[y*maxx+x-1]!='B' && map[y*maxx+x-1]!='W')
{
x--;
pos.X-=2;
}
else if (x>1 && map[y*maxx+x-1]=='B' && map[y*maxx+x-2]!='B' && map[y*maxx+x-2]!='W')
{
map[y*maxx+x-1]='P';
map[y*maxx+x-2]='B';
x--;
pos.X-=4;
rc.Left-=2;
} 
}
else return;
break;
case RIGHT:
if (x<maxx-1)
{
if (map[y*maxx+x+1]!='B' && map[y*maxx+x+1]!='W')
{
x++;
pos.X+=2;
}
else if (x<maxx-2 && map[y*maxx+x+1]=='B' && map[y*maxx+x+2]!='B' && map[y*maxx+x+2]!='W')
{
map[y*maxx+x+1]='P';
map[y*maxx+x+2]='B';
x++;
pos.X+=2;
rc.Right+=2;
}
}
else return;
break;
case DOWN:
if (y<maxy-1)
{
if (y<maxy-1 && map[(y+1)*maxx+x]!='B' && map[(y+1)*maxx+x]!='W')
{
y++;
pos.Y++;
}
else if (y<maxy-2 && map[(y+1)*maxx+x]=='B' && map[(y+2)*maxx+x]!='B' && map[(y+2)*maxx+x]!='W')
{
map[(y+1)*maxx+x]='P';
map[(y+2)*maxx+x]='B';
y++;
pos.Y++;
rc.Bottom++;
}
}
else return;
break;
default:
return;
}
ScrollConsoleScreenBuffer(hOut, &rc, 0, pos, &chFill);
JudgeMap();
}

//��ȡ����
void GetKey()
{
switch (getch())
{
case ENTER: SelectMap(); break;
case ESC: CloseHandle(hOut); TerminateProcess(GetCurrentProcess(), 0);
case SPACE: NewMap(); break;
case ARROW: move(getch());
}
}

int main()
{
//���ô��ڴ�С
COORD size={80, 25};
SetConsoleScreenBufferSize(hOut, size);

SetConsoleOutputCP(936); //����ҳ����Ϊ��������
SetConsoleTitleA("�����ӡ���MasterRay"); //���ô��ڱ���

StartGame();
NewMap();
while (1)
GetKey();
return 0;
} 
 
 
