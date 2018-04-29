//#define   MSGSIZE   20
       #include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>

//	Sample run output...
/*
emily@Emily-Ubuntu:~/Documents/unixc/unit09/examples$ gcc -g -o pipe pipe1.c
emily@Emily-Ubuntu:~/Documents/unixc/unit09/examples$ ll
total 60
-rwxrwxr-x 1 emily emily 11864 Apr  6 18:51 pipe*
-rw-r--r-- 1 emily emily  2437 Apr  6 18:50 pipe1.c
emily@Emily-Ubuntu:~/Documents/unixc/unit09/examples$ ./pipe "This  page  is  part of release 4.04 of the Linux man-pages project.  A
       description of the project, information about"

Input write -> pipe -> read Output write stdout...

This  page  is  part of release 4.04 of the Linux man-pages project.  A
       description of the project, information about
While loop count of read  buf[5] =    25
Total byte count of input string =   124

emily@Emily-Ubuntu:~/Documents/unixc/unit09/examples$ 
*/

int	main(int argc, char *argv[])
{
	int fd[2], pid, pipe(int fd[2]), fork();
	//	fd[0]: read  end of the pipe
	//	fd[1]: write end of the pipe
//	Data  written  to  the write end of the pipe is buffered by the
//      kernel until it is read from the read end of  the  pipe.
//	static char msgout[MSGSIZE] = "Hello, world\n";
//	static char msgin [MSGSIZE];
	
	if (argc != 2)	{
		fprintf(stderr, "Usage: %s <inputString>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("\nInput write -> pipe -> read Output write stdout...\n\n");
	if (pipe(fd) == -1) {
		perror(argv[0]);
		exit(EXIT_FAILURE);
		exit(1);
	}
	
	int  readBytes, loopCnt = 0, byteCnt = 0, bufSize = 5;
	char buf[bufSize];
	if ((pid = fork()) > 0) {	/* parent */
		close(fd[0]);	// parent close unused read end
		write(fd[1], argv[1], strlen(argv[1]));
		close(fd[1]);
//      wait for state changes in a child of  the  calling  process, and 
//	obtain information about the child whose state has changed.  
//	A state change is considered to be: the child  ter‐minated; 
		wait(NULL);	// wait for child to exit so that the prompt won't appear before child write out ends
		exit(EXIT_SUCCESS);
	}
	else if (pid == 0) {	/* child reads from pipe */
		close(fd[1]);	// child close unused write end
		while (1)
		{
			if (loopCnt % 2 == 0)
			{
				printf("\\");
		//		printf("%d", loopCnt);
			}
			else
				printf("/");
//			sleep(1);	
			printf("\b");
			loopCnt++;
		}
		write(STDOUT_FILENO, "\n\n", 1); 
//		puts(msgin);
		printf("While loop count of read  buf[%d] = %5d\n", bufSize, loopCnt); 
		printf("Total byte count of input string = %5d\n\n", byteCnt);  
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	else {		/* cannot fork */
		perror(argv[0]);
		exit(2);
	}
	
	exit(0);
}
