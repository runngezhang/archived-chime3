#include <windows.h>
#include <stdio.h>
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include "udp.h"
#include <iostream.h>

//create a subscriber that will create a filter for all packets going to client and having the
//client's username
SienaSubscriber::SienaSubscriber(char *_host, short _port, char *_username, NavCallback *_nav) {

	nav = _nav;
	username = _username;
	host = _host;
	port = _port;

	
	WORD wVersionRequested = MAKEWORD (2,2); // Version of Winsock that is used <2.2>
	WSADATA wsaData;
	int nRet;

	nRet = WSAStartup (wVersionRequested, &wsaData); // Initializes Winsock

	// Checks for the correct version of winsock
	if (wsaData.wVersion != wVersionRequested)
		printf ("\n\nError: Winsock did not Initialize Properly\n\n");
	
	else
	{
		LPHOSTENT lpht = gethostbyname (host);

		if (lpht == NULL)
			fprintf (stderr, "\n\nWinsock Error: Host Not Found\n\n");

		r = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
		if (r == INVALID_SOCKET)
			fprintf (stderr, "\n\nWinsock Error: Invalid Socket\n\n");

		SOCKADDR_IN saR;

		saR.sin_family      = AF_INET;
		saR.sin_addr.s_addr = INADDR_ANY;	
		saR.sin_port        = htons (5000);

		if (bind (r, (LPSOCKADDR) &saR, sizeof (struct sockaddr)) == SOCKET_ERROR)
		{
			fprintf (stderr, "\n\nWinsock Error: Unable to Bind\n\n");
			closesocket (r);
		}

	}

}

void SienaSubscriber::subscribeRoom(char *room) {

		SOCKET s = createSendSocket();	
		// Create Header
		sprintf (subscribeString, "senp{method=\"SUB\" ttl=30 version=1.1 id=\"randomnum.0.dez\" ");
		sprintf (subscribeString, "%sto=\"senp://", subscribeString);
		sprintf (subscribeString, "%s%s", subscribeString, host);
		sprintf (subscribeString, "%s:", subscribeString);
		sprintf (subscribeString, "%s%d\" ", subscribeString, port);
		sprintf (subscribeString, "%shandler=\"senp://localhost:5000\"}", subscribeString);


		// Create Filter
		sprintf (subscribeString, "%s filter{", subscribeString);
		sprintf (subscribeString, "%s address=\"%s\"}", subscribeString, room); 
		printf("Sending filter request: %s\n\n", subscribeString);

		// Subscribes
		if (send (s, subscribeString, strlen(subscribeString), 0) == SOCKET_ERROR)
		{
			fprintf (stderr, "\n\nWinsock Error: Unable to Send\n\n");
		}

		closesocket(s);
}

void SienaSubscriber::subscribeClient() {
		SOCKET s = createSendSocket();
		
		// Create Header
		sprintf (subscribeString, "senp{method=\"SUB\" ttl=30 version=1.1 id=\"randomnum.0.dez\" ");
		sprintf (subscribeString, "%sto=\"senp://", subscribeString);
		sprintf (subscribeString, "%s%s", subscribeString, host);
		sprintf (subscribeString, "%s:", subscribeString);
		sprintf (subscribeString, "%s%d\" ", subscribeString, port);
		sprintf (subscribeString, "%shandler=\"senp://localhost:5000\"}", subscribeString);


		// Create Filter
		sprintf (subscribeString, "%s filter{", subscribeString);
		sprintf (subscribeString, "%s username=\"%s\"}", subscribeString, username); 
		printf("Sending filter request: %s\n\n", subscribeString);

		// Subscribes
		if (send (s, subscribeString, strlen(subscribeString), 0) == SOCKET_ERROR)
		{
			fprintf (stderr, "\n\nWinsock Error: Unable to Send\n\n");
		}

		closesocket (s);
}


void SienaSubscriber::subscribeMethod(char *method) {
		SOCKET s = createSendSocket();
		
		// Create Header
		sprintf (subscribeString, "senp{method=\"SUB\" ttl=30 version=1.1 id=\"randomnum.0.dez\" ");
		sprintf (subscribeString, "%sto=\"senp://", subscribeString);
		sprintf (subscribeString, "%s%s", subscribeString, host);
		sprintf (subscribeString, "%s:", subscribeString);
		sprintf (subscribeString, "%s%d\" ", subscribeString, port);
		sprintf (subscribeString, "%shandler=\"senp://localhost:5000\"}", subscribeString);


		// Create Filter
		sprintf (subscribeString, "%s filter{", subscribeString);
		sprintf (subscribeString, "%s username=\"%s\"", subscribeString, username);
		sprintf (subscribeString, "%s method=\"%s\"}", subscribeString, method);
		printf("Sending filter request: %s\n\n", subscribeString);

		// Subscribes
		if (send (s, subscribeString, strlen(subscribeString), 0) == SOCKET_ERROR)
		{
			fprintf (stderr, "\n\nWinsock Error: Unable to Send\n\n");
		}

		closesocket (s);	
}

