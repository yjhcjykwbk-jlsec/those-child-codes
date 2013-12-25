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
    // 成功编译,尽管 pY3 只是一个 "新 CBaseY()"   
    CDerived* pD3 = static_cast<CDerived*>(pY3);  
    //当然了，经过向上强制类型转换之后，指针的值会减少四，以指向CDerived类型。而这里的CDerived实际是不包含CBaseX数据部分的。 
    printf("CDerived* pD3 = %x\n", (int)pD3);

    // Convert between CBaseX* and CBaseY*   
    // CBaseX* 和 CBaseY*之间的转换   
    CBaseX* pX = new CBaseX();
    // Error, types pointed to are unrelated   
    // 错误， 类型指向是无关的   
    //     CBaseY* pY1 = static_cast<CBaseY*>(pX);   
    // Compile OK, but pY2 is not CBaseX   
    // 成功编译, 但是 pY2 不是CBaseX   
    CBaseY* pY2 = reinterpret_cast<CBaseY*>(pX);  
    // System crash!!   
    // 系统崩溃!!  
    pX->foo(); 
    pY2->ar();//正如我们在泛型例子中所认识到的，如果你尝试转换一个对象到另一个无关的类static_cast<>将失败，而reinterpret_cast<>就总是成功“欺骗”编译器：那个对象就是那个无关类。  

    void *pV = pY3;
    printf("CBaseY* pY3 = %x\n", (int)pY3);  
    CDerived *pD4=static_cast<CDerived*>(pV);
    printf("CDerived* pD4 = %x\n", (int)pD4);  
    pD4->foo();

    int i;
    cin>>i;
}

