# 1 "string.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "string.c"

int strlen(char *string){
 int len=0;
 while(string[len]!='\0')
  len++;
 return len;
}
