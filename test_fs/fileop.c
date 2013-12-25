#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(void){
	int fd=-1,i;
	ssize_t size=-1;
	int input=0;
	char *buf="quick brown fox jumps \n";
	char *filename="test.txt";
	fd=open(filename,O_RDWR);// 读写方式打开
	if(-1==fd){
		printf("open file failed\n");
	}else{
		printf("open file %s as %d successfully\n",filename,fd);}
	size=write(fd,buf,strlen(buf));
	printf("write %d bytes to %s\n",size,filename);
	close(fd);
	return 0;
}
