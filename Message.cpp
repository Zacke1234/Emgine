#include "Message.h"
#include <iostream>
using namespace std;


Message::~Message()
{
	if (type == MessageType::String)
	{
		delete data.msg;
	}
}

std::string Message::GetStringData()
{
	if (type == MessageType::String)
	{
		return *data.msg;

	}
	return std::string();
}

float Message::GetFloatData()
{
	if (type == MessageType::FloatMessage)
	{
		return data.FloatMsg;
	}
	return 0.0f;
}


Message::MessageType Message::GetMessageType()
{
	return type;
}

Message::Message(std::string msg)
{
	
	type = MessageType::String;
	data.msg = new std::string(msg);
	

}


//Message::MessageData::MessageData()
//{
//
//}


void MyManager::ProcessMessage(Message* message)
{
	const string& msg = message->GetStringData();
	
	switch (message->GetMessageType())
	{
	case Message::MessageType::String:
		if (msg == "ObjLoaderStart") {
			std::cout << msg << endl;
		}
		else if (msg == "ObjLoaderStop")
		{
			std::cout << msg << endl;
		}
		break;

		
		     
	}

	
}

void MessageQueueClass::QueueMessage(Message* message)
{
	messages.push(message);
}

void MessageQueueClass::ProcessMessages()
{
	while (messages.size())
	{
		Message* message = messages.front();
		messages.pop();
		ProcessMessage(message);
		delete message;
	}
}

void MessageQueueClass::ProcessMessage(Message* message)
{
	
}

