#pragma once
#include <string>
#include "Collider.h"
#include <glm.hpp>
#include <vector>
#include <list>
#include <queue>

//struct mesg_buffer { // for message queue
//	long mesg_type;
//	char mesg_text[100];
//} message;

class Message
{

public:
	
	
	
	enum class MessageType {
		String, 
		Mouse, 
		FloatMessage,
		Raycast,
	};

	

	Message(std::string msg);
	~Message();
	
	std::string GetStringData();
	float GetFloatData();
	MessageType GetMessageType();
	
private:
	

	MessageType type;
	union MessageData
	{
		
		std::string* msg;

		float FloatMsg;
	};
	MessageData data;
};

class MyManager {

public:
	void ProcessMessage(Message* message);
};

class MessageQueueClass {
public:

	void QueueMessage(Message* message);

	void ProcessMessages();
	void ProcessMessage(Message* message);

	std::queue<Message*> messages;
};

class RaycastMessage : public Message {
public:
	//RaycastMessage() : Message(MessageType::Raycast){}
	//glm::vec3 startPos;
};


