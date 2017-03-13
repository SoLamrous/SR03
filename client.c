#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>
#include <unistd.h>
#include "iniobj.h"

int main(int argc, char *argv[])
{
  int sd, rece;
  obj objet;
  struct sockaddr_in sin;
  struct hostent *hp;

  sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(sd==-1)
  {
    printf("ERREUR");
    exit(-1);
  }
  bzero(&sin, sizeof(sin));
  hp = gethostbyname(argv[1]);
  bcopy(hp->h_addr,&sin.sin_addr, hp->h_length);
  sin.sin_family = hp->h_addrtype;
  sin.sin_port = htons(atoi(argv[2]));
  if(connect(sd, (struct sockaddr*) &sin, sizeof(sin))==-1)
  {
    printf("Erreur connect");
    exit(-1);
  }
    send(sd, &tabobj[0],sizeof(objet),0);

	rece=recv(sd,&objet,sizeof(objet),0);

	printf("objet reçu: %s\n",objet.id);
	
	obj fin = {"fin","",0,0,0};
	send(sd, &fin, sizeof(fin),0);
	printf("end request sent.\n");

  close(sd);
  exit(0);

  return(0);
}
