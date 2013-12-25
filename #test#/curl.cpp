#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

struct MemoryStruct {
  char *memory;
  size_t size;
};
static size_t
WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)data;
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    exit(EXIT_FAILURE);
  }
  memcpy(&(mem->memory[mem->size]), ptr, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  return realsize;
}

static char* post_callback(char *url,struct MemoryStruct *chunk)
{
   CURL *curl_handle;
   chunk->memory = malloc(1);
   chunk->size = 0;
   char* crst;
   curl_global_init(CURL_GLOBAL_ALL);
   curl_handle = curl_easy_init();
   curl_easy_setopt(curl_handle, CURLOPT_URL, url);
   curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
   curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)chunk);
   curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
   curl_easy_perform(curl_handle);
   curl_easy_cleanup(curl_handle);
   curl_global_cleanup(); 
     if(chunk->size>0)
  {
   //printf("%s \n", chunk.memory);
   crst = chunk->memory;
  }
  else{
     printf("something wrong!");
  }
   return crst;  
  /* we're done with libcurl, so clean it up */ 

}
int main(int argc, char *argv[])
{
  char* rst;
  struct MemoryStruct *chunk;
  rst =post_callback("http://hi.baidu.com/firwind/",&chunk);
      
 printf("%s \n",rst);
 if(chunk->memory)
     free(chunk->memory);
  return 0;
}

 

