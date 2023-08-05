#include "socketUtil.h"
#include<stdbool.h>
#include<pthread.h>

typedef struct user
{
    int socketID;
    struct sockaddr_in address;
    char *userName;
    int error;
    bool isConnected;

    struct user * next;

}user;

typedef struct room
{
    user * userList;
    user *end;
    int numUsers;
} room;

user * acceptConnections(int);
void talkToClient(int *);
void handleConnection(int);

//linkedList Functions
void insertUser(room * , user *);

int main()
{
    int serverSocketID = createTCPIpv4Socket();

    struct sockaddr_in * serverAddress = createIpv4Address("",2000);

    int result = bind (serverSocketID , (const struct sockaddr *)serverAddress , sizeof(*serverAddress));
    if(result == 0)
	printf("Socket was bound successfully......Receiving messages ....\n\n");

    
    int listenResult = listen (serverSocketID,10);

    room newRoom;
    newRoom.userList = NULL;
    newRoom.end = NULL;
    newRoom.numUsers = 0;

    while(true)
    {
	user * newClient = acceptConnections(serverSocketID);

	insertUser(&newRoom , newClient);

	handleConnection(newClient -> socketID);
    }

    shutdown(serverSocketID , SHUT_RDWR);

    return 0;
}

void insertUser(room  * currentRoom , user * newUser)
{

    if(currentRoom -> userList == NULL)
    {
	currentRoom -> userList = newUser;
	currentRoom -> end = newUser;
	return;
    }

    currentRoom -> end -> next = newUser;
    currentRoom -> numUsers++;


    printf("\nSYS : New user added ... total - %d\n\n" , currentRoom -> numUsers);

    return;
}

void handleConnection(int clientSocketID)
{
    pthread_t id;

    int *newClientID = (int *)malloc(sizeof(int));
    *newClientID = clientSocketID;


    int createNewThead = pthread_create(&id , NULL , talkToClient , newClientID);

    return;
}

void talkToClient(int *clientSocketID)
{
    char buffer[1024];

    int thisClientID = *clientSocketID;

    while(true)
    {
	ssize_t charRecv = recv(thisClientID, buffer , 1024 , 0);

	if(charRecv <= 0) break;

	buffer[charRecv] = 0;

	printf("%d :  %s \n" , thisClientID,  buffer);
    }

    close(thisClientID);

}

user *acceptConnections(int serverSocketID)
{
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketID = accept (serverSocketID ,(struct sockaddr *) &clientAddress , &clientAddressSize);

    user *connection = (user *) malloc(sizeof(user));

    connection -> socketID = clientSocketID;
    connection -> address = clientAddress;
    connection -> isConnected = clientSocketID > 0;
    connection -> next = NULL;

    if(!connection -> isConnected) connection -> error = clientSocketID;

    return connection;
}
