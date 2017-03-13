#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/wait.h>
#include <signal.h>

#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>
#include <unistd.h>
#include "defobj.h"


static void handler (int signalNum);
pid_t childPID;
int status;

int main(int argc, char *argv[])
{

	int sd, newsd, rece;
	struct sockaddr_in sin;
	obj objet;
	sd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sd==-1)
		{ 
			printf("ERREUR");
			exit( -1);
		}
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port=htons(atoi(argv[1]));
	if(bind(sd, (struct sockaddr*) &sin, sizeof(sin))==-1)
		{
			printf("ERREUR bind");
			exit(-1);
		}
	
if (listen(sd,5)==-1)
				printf("erreur co");
else 	{while(1) {
	newsd =accept(sd,0,0);
	if(newsd==-1)
		{
			printf("ERREUR accept");
			exit( -1);
		}


	signal(SIGCHLD, handler);	

	childPID = fork();

	switch(childPID){
	case 0:
		
		rece=recv(newsd,&objet,sizeof(objet),0);
		printf("\n objet reçu: %s ,  %s \n",objet.id, objet.desc);
		while(rece != 0){
			sleep(1);
			if(rece==-1)
				{
					printf("Erreur recv"); 
					exit( -1);
				}
			else
				{
					if(strcmp("fin", objet.id) == 0)
					{
						printf("\n close connection socket , le PID: %d\n", getpid());
						close(newsd);
						signal(SIGCHLD, handler);			
						if (kill(getpid(),0)==-1) printf("kill error");
						exit(0);
					}
					else
					{	
						printf("objet reçu: %s ,  %s \n",objet.id, objet.desc);
						strcpy(objet.id, "testUpdate");
						send(newsd, &objet,sizeof(objet),0);
						printf("objet modifié envoyé: %s ,  %s \n",objet.id, objet.desc);
						rece=recv(newsd,&objet,sizeof(objet),0);	
						printf("objet reçu du client: %s ,  %s \n",objet.id, objet.desc);

					}
				}
		}
		exit(0);

	break;

	case -1:
	printf("ERREUR accept");
	break;
	
	default:
	break;
	}}
	close(sd);}
	exit(0);
}

static void handler (int signalNum)
{
	waitpid(childPID, &status, WUNTRACED);
}
