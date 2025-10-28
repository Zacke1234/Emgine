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

class MessageQueue : public Message
{
private:
	std::vector<Message*> messageQueue; 

public:
	void Enqueue(Message* message)  {
		messageQueue.push_back(message);
	}
	void Dequeue(Message* message) {
		messageQueue.erase(std::remove(messageQueue.begin(), messageQueue.end(), message), messageQueue.end());
	}
};
