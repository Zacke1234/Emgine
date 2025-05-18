#include "Message.h"
#include <iostream>
using namespace std;


Message::Message(MessageType type,std::string msg) : type(type), msg(msg)
{
	msg = "";
	FloatMsg = 0.0f;
	type = MessageType::String;
	
}

Message::~Message()
{
	delete &msg;
	
}

void MyManager::ProcessMessage(Message* message)
{
	string* msg = &message->msg;
	switch (message->type)
	{
	case Message::MessageType::String:
		break;
		
	}
}
