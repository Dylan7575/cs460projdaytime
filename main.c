#include <arpa/inet.h>
#include "Header.h"

char* read_line(int socket);

int main() {
    int sock;
    struct sockaddr_in dest;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){//creating socket and error checking
		perror("Socket has malfuncioned");
		exit(-1);
	}
	dest.sin_family=AF_INET;
	dest.sin_port= htons(PORT_NUM);

	if ( inet_pton(AF_INET,SERVER_NAME,&dest.sin_addr) < 0 )//assigning address to socket
	{
		perror("");
		exit(errno);
	}
	if(connect(sock,(struct sockaddr*)&dest, sizeof(dest))!=0){//connecting local socket to dest socket and error checking
		perror("Error Connecting");
		exit(0);
	}
	printf("%s",read_line(sock));  //sending sending socket to be read and printing results
	close(sock);//closing the socket

    return 0;//ending program
}
char* read_line(int socket){
	int counter=0; //for going through buffer array
	char* buffer=malloc(80* sizeof(char)); // mallocing an array to keep variable saved
	while((read(socket,&buffer[counter],1))>0){//reading in the stream byte by byte so to catch the otm character
		if(buffer[counter]== OTM_CHAR){//if the character is the OTM char go back one char and null terminate and break loop
			buffer[counter-1]='\0';
			break;
		}
		counter++;//incrementing array

	}
	return buffer;//returning full string
}