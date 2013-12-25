//处理hosts文件，进行去重
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;
int main(){
	FILE *hosts=fopen("/etc/hosts","r");
	char ip[1000];
	char host[1000];
	map<string,string> _map;
	int i=0;
	while(fscanf(hosts,"%s %s\n",ip,host)>0){
		_map[host]=ip;i++;
	}
	printf("%d\n",i);
	fclose(hosts);
	hosts=fopen("/etc/hosts","w");
	fseek(hosts,0,0);
	i=0;
	for(map<string,string>::iterator it=_map.begin();it!=_map.end();it++){
		string s=it->first,t=it->second;
		fprintf(hosts,"%s %s\n",t.c_str(),s.c_str());
		i++;
	}
	fprintf(hosts,"###################################end\n");
	printf("%d\n",i);
	fclose(hosts);
	return 0;
}

