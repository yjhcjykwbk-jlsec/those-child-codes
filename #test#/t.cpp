#include <iostream>
#include <stdio.h>
using namespace std;
 
int  encode(const  void*  raw_in,  void*  raw_out,  uint32_t  password,  size_t  len) 
{ 
const  uint8_t*  in  =  (const  uint8_t*)raw_in; 
uint8_t*  out  =  (uint8_t*)raw_out; 

uint32_t  seed  =  password  ^  0x239e36f4u; 
for  (size_t  i  =  0  ;  i  <  len;  ++i)  { 
uint8_t  a  =  (  in[i]  ^  seed  )  >>  1; 
uint8_t  b  =  (  (  ((uint32_t)in[i])  <<  20  )  ^  seed  )  >>  (20-7); 
a  &=  127; 
b  &=  128; 
a  =  127  &  (  a  ^  (b  <<  3)); 
out[i]  =  a  |  b; 
seed  =  (seed  *  5393887  +  out[i]); 
} 
} 



int  decode(const  void*  raw_in,  void*  raw_out,  uint32_t  password,  size_t  len) 
{ 
const  uint8_t*  in  =  (const  uint8_t*)raw_in; 
uint8_t*  out  =  (uint8_t*)raw_out; 

uint32_t  seed  =  password  ^  0x239e36f4u; 
for  (size_t  i  =  0  ;  i  <  len;  ++i)  { 
//  请在此处补全代码 
uint32_t a,b;
a=in[i]&127;
b=in[i]&128;
a^=((b<<3)&255);
a&=127;
b<<=(20-7);
b^=seed;
b>>=20;
b&=1;
a<<=1;
a^=seed;
a&=254;
out[i]=(uint8_t)(a|b);
seed  =  (seed  *  5393887  + in[i]); 
} 
} 
int  main() 
{ 
const  uint8_t  buf1[]  =  {0x8a,  0x8d,  0x6d,  0xbe,  0x3b,  0xf3,  0xb5,  0x35,  0xc6,  0xf6,  0xdc,  0xe5,  0x85,  0xc4,  0xd7,  0xe9,  0x73,  0xc4,  0x1d,  0x8d,  0x02,  0xc8,  0x08,  0xaa,  0x61,  0x78,  0x1f,  0x29,  0xf3,  0x09,  0x08,  0x27,  0x4b,  0x1b,  0x83,  0x7f,  0xf1,  0x08,  }; 
uint8_t  buf2[100]  =  {}; 
const  uint32_t  password  =  0x51f78b2bu; 
const  size_t  len  =  sizeof(buf1); 
decode(buf1,  buf2,  password,  len); 
printf("%s\n",  buf2); 
} 


 
