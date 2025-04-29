#pragma once
#include <string>
#include <glm.hpp>

class Message
{

public:

	enum class MessageType {
		String, // basic type
		Mouse,
		FloatMessage,
		Raycast,
		Collision
	};

	MessageType type;
	
	std::string msg;
	Message(MessageType type, std::string msg);
	virtual ~Message();

	 

private:

};

class RaycastMessage : public Message {
public:
	//RaycastMessage() : Message(MessageType::Raycast){}
	//glm::vec3 startPos;
};
