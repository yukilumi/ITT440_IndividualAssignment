#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<signal.h>

int main(void)
{
void sigint_handler(int sig);
if(signal(SIGINT,sigint_handler)==SIG_ERR)
{
perror("signal");
exit(1);
}

while(1)
{
int fd[2];
pipe(fd);
pid_t pid=fork();

char name[50];
char buffer[50];

if(pid>0)
{
printf("\nEnter your name:");
if(fgets(name,50,stdin)==NULL)
perror("gets");
close(fd[0]);
write(fd[1],name, 50);
wait(NULL);
printf("Okay;\n");
}

if(pid==0)
{
close(fd[1]);
read(fd[0],buffer,50);
printf("Your name is  %s",buffer);
close(fd[0]);
exit(EXIT_SUCCESS);
}

}
return EXIT_SUCCESS;
}

void sigint_handler(int sig)
{
printf("Oops interrupt detected. Exiting the program\n");
exit(1);
}
