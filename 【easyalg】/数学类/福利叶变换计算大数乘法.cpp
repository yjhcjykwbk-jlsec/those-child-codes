快速傅里叶变换计算大数相乘  
 FFT ：Fast Fourier Transform
10^10000 * 10^10000
long double 必须不少于80位

#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
using namespace std;

const long double PI = 3.1415926535897932384626433832795L;

int BitRev(int x, int n)
{
int res = 0;
for (; n != 1; n /= 2)
{
res = res*2+x%2;
x /= 2;
}
return res;
}

void FFT(complex<long double> x[], int n)
{
for (int i = 0; i < n; ++i)
{
int j = 0;
for (int t = i, k = n; k /= 2; t /= 2)
j = j*2+t%2;
if (j > i) swap(x[j], x[i]);
}
for (int k = 2; k <= n; k *= 2)
{
const complex<long double> omega_unit(cosl(2*PI/k), sinl(2*PI/k));
for (int i = 0; i < n; i += k)
{
complex<long double> omega(1, 0);
for (int j = 0; j < k/2; ++j)
{
complex<long double> t = omega*x[i+j+k/2];
x[i+j+k/2] = x[i+j]-t;
x[i+j] += t;
omega *= omega_unit;
}
}
}
}

void IFFT(complex<long double> x[], int n)
{
for (int i = 0; i < n; ++i)
{
int j = 0;
for (int t = i, k = n; k /= 2; t /= 2)
j = j*2+t%2;
if (j > i) swap(x[j], x[i]);
}
for (int k = 2; k <= n; k *= 2)
{
const complex<long double> omega_unit(cosl(-2*PI/k), sinl(-2*PI/k));
for (int i = 0; i < n; i += k)
{
complex<long double> omega(1, 0);
for (int j = 0; j < k/2; ++j)
{
complex<long double> t = omega*x[i+j+k/2];
x[i+j+k/2] = x[i+j]-t;
x[i+j] += t;
omega *= omega_unit;
}
}
}
for (int i = 0; i < n; ++i)
x[i] /= n;
}

int main()
{
static char str[10001];
static complex<long double> a[8192], b[8192];
int a_size = 0, b_size = 0, n;

gets(str);
for (int size = (int)strlen(str); size > 3; str[size -= 3] = '\0')
a[a_size++] = atof(str+size-3);
a[a_size++] = atof(str);
gets(str);
for (int size = (int)strlen(str); size > 3; str[size -= 3] = '\0')
b[b_size++] = atof(str+size-3);
b[b_size++] = atof(str);

a_size += b_size;
for (n = a_size; n != (n&-n); n += n&-n);
FFT(a, n);
FFT(b, n);
for (int i = 0; i < n; ++i)
a[i] *= b[i];
IFFT(a, n);

for (int i = 0; i < a_size-1; ++i)
{
a[i+1] += a[i].real()/1000.;
a[i] = fmodl(a[i].real(), 1000.L);
}
if (!(int)a[a_size-1].real())
--a_size;
printf("%d", (int)a[a_size-1].real());
for (int i = a_size-2; i >= 0; --i)
printf("%03d", (int)a[i].real());
putchar('\n');
return 0;
}

-----

Number Theoretic Transform
使用质数代替单位根进行运算，更快并且免去复数运算误差

#include <algorithm>
#include <cstdio>
using namespace std;

const unsigned P = 2013265921; //15*2^27+1
const unsigned OMEGA = 440564289; //root，31^15 % P
const unsigned INV_TWO = 1006632961; //2^(-1)
char str[10001];
unsigned a[8192], b[8192], roots[8192];

unsigned Power(unsigned x, unsigned y)
{
unsigned res = 1;
for (; y; y /= 2)
{
if (y&1) res = (unsigned long long)res*x%P;
x = (unsigned long long)x*x%P;
}
return res;
}

void FFT(unsigned x[], int n)
{
unsigned root = Power(OMEGA, (1<<27)/n);
roots[0] = 1;
for (int i = 1; i < n; ++i)
roots[i] = (unsigned long long)roots[i-1]*root%P;
for (int i = 0; i < n; ++i)
{
int j = 0;
for (int t = i, k = n; k /= 2; t /= 2)
j = j*2+t%2;
if (j > i) swap(x[i], x[j]);
}
for (int k = 2; k <= n; k *= 2)
for (int i = 0; i < n; i += k)
for (int j = 0; j < k/2; ++j)
{
unsigned t = (unsigned long long)roots[n*j/k]*x[i+j+k/2]%P;
x[i+j+k/2] = (x[i+j]-t+P)%P;
x[i+j] = (x[i+j]+t)%P;
};
}

void IFFT(unsigned x[], int n)
{
unsigned root = Power(OMEGA, (1<<27)/n*(n-1));
roots[0] = 1;
for (int i = 1; i < n; ++i)
roots[i] = (unsigned long long)roots[i-1]*root%P;
for (int i = 0; i < n; ++i)
{
int j = 0;
for (int t = i, k = n; k /= 2; t /= 2)
j = j*2+t%2;
if (j > i) swap(x[i], x[j]);
}
for (int k = 2; k <= n; k *= 2)
for (int i = 0; i < n; i += k)
for (int j = 0; j < k/2; ++j)
{
unsigned t = (unsigned long long)roots[n*j/k]*x[i+j+k/2]%P;
x[i+j+k/2] = (x[i+j]-t+P)%P;
x[i+j] = (x[i+j]+t)%P;
};
unsigned inv_n = 1;
for (int i = n; i /= 2; )
inv_n = (unsigned long long)inv_n*INV_TWO%P;
for (int i = 0; i < n; ++i)
x[i] = (unsigned long long)x[i]*inv_n%P;
}

int main()
{
int a_size = 0, b_size = 0, n;

gets(str);
for (int size = (int)strlen(str); size > 3; str[size -= 3] = '\0')
a[a_size++] = atoi(str+size-3);
a[a_size++] = atoi(str);
gets(str);
for (int size = (int)strlen(str); size > 3; str[size -= 3] = '\0')

 
 
  
 作者： 221.217.151.*  2009-9-5 12:01 　  
 
--------------------------------------------------------------------------------
 
2 快速傅里叶变换计算大数相乘  
 b[b_size++] = atoi(str+size-3);
b[b_size++] = atoi(str);

a_size += b_size;
for (n = a_size; n != (n&-n); n += n&-n);
FFT(a, n);
FFT(b, n);
for (int i = 0; i < n; ++i)
a[i] = (unsigned long long)a[i]*b[i]%P;
IFFT(a, n);

for (int i = 0; i < a_size-1; ++i)
{
a[i+1] += a[i]/1000;
a[i] %= 1000;
}
if (!a[a_size-1]) --a_size;
printf("%u", a[a_size-1]);
for (int i = a_size-2; i >= 0; --i)
printf("%03u", a[i]);
putchar('\n');
return 0;
} 
 
 
