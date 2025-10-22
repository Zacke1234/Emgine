#pragma once
#include "Observer.h"
class DisplayMessage : public Observer
{
public:


	void Update(std::string message_from_subject) override
	{
		std::cout << "Message to: " << message_from_subject << "\n";
	}

};

