/*
	<<Practice of Programming in C&C++>>
	Sample Program of Team Game -- Blokus  
	Written by Zhong Cheng, Mar.22nd, 2009
*/
 
#include <iostream>
#include <string>
using namespace std;

const int
	Length = 19,
	//��Ϸ���̵Ĺ�ģ��[0..19]*[0..19]����
	Piecesize = 4,
	//����Ĺ�ģ��[0..4]*[0..4]����
	Piecenum = 20,
	//����ĸ������������Ϊ0, 1, ... , 20����

	Blankcolour = 4,
	//��Ϸ�����Ͽհ׸��ӵ���ɫ��
	Mycolour = 5;
	//�Լ��������ɫ��

struct board {
		int
			b[Length + 1][Length + 1];
	};
	//��Ϸ���̡���[i][j]������ֵ����ʾ��i�С���j�еĸ��ӵ���ɫ��
	//�������е����������ꡱ[x][y]��Ҳ����ʾ��x�С���y�С�
struct piece {
		int
			p[Piecesize + 1][Piecesize + 1];
	};
	//���飬�������ֵΪ1��0����ʾ�ø����Ƿ�ռ��

const piece
	Iron[Piecenum + 1] =
	//��Ϸ�����и�����21�ַ��顣
		{
			//No.0
			{
				{1, 0, 0, 0, 0,				
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.1
			{
				{1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.2
			{
				{1, 1, 1, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.3
			{
				{1, 1, 1, 1, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
		
			//No.5
			{
				{1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.6
			{
				{1, 1, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.4
			{
				{1, 1, 1, 1, 1,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.7
			{
				{1, 1, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.8
			{
				{1, 1, 0, 0, 0,
				 0, 1, 1, 0, 0,
				 0, 0, 1, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
				
			//No.9
			{
				{1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.10
			{
				{1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.11
			{
				{1, 0, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.16
			{
				{1, 1, 1, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.13
			{
				{1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.14
			{
				{0, 1, 0, 0, 0,
				 1, 1, 1, 0, 0,
				 0, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.15
			{
				{1, 0, 0, 0, 0,
				 1, 1, 1, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.12
			{
				{1, 0, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 1, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			
			//No.17
			{
				{0, 1, 1, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.18
			{
				{0, 1, 1, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.19
			{
				{0, 1, 1, 0, 0,
				 0, 1, 0, 0, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			},
			//No.20
			{
				{0, 1, 1, 1, 0,
				 1, 1, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0}
			}
		};
const int
	Ironsize[Piecenum + 1] =
	//����Ĵ�С����ÿ������ķ�ֵ��
		{
			1, 2, 3, 4, 5, 3, 4,
			5, 5, 4, 5, 4, 5, 5,
			5, 5, 5, 4, 5, 5, 5
		};

board
	cur;
	//��ǰ����Ϸ���̡�
piece
	diamond[Piecenum + 1][8];
	//��[i][d]��������ʾ��i�ַ��龭��d�ַ�ʽ��ת�󣬵õ��ķ��顣
bool
	used[Piecenum + 1];
	//��[i]������ʾ��i�������Ƿ��ѱ�ʹ�á�
int
	fx, fy;
	//��һ��������븲�ǵĸ������ꡣ
bool
	meetend;
	//�Ƿ��յ�[end]ָ�

void turn(int d, piece oir, piece & res);
//����oir����d�ַ�ʽ��ת�󣬵õ�����res��
void forge();
//����diamond���顣
void clean(board & cur);
//��ʼ����Ϸ���̡�
void start(board & cur);
//ִ��[start]ָ�

bool putable(board cur, int x, int y, int i, int d);
//�ж���(x, y)Ϊ���Ͻ�����ĵ�i�ַ��飬����d�ַ�ʽ��ת��õ��ķ��飬�ܷ񱻷�����
//��ǰ�����ϡ�
bool putablefirst(int x, int y, int i, int d);
//�ж���(x, y)Ϊ���Ͻ�����ĵ�i�ַ��飬����d�ַ�ʽ��ת��õ��ķ��飬�ܷ���Ϊ��һ
//�����飬�������������ϡ�

void putsingle(board & cur, int x, int y, int p, int i, int d);
//����(x, y)Ϊ���Ͻ�����ĵ�i�ַ��飬����d�ַ�ʽ��ת��õ��ķ��飬����ɫp������
//�����ϡ�
void putothers(board & cur);
//ִ��[put]ָ������������������������õķ��飬������Ϸ���̸������ӵ���ɫ��
void putmine(board & cur);
//����ѡ��ö�٣���������ࡢ��ת��ʽ��λ�ã�ֱ�����ܹ������ڵ�ǰ������Ϊֹ����
//��������
void putminefirst(board & cur);
//����ѡ��ö�٣���һ����������ࡢ��ת��ʽ��λ�ã�ֱ�����ܹ������ڵ�ǰ������Ϊ
//ֹ������������

int main()
{
	forge();
	start(cur);
	//��ʼ����Ϸ���̣���������Ϸ���跽�顣
	putothers(cur);
	putminefirst(cur);
	//���õ�һ�����顣
	meetend = false;
	for (;;) {
		putothers(cur);
		if (meetend == true)
			break;
		putmine(cur);
	}
	//���ϸ���������µ�ǰ��Ϸ���̣�������Լ��ķ�����Ϣ��ֱ�����յ�[end]ָ�
	return 0;
}

void turn(int d, piece oir, piece & res)
//����oir����d����ת��ʽ�󣬵õ�����res��
{
	int
		u, v;

	switch (d) {
		case 0 :
		//ԭ״��
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[u            ][v            ];
		break;

		case 1 :
		//����90�ȡ�
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[Piecesize - v][u            ];
		break;

		case 2 :
		//����180�ȡ�
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[Piecesize - u][Piecesize - v];
		break;

		case 3 :
		//����270�ȡ�
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[v            ][Piecesize - u];
		break;

		case 4 :
		//ˮƽ��ת��
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[u            ][Piecesize - v];
		break;

		case 5 :
		//ˮƽ��ת������90�ȡ�
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[Piecesize - v][Piecesize - u];
		break;

		case 6 :
		//ˮƽ��ת������180�ȡ�
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[Piecesize - u][v            ];
		break;

		case 7 :
		//ˮƽ��ת������270�ȡ�
		for (u = 0; u <= Piecesize; u++)
		for (v = 0; v <= Piecesize; v++)
			res.p[u][v] = oir.p[v            ][u            ];
	}
}

void forge()
//����diamond���顣
{
	int
		i, d;

	for (i = 0; i <= Piecenum; i++)
	for (d = 0; d <= 7; d++)
		turn(d, Iron[i], diamond[i][d]);
	//����i�ַ��飨Iron[i]������d����ת��ʽ��õ��ķ��飬��¼��diamond���顣
}

void clean(board & cur)
//��ʼ����Ϸ���̡�
{
	int
		u, v;

	for (u = 0; u <= Length; u++)
	for (v = 0; v <= Length; v++)
		cur.b[u][v] = Blankcolour;
	//����Ϸ���̳�ʼ��Ϊδ���÷���ĸ��ӵ���ɫ��
}

void start(board & cur)
//ִ��[start]ָ�
{
	string
		command;

	getline(cin, command);
	cin>>fx>>fy;
	cin.get();
	//�����һ��������븲�ǵĸ��ӡ�
	clean(cur);
	memset(used, 0, sizeof(used));
	//��ʼ����Ϸ���̣��������з�����Ϊ��δʹ�ù���״̬��
}

bool putable(board cur, int x, int y, int i, int d)
//�ж���(x, y)Ϊ���Ͻ�����ĵ�i�ַ��飬����d�ַ�ʽ��ת��õ��ķ��飬�ܷ񱻷�����
//��ǰ�����ϡ�
{
	int
		u, v;
	bool
		corner;
	
	corner = false;
	for (u = 0; u <= Piecesize; u++)
	for (v = 0; v <= Piecesize; v++) {
		if (
			(diamond[i][d].p[u][v] == 1) &&
			(
				((x + u) < 0     ) ||
				((y + v) < 0     ) ||
				((x + u) > Length) ||
				((y + v) > Length) ||
				//�Ƿ��и��ӳ�����Ϸ���̵ķ�Χ��
				(cur.b[x + u][y + v] != Blankcolour) ||
				(
					((y + v + 1) <= Length) &&
					(cur.b[x + u    ][y + v + 1] == Mycolour)
					//�ұߡ�
				) ||
				(
					((x + u + 1) <= Length) &&
					(cur.b[x + u + 1][y + v    ] == Mycolour)
					//�±ߡ�
				) ||
				(
					((y + v - 1) >= 0) &&
					(cur.b[x + u    ][y + v - 1] == Mycolour)
					//��ߡ�
				) ||
				(
					((x + u - 1) >= 0) &&
					(cur.b[x + u - 1][y + v	   ] == Mycolour)
					//�ϱߡ�
				)
				//�Ƿ����Լ��ĸ��������ڵıߡ�
			)
		)
			return false;
		if (
			(corner == false) &&
			(diamond[i][d].p[u][v] == 1) &&
			(
				(
					((x + u - 1) >= 0     ) &&
					((y + v + 1) <= Length) &&
					(cur.b[x + u - 1][y + v + 1] == Mycolour)
					//���Ͻǡ�
				) ||
				(
					((x + u + 1) <= Length) &&
					((y + v + 1) <= Length) &&
					(cur.b[x + u + 1][y + v + 1] == Mycolour)
					//���½ǡ�
				) ||
				(
					((x + u + 1) <= Length) &&
					((y + v - 1) >= 0     ) &&
					(cur.b[x + u + 1][y + v - 1] == Mycolour)
					//���½ǡ�
				) ||
				(
					((x + u - 1) >= 0     ) &&
					((y + v - 1) >= 0     ) &&
					(cur.b[x + u - 1][y + v - 1] == Mycolour)
					//���Ͻǡ�
				)
			)
			//�Ƿ��������Ķ��㡣
		)
			corner = true;
	}
	if (corner == true)
		return true;
	else
		return false;
	//��������������Ķ��㣬����Ϊ���ܡ���
}

bool putablefirst(int x, int y, int i, int d)
//�ж���(x, y)Ϊ���Ͻ�����ĵ�i�ַ��飬����d�ַ�ʽ��ת��õ��ķ��飬�ܷ���Ϊ��һ
//�����飬�������������ϡ�
{
	int
		u, v;
	bool
		filled;

	filled = false;
	for (u = 0; u <= Piecesize; u++)
	for (v = 0; v <= Piecesize; v++) {
		if (
			(diamond[i][d].p[u][v] == 1) &&
			(
				((x + u) < 0     ) ||
				((y + v) < 0     ) ||
				((x + u) > Length) ||
				((y + v) > Length)
			)
			//�Ƿ��и��ӳ�����Ϸ���̵ķ�Χ����һ�η��÷���ʱ�����������Լ��ĸ���
			//�����ڵıߣ���������ж���һ�㣩��
		)
			return false;
		if (
			(diamond[i][d].p[u][v] == 1) &&
			((x + u) == fx) &&
			((y + v) == fy)
			//�Ƿ��ܸ��Ǹ���(fx, fy)��
		)
			filled = true;
	}
	if (filled == true)
		return true;
	else
		return false;
	//�������(fx, fy)�����ǣ�����Ϊ���ܡ���
}

void putsingle(board & cur, int x, int y, int p, int i, int d)
//����(x, y)Ϊ���Ͻ�����ĵ�i�ַ��飬����d�ַ�ʽ��ת��õ��ķ��飬����ɫp������
//�����ϡ�
{
	int
		u, v;

	for (u = 0; u <= Piecesize; u++)
	for (v = 0; v <= Piecesize; v++)
		if (diamond[i][d].p[u][v] == 1)
			cur.b[x + u][y + v] = p;
		//��Ϊ(x, y)�����Ͻ����꣬���Ը÷����(u, v)λ�ã���Ӧ����Ϸ�����ϵ�
		//(x + u, y + v)λ�á�
}

void putothers(board & cur)
//ִ��[put]ָ������������������������õķ��飬������Ϸ���̸������ӵ���ɫ��
{
	string
		command;
	int
		n, ni, x, y, p, i, d;

	getline(cin, command);
	if (command == "[end]") {
		meetend = true;
		return;
	}
	//�������[end]ָ�����Ϸ�������Զ��˳���

	cin>>n;
	cin.get();
	for (ni = 1; ni <= n; ni++) {
		cin>>x>>y>>p>>i>>d;
		cin.get();
		putsingle(cur, x, y, p, i, d);
		//ÿ����һ��������������õķ��飬��������һ�Ρ�
	}
}

void putmine(board & cur)
//����ѡ��ö�٣���������ࡢ��ת��ʽ��λ�ã�ֱ�����ܹ������ڵ�ǰ������Ϊֹ����
//��������
{
	int
		u, v, i, d;

	for (u = (- Piecesize); u <= Length; u++)
	for (v = (- Piecesize); v <= Length; v++)
	//ö�ٷ������Ͻǵĸ��ӵ����ꡣ
	for (i = Piecenum; i >=0 ; i--)/////////////////////////////////ö��˳��ı� 
	//ö�ٷ������ࡣ
	for (d = 0; d <= 7; d++)
	//ö����ת��ʽ��
		if (
			(used[i] == false) &&
			(putable(cur, u, v, i, d) == true)
			//�����δ��ʹ�ã��ҿ��Է����ڵ�ǰ��Ϸ�����ϡ�
		) {
			putsingle(cur, u, v, Mycolour, i, d);
			used[i] = true;
			cout<<u<<' '<<v<<' '<<i<<' '<<d<<endl<<flush;
			//���ݸ÷�������ࡢ��ת��ʽ��λ�ã��������Ϸ��ø÷��鲢��������
			return;
		}
}

void putminefirst(board & cur)
//����ѡ��ö�٣���һ����������ࡢ��ת��ʽ��λ�ã�ֱ�����ܹ������ڵ�ǰ������Ϊ
//ֹ������������
{
	int
		u, v, i, d;

	for (u = (- Piecesize); u <= Length; u++)
	for (v = (- Piecesize); v <= Length; v++)
	//ö�ٷ������Ͻǵĸ��ӵ����ꡣ
	for (i = 0; i <= Piecenum; i++)
	//ö�ٷ������ࡣ
	for (d = 0; d <= 7; d++)
	//ö����ת��ʽ��
		if (putablefirst(u, v, i, d) == true) {
			//����������Ϊ��һ�����飬�������������ϡ�
			putsingle(cur, u, v, Mycolour, i, d);
			used[i] = true;
			cout<<u<<' '<<v<<' '<<i<<' '<<d<<endl<<flush;
			//���ݸ÷�������ࡢ��ת��ʽ��λ�ã��������Ϸ��ø÷��鲢��������
			return;
		}
}
