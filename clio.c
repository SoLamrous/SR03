#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>
#include "iniobj.h"

int main(int argc, char *argv[])
{
  int sd,i;
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
  for(i = 0;i < 3; i++)
  {
    send(sd, &tabobj[i],sizeof(objet),0);
  }
  exit(0);

  return(0);
}