void SienaSubscriber::unsubscribeRoom(char *room) {
		SOCKET s = createSendSocket();

		// Create Header
		sprintf (subscribeString, "senp{method=\"UNS\" ttl=30 version=1.1 id=\"randomnum.0.dez\" ");
		sprintf (subscribeString, "%sto=\"senp://", subscribeString);
		sprintf (subscribeString, "%s%s", subscribeString, host);
		sprintf (subscribeString, "%s:", subscribeString);
		sprintf (subscribeString, "%s%d\" ", subscribeString, port);
		sprintf (subscribeString, "%shandler=\"senp://localhost:5000\"}", subscribeString);


		// Create Filter
		sprintf (subscribeString, "%s filter{", subscribeString);
		sprintf (subscribeString, "%s address=\"%s\"}", subscribeString, room); 
		printf("Sending filter request: %s\n\n", subscribeString);

		// Subscribes
		if (send (s, subscribeString, strlen(subscribeString), 0) == SOCKET_ERROR)
		{
			fprintf (stderr, "\n\nWinsock Error: Unable to Send\n\n");
		}
	
		closesocket (s);
}

void SienaSubscriber::unsubscribeClient() {
		SOCKET s = createSendSocket();

		// Create Header
		sprintf (subscribeString, "senp{method=\"UNS\" ttl=30 version=1.1 id=\"randomnum.0.dez\" ");
		sprintf (subscribeString, "%sto=\"senp://", subscribeString);
		sprintf (subscribeString, "%s%s", subscribeString, host);
		sprintf (subscribeString, "%s:", subscribeString);
		sprintf (subscribeString, "%s%d\" ", subscribeString, port);
		sprintf (subscribeString, "%shandler=\"senp://localhost:5000\"}", subscribeString);


		// Create Filter
		sprintf (subscribeString, "%s filter{", subscribeString);
		sprintf (subscribeString, "%s username=\"%s\"}", subscribeString, username); 
		printf("Sending filter request: %s\n\n", subscribeString);

		// Subscribes
		if (send (s, subscribeString, strlen(subscribeString), 0) == SOCKET_ERROR)
		{
			fprintf (stderr, "\n\nWinsock Error: Unable to Send\n\n");
		}

		closesocket (s);
}


SOCKET SienaSubscriber::createSendSocket() {
	WORD wVersionRequested = MAKEWORD (2,2); // Version of Winsock that is used <2.2>
	WSADATA wsaData;
	int nRet;

	nRet = WSAStartup (wVersionRequested, &wsaData); // Initializes Winsock

	// Checks for the correct version of winsock
	if (wsaData.wVersion != wVersionRequested) {
		printf ("\n\nError: Winsock did not Initialize Properly\n\n");
		return NULL;
	}
	
	else
	{
		LPHOSTENT lpht = gethostbyname (host);

		if (lpht == NULL)
			fprintf (stderr, "\n\nWinsock Error: Host Not Found\n\n");

		SOCKET s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
		if (s == INVALID_SOCKET)
			fprintf (stderr, "\n\nWinsock Error: Invalid Socket\n\n");

		SOCKADDR_IN saS;
		saS.sin_family		= AF_INET;
		saS.sin_addr		= *((LPIN_ADDR)*lpht -> h_addr_list);
		saS.sin_port		= htons (port);

		if (connect (s, (LPSOCKADDR) &saS, sizeof (struct sockaddr)) == SOCKET_ERROR)
		{
			fprintf (stderr, "\n\nWinsock Error: Unable to Connect\n\n");
			closesocket (s);
		}

		return s;
	}
}


void SienaSubscriber::formatResponse(char *string) {

	char *data = strstr(string, "data");
	printf("The first-first data is: %s\n", data);



/*
	if (strpbrk(string, "s_moveObject") != NULL)
		nav->GetSienaFunction(s_moveObject, 
	char *method = strtok(string, "method");
	printf("The method string is %s", method);
	method = strtok(method, "\"");
	printf("The method string is %s", method);
	sscanf(method, "%s\"", method);
	printf("The method is: %s", method);
	nav->GetSienaFunction(method);
	*/
}



void SienaSubscriber::startServer() {

	//make sure to subscribe the client
	//don't think this is really necessary
	subscribeClient();

	//let's just subscribe the client to all the methods that he wants
	subscribeMethod("s_moveObject");
	subscribeMethod("s_moveUser");
	subscribeMethod("s_addObject");
	subscribeMethod("s_enteredRoom");
	subscribeMethod("s_leftRoom");
	subscribeMethod("s_deleteObject");
	subscribeMethod("s_changeCLass");
	subscribeMethod("s_roomInfo");

	// Infinite loop to keep receiving events for the client 
	
			if (listen (r, SOMAXCONN) == SOCKET_ERROR)
			{
				fprintf (stderr, "\n\nWinsock Error: Unable to Listen\n\n");
				closesocket (r);
			}

		
	while(1)
		{
			SOCKET	remoteSocket;

			printf("\n\nListening...\n\n");
			remoteSocket = accept (r, NULL, NULL);

			if (remoteSocket == INVALID_SOCKET)
			{
				fprintf (stderr, "\n\nWinsock Error: Unable to Accept\n\n");
				closesocket (r);
			}

			char recvString [5000]; 
			int length = 0;
			if ((length = recv (remoteSocket, recvString, 5000, 0)) == SOCKET_ERROR)
			{
				fprintf (stderr, "\n\nWinsock Error: Unable to Recv\n\n");
				closesocket (r);
				closesocket (remoteSocket);
			}

			if (recvString != NULL)
				recvString[length] = NULL;
				formatResponse(recvString);
				//printf ("%s\n\n", recvString);
		}

		
	WSACleanup ();

	return;
}