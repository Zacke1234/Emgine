#pragma once
#include <string>
#include "Collider.h"
#include <glm.hpp>
#include <vector>
#include <list>
#include <queue>
#include "iostream"
#include "Observer.h"
#include "MeshManager.h"
#include "MeshLoader.h"



//// Mediator pattern
//
//namespace std {};
//
//struct message {
//
//	int operator()()
//	{
//		
//	}
//};
//
//class MyBaseManager; // Basecomponent
//
class Message : public Subject
{
public:
	Message();

private:
	std::vector<Observer*> observers;
	std::string message;

public:
	void Attach(Observer* observer) override {
		observers.push_back(observer);

	}
	void Detach(Observer* observer) override {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}
	void Notify() override {
		for (Observer* observer : observers)
		{
			observer->Update(message);
		}
	}
	void setMessage(std::string message) {
		this->message = message;
		Notify();
	}

};



/*void AttachMesh(MeshManager* meshManager) override {
	observers.push_back((Observer*)meshManager);
}
void AttachObjLoader(ObjLoader* objload) override {
	observers.push_back((Observer*)objload);
}*/
	
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

//
//class MyBaseManager { // Basecomponent
//	protected:
//		Message* message; // Mediator
//
//	public:
//		MyBaseManager(Message* m = nullptr) : message(m) {} // Basecomponent Mediator to nullptr
//		void setMessage(Message* m);
//
//
//	//void ProcessMessage(Message* message);
//};
//
//class MessageQueueComponent1 : public MyBaseManager { // Component1 : BaseComponent
//public:
//	std::vector<std::string> MessageList;
//	/*std::string test;
//	MessageList.push_back(test);
//	MessageList.pop_back();*/
//	void PerformMessage1();
//	
//	void PerformMessage2();
//
//
//
//	/*void QueueMessage(Message* message);
//
//	void ProcessMessages();
//	void ProcessMessage(Message* message); 
//
//	std::queue<Message*> messages;*/
//};
//
//class MessageQueueComponent2 : public MyBaseManager { // Component2 : BaseComponent
//public:
//	void PerformMessage3();
//	
//	void PerformMessage4();
//};
//
//class ConcreteMessage : public Message { // ConcreteMediator : Mediator
//	MessageQueueComponent1* comp1;
//	MessageQueueComponent2* comp2;
//public:
//	ConcreteMessage(MessageQueueComponent1* c1, MessageQueueComponent2* c2) : comp1(c1), comp2(c2){
//		comp1->setMessage(this);
//		comp2->setMessage(this);
//	}
//	//void Notify(MyBaseManager* sender, std::string event) const override;
//};
//
//class ThreadingMessage : public Message {
//public:
//	void SendMessage();
//};
//
//class OBJLoaderMessage : public Message {
//public:
//	void SendMessage();
//};
//
//class RaycastMessage : public Message {
//public:
//	void SendMessage();
//	//RaycastMessage() : Message(MessageType::Raycast){}
//	//glm::vec3 startPos;
//};
//
//
