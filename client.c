#include "socketUtil.h"
#include<stdbool.h>

int main()
{
    int socketID = createTCPIpv4Socket();

    struct sockaddr_in *address = createIpv4Address("",2000);


    int result = connect(socketID ,(struct sockaddr *) address , sizeof(*address));

    if(result == 0)
	printf("connection was successful....Sending messages ..\n\n");
    else 
    {
	if(result == -1)
	    perror("Error in connect");
    }

    char *line = NULL;
    size_t lineSize = 0;

    printf("Enter text to send .....(type exit to return):\n");

    while(true)
    {
	ssize_t charCount = getline(&line , &lineSize , stdin);

	if(charCount <= 0) continue;
	if(strcmp(line , "exit\n") == 0) break;

	ssize_t charSent = send(socketID , line , charCount , 0);
    }

    shutdown(socketID , SHUT_RDWR);

    return 0;
}
