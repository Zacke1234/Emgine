#pragma once
// observer pattern
#include <string>
#include <list>
#include <iostream>
#include <vector>
// Mesh manager and objectloaders will both be subscribers to this publisher 
// for the message output that is needed 


 
class Observer
{
public:
	virtual ~Observer() {};
	void Update(const std::string& message_from_subject);
};

class Subject {
public:
	std::vector<Observer*> observers;
	std::string message;
	void Attach(Observer *observer);
	void Detach(Observer *observer);
	void Notify();

	~Subject() {};
}; 

class Output : public Observer {
public:
	void update(std::string classMessage) {
		std::cout << "The " << classMessage << "class Loaded in" << std::endl;
	}
};