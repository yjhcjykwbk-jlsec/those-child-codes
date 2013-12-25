#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <iostream>
using std::endl;
using std::cout;
int main(){
	int sock;int _ret;
	char *ip="127.0.0.1";
	struct sockaddr_in sa;
	unsigned long inaddr=(unsigned long)inet_addr(ip);
	memcpy((char *)&sa.sin_addr,(char*)&inaddr,sizeof(inaddr));
	sa.sin_family=AF_INET;
	sa.sin_port=htons(80);
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
            cout<<"socket is not successful"<<endl;
	    return -1;
        }
	int optval=1;
        //设置socket的状态
	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&optval,sizeof(optval)<0)){
	    cout<<"setsocketopt() in createsocket"<<endl;
	    close(sock);
	    return -1;
	}
        _ret=connect(sock,(struct sockaddr*)&sa,sizeof(struct sockaddr));
	if(_ret==-1){
	    cout<<"non_connect "<<endl;
	    close(sock);
	    return -1;
	}
	cout<<"socket is "<<sock<<endl;
        //发送请求报文 即写入socket“文件”请求信息
        char requestBuf[1000];
        char httpVersion[20]="HTTP/1.0";
        char host="www.baidu.com";
        requestBuf[0]=0;
        //如果不知道文件名(可能是index.html)，则/即可
        snprintf(requestBuf,1000,"GET / %s\r\n",HTTP_VERSION);
        //host
        strcat(requestBuf,"Host: ");
        strcat(requestBuf,host);
        strcat(requtstBuf,"\r\n");
        //agent
        strcat(requestBuf,"User-Agent: ");
        strcat(requestBuf,Default_user_agent);
        strcat(requestBuf,"/"); 
        strcat(tequestBuf,Version);
	ret=write(sock,reques{
//	cout<<requestBuf<<endl;
//	cout<<"write nothing"<<endl;
	}
	}
