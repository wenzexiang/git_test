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
	if(mkfifo("home/linux/myfifo", 0664) < 0){
		if(errno == EEXIST){
			fd = open("home/linux/myfifo", O_RDWR);
			printf("fd = %d\n", fd);
		}
		else{
			printf("mkfifo error");
		}
	}
	else{
		fd = open("home/linux/myfifo", O_RDWR);
		printf("fd = %d\n", fd);
	}

	while(1){
		read(fd, buf, N);

		if(strncmp(buf, "quit", 4) == 0){
			system("rm fifo");
			break;
		}

		printf("reader:%s\n", buf);
	}
	return 0;
}

