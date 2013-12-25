#define ENDSTRING '\0'
int strlen(char *string){
	int len=0;
	while(string[len]!=ENDSTRING)
		len++;
	return len;
}
