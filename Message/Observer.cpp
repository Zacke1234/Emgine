#include "Observer.h"
#include <iostream>
#include <algorithm>
#include <list>
#include <string>

// i don't think I will ever understand things like override and singletons and stuff like that


//class MessageSubject : public Subject {
//	std::vector<Observer*> observers;
//	std::string message;
//};


void Subject::Attach(Observer *observer) {
	observers.push_back(observer);
	
}

void Subject::Detach(Observer* observer){
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::Notify()
{
	for (Observer* observer : observers)
	{
		observer->Update(message);
	}
}

//void SetMessage(std::string setMessage)
//{
//	
//}

void Observer::Update(const std::string& message_from_subject)
{
}
