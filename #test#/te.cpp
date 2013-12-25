#include <iostream>
#include <stdio.h>
using namespace std;
int  encode(const  void*  raw_in,  void*  raw_out,  uint32_t  password,  size_t  len) 
{ 
const  uint8_t*  in  =  (const  uint8_t*)raw_in; 
uint8_t*  out  =  (uint8_t*)raw_out; 

uint32_t  seed  =  password  ^  0x6668518bu; 
for  (size_t  i  =  0  ;  i  <  len;  ++i)  { 
uint8_t  a  =  (  in[i]  ^  seed  )  >>  4; 
uint8_t  b  =  (  (  ((uint32_t)in[i])  <<  15  )  ^  seed  )  >>  (15-4); 
a  &=  15; 
b  &=  240; 
a  =  15  &  (  a  ^  (b  <<  3)); 
out[i]  =  a  |  b; 
seed  =  (seed  *  48475829  ^  seed  ^  in[i]); 
} 
} 


int  decode(const  void*  raw_in,  void*  raw_out,  uint32_t  password,  size_t  len) 
{ 
const  uint8_t*  in  =  (const  uint8_t*)raw_in; 
uint8_t*  out  =  (uint8_t*)raw_out; 

uint32_t  seed  =  password  ^  0x6668518bu; 
for  (size_t  i  =  0  ;  i  <  len;  ++i)  { 
//  请在此处补全代码 
uint32_t a,b;
a=in[i]&15;
b=in[i]&240;
a^=((b<<3)&255);
a&=15;
b<<=11;
b^=seed;
b>>=15;
b&=15;
a<<=4;
a^=seed;
a&=240;
cout<<"a:"<<a<<"b:"<<b<<endl;
out[i]=(uint8_t)(a|b);
seed  =  (seed  *  48475829  ^  seed  ^ out[i]); 
} 
printf("%s\n",tt);
} 
int  main() 
{ 
const  uint8_t  buf1[]  =  {0xdb,  0xa2,  0x23,  0xc8,  0x93,  0x5f,  0x67,  0x01,  0x61,  0x67,  0xe5,  0x0f,  0x8b,  0x0d,  0x7f,  0xb3,  0x87,  0xbd,  0xe1,  0xbb,  0xf9,  0x16,  0x17,  0x8f,  0x78,  0x71,  0x83,  0xaf,  0x04,  0xa1,  0x54,  0x81,  0xe4,  }; 
uint8_t  buf2[100]  =  {}; 
const  uint32_t  password  =  0x5f1b1bf8u; 
const  size_t  len  =  sizeof(buf1); 
decode(buf1,  buf2,  password,  len); 
printf("%s\n",  buf2); 
getchar();
} 


 
