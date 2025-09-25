#pragma once
#include <string>
#include "Collider.h"
#include <glm.hpp>
#include <vector>
#include <list>
#include <queue>
#include "iostream"
//using namespace std;

//struct mesg_buffer { // for message queue
//	long mesg_type;
//	char mesg_text[100];
//} message;

class MyBaseManager; // Basecomponent

class Message // Mediator
{

public:
	Message();
	virtual void Notify(MyBaseManager* sender, std::string event) const = 0;
	
	
	/*virtual enum class MessageType {
		String,
		FloatMessage,
		Component
	};

	

	Message(std::string msg);
	~Message();
	
	std::string GetStringData();
	float GetFloatData();
	MessageType GetMessageType();*/
	
//private:
//	
//	MeshManager* myMeshManager;
//	ObjLoader* myObjLoader;
//
//	MessageType type;
//	union MessageData
//	{
//		
//		std::string* msg;
//
//		float FloatMsg;
//	};
//	MessageData data;
};

class MyBaseManager { // Basecomponent
	protected:
		Message* message; // Mediator

	public:
		MyBaseManager(Message* m = nullptr) : message(m) {} // Basecomponent Mediator to nullptr
		void setMessage(Message* m) { // set mediator
			message = m;
		}


	//void ProcessMessage(Message* message);
};

class MessageQueueComponent1 : public MyBaseManager { // Component1 : BaseComponent
public:
	std::vector<std::string> MessageList;
	/*std::string test;
	MessageList.push_back(test);
	MessageList.pop_back();*/
	void PerformMessage1()
	{
		std::cout << "Component 1 peforms Message 1" << "\n";
		message->Notify(this, "Message 1");
	}
	void PerformMessage2()
	{
		std::cout << "Component 1 perform Message 2" << "\n";
		message->Notify(this, "Message 2");
	}



	/*void QueueMessage(Message* message);

	void ProcessMessages();
	void ProcessMessage(Message* message);

	std::queue<Message*> messages;*/
};

class MessageQueueComponent2 : public MyBaseManager { // Component2 : BaseComponent
public:
	void PerformMessage3() {
		std::cout << "Component 2 perform Message 3" << "\n";
		message->Notify(this, "Message 3");
	}
	
	void PerformMessage4()
	{
		std::cout << "Component 2 perform Message 4" << "\n";
		message->Notify(this, "Message 4"); 
	}
};

class ConcreteMessage : public Message { // ConcreteMediator : Mediator
	MessageQueueComponent1* comp1;
	MessageQueueComponent2* comp2;
public:
	ConcreteMessage(MessageQueueComponent1* c1, MessageQueueComponent2* c2) : comp1(c1), comp2(c2){
		comp1->setMessage(this);
		comp2->setMessage(this);
	}
	void Notify(MyBaseManager* sender, std::string event) const override {
		if (event == "Message 1"){
			std::cout << "Message reacts on Message 1 and triggers following operations: " << "\n";
			comp2->PerformMessage3();
		}
		if (event == "Message 4") {
			std::cout << "Message reacts on Message 4 and triggers following operations: " << "\n";
			comp1->PerformMessage2();
			comp2->PerformMessage3();
		}
	}
};

class RaycastMessage : public Message {
public:
	//RaycastMessage() : Message(MessageType::Raycast){}
	//glm::vec3 startPos;
};


