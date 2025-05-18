#pragma once
#include <string>
#include "Collider.h"
#include <glm.hpp>

class Message
{

public:


	enum class MessageType {
		String, 
		Mouse, 
		FloatMessage,
		Raycast,
	};

	std::string msg;
	 
	float FloatMsg;

	Message(MessageType type,std::string msg);
	MessageType type;
	virtual ~Message();
private:

};

class MyManager {

public:
	void ProcessMessage(Message* message);
};

class RaycastMessage : public Message {
public:
	//RaycastMessage() : Message(MessageType::Raycast){}
	//glm::vec3 startPos;
};
