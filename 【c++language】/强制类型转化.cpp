#include <iostream>
using namespace std; 
class CBaseX  
{  
    public:  
        int x;  
        CBaseX() { x = 10; }  
        void foo() { printf("CBaseX::foo() x=%d\n", x); }  
};  
class CBaseY  
{  
    public:  
        char t;
        int y;  
        int* py;  
        CBaseY() { y = 20; py = &y; }  
        void ar()  { printf("hello\n"); }
        void bar() { printf("CBaseY::bar() y=%d, *py=%d\n", y, *py);   
        }  
};  
class CDerived : public CBaseX, public CBaseY  
{  
    public:  
        int z;  
};
int main(){
    CBaseY* pY3 = new CBaseY();  
    printf("CBaseY* pY3 = %x\n", (int)pY3);  
    // �ɹ�����,���� pY3 ֻ��һ�� "�� CBaseY()"   
    CDerived* pD3 = static_cast<CDerived*>(pY3);  
    //��Ȼ�ˣ���������ǿ������ת��֮��ָ���ֵ������ģ���ָ��CDerived���͡��������CDerivedʵ���ǲ�����CBaseX���ݲ��ֵġ� 
    printf("CDerived* pD3 = %x\n", (int)pD3);

    // Convert between CBaseX* and CBaseY*   
    // CBaseX* �� CBaseY*֮���ת��   
    CBaseX* pX = new CBaseX();
    // Error, types pointed to are unrelated   
    // ���� ����ָ�����޹ص�   
    //     CBaseY* pY1 = static_cast<CBaseY*>(pX);   
    // Compile OK, but pY2 is not CBaseX   
    // �ɹ�����, ���� pY2 ����CBaseX   
    CBaseY* pY2 = reinterpret_cast<CBaseY*>(pX);  
    // System crash!!   
    // ϵͳ����!!  
    pX->foo(); 
    pY2->ar();//���������ڷ�������������ʶ���ģ�����㳢��ת��һ��������һ���޹ص���static_cast<>��ʧ�ܣ���reinterpret_cast<>�����ǳɹ�����ƭ�����������Ǹ���������Ǹ��޹��ࡣ  

    void *pV = pY3;
    printf("CBaseY* pY3 = %x\n", (int)pY3);  
    CDerived *pD4=static_cast<CDerived*>(pV);
    printf("CDerived* pD4 = %x\n", (int)pD4);  
    pD4->foo();

    int i;
    cin>>i;
}

