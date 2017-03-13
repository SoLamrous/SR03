#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>
#include <unistd.h>
#include "defobj.h"

int main(int argc, char *argv[])
{

	int sd, newsd, pid, rece;
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
	listen(sd,5);
	newsd =accept(sd,0,0);
	if(newsd==-1)
		{
			printf("ERREUR accept");
			exit( -1);
		}
	pid = fork();
	switch(pid){
	case 0:
		rece=recv(newsd,&objet,sizeof(objet),0);
		while(rece != 0){
			if(rece==-1)
				{
					printf("Erreur recv"); 
					exit( -1);
				}
			else
				{
					printf("objet reçu: %s",objet.id);
					rece=recv(newsd,&objet,sizeof(objet),0);
				}
		}
		exit(0);

	break;

	case -1:
	printf("ERREUR accept");
	break;
	
	default:
		newsd =accept(sd,0,0);
		if(newsd==-1)
		{
		printf("ERREUR accept");
		exit( -1);
		}
	break;
	}

	exit(0);
}
