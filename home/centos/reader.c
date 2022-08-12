nclude <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define N 128

int main(int argc, const char *argv[])
{
	int fd;	
	char buf[N] = "";
	if(mkfifo("/home/linux/myfifo", 0664) < 0){
		if(errno == EEXIST){
			fd = open("/home/linux/myfifo", O_RDWR);
			printf("fd = %d\n", fd);
		}
		else{
			printf("mkfifo error");
		}
	}
	else{
		fd = open("/home/linux/myfifo", O_RDWR);
		printf("fd = %d\n", fd);
	}

	while(1){
		fgets(buf, N, stdin);
		buf[strlen(buf) - 1] = '\0';

		write(fd, buf, strlen(buf));

		if(strncmp(buf, "quit", 4) == 0){
			break;
		}
	}
	return 0;
}
