#include <stdio.h>
#include <time.h>
int main() {
time_t biggest = 0x7FFFFFFF;
printf("biggest = %s \n", ctime(&biggest) );
scanf("%s");
return 0; 
} 
 
