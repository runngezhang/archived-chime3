//*******************************************************************
//*
//* Implementation of ChimeComm communication class.
//*
//*******************************************************************

#include <stdlib.h>
#include <string.h>

#include "cssysdef.h"
#include "chimeComm.h"


chimeComm::chimeComm()
{
	
}

chimeComm::~chimeComm()
{

}

//Utility function to convert from float to string
char * chimeComm::ftoa(float num)
{
	int i, dec, sign, size;
	char str[15], tempstr[15];

	strcpy(tempstr, fcvt(num, 4, &dec, &sign));
	size = strlen(tempstr);

	for (i = 0; i < dec; i=i+1)
		str[i] = tempstr[i];

	str[dec] = '.'; //put the decimal point

	for (i = dec; i <=size; i=i+1)
		str[i+1] = tempstr[i];
	
	return strdup(str);
}

//Append given token to a string.
bool chimeComm::AppendToken(char *command, char *token)
{
	strcat(command, " ");
	strcat(command, token);

	return true;
}

//Connect to a given CHIME Server
bool chimeComm::Connect(char *server, char *userID, char *password)
{
	strcpy(command, server);	
	AppendToken(command, userID);
	AppendToken(command, password);

	//SendFunction(c_connect, command);
	return true;
}

//Request info about a given room
bool chimeComm::GetRoom(char *url)
{
	strcpy(command, url);

	//SendFunction(c_getRoom, command);
	return true;
}


//Send updated position of a moved object
bool chimeComm::MoveObject(char *roomUrl, char *objectUrl, float x, float y, float z)
{
	strcpy(command, roomUrl);
	AppendToken(command, objectUrl);
	AppendToken(command, ftoa(x));
	AppendToken(command, ftoa(y));
	AppendToken(command, ftoa(z));

	//SendFunction(c_moveObject, command);
	return true;
}

//Send updated position of the user
bool chimeComm::MoveUser(char *roomUrl, char *userID, float x, float y, float z, const csStrVector *userList)
{
	
	strcpy(command, roomUrl);
	AppendToken(command, userID);
	AppendToken(command, ftoa(x));
	AppendToken(command, ftoa(y));
	AppendToken(command, ftoa(z));
	 

	//SendFunction(c_moveUser, command);
	return true;
}

//Broadcast entrance of a user in a given room
bool chimeComm::UserEnteredRoom(char *userID, char *newRoomUrl, float x, float y, float z)
{
	
	strcpy(command, userID);
	AppendToken(command, newRoomUrl);
	AppendToken(command, ftoa(x));
	AppendToken(command, ftoa(y));
	AppendToken(command, ftoa(z));

	//SendFunction(c_enteredUser, command);
	return true;
}

//Broadcast that a user has lift a given room
bool chimeComm::UserLeftRoom(char *userID, char *oldRoomUrl)
{
	
	strcpy(command, userID);
	AppendToken(command, oldRoomUrl);	

	//SendFunction(c_leftUser, command);
	return true;
}

//Broadcast addition of new object in a given room
bool chimeComm::AddObject(char *roomUrl, char *objectUrl, float x, float y, float z)
{
	strcpy(command, roomUrl);
	AppendToken(command, objectUrl);
	AppendToken(command, ftoa(x));
	AppendToken(command, ftoa(y));
	AppendToken(command, ftoa(z));

	//SendFunction(c_addObject, command);

	return true;
}

//Broadcast deletion of new object in a given room
bool chimeComm::DeleteObject(char *roomUrl, char *objectUrl)
{
	strcpy(command, roomUrl);
	AppendToken(command, objectUrl);

	//SendFunction(c_deleteObject, command);
	return true;
}

//Subscribe for events of this room
bool chimeComm::SubscribeRoom(char *roomUrl, char *userID)
{
	strcpy(command, roomUrl);
	AppendToken(command, userID);

	//SendFunction(c_subscribeRoom, command);
	return true;
}
//Unsubscribe for events of this room
bool chimeComm::UnsubscribeRoom(char *roomUrl, char *userID)
{
	strcpy(command, roomUrl);
	AppendToken(command, userID);

	//SendFunction(c_unsubscribeRoom, command);
	return true;
}

//Disconnect user from CHIME server
bool chimeComm::Disconnect(char *userID)
{
	strcpy(command, userID);
	//SendFunction(c_disconnect, command);
	return true;
}