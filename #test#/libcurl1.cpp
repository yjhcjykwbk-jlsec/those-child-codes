#include <stdio.h>
#include "../include/curl/curl.h"
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#pragma comment (lib, "libcurl.lib")
#endif

FILE *fp; //定义FILE类型指针

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) //这个函数是为了符合CURLOPT_WRITEFUNCTION, 而构造的
{
	int written = fwrite(ptr, size, nmemb, (FILE *)fp);
	return written;
}

int main(int argc, char *argv[])
{
	CURL *curl;

	curl_global_init(CURL_GLOBAL_ALL); 
	curl=curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);

	char cFileName[128]={0};
	sprintf(cFileName,"%s.txt",argv[1]);

	if((fp=fopen(cFileName,"w"))==NULL)
	{
		curl_easy_cleanup(curl);
		exit(1);
	}
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); //CURLOPT_WRITEFUNCTION 将后继的动作交给write_data函数处理
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	exit(0);
}
