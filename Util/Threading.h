#include <thread>
#include <mutex>
#include <iostream>
#include "Physics.h"
#include "MeshManager.h"
#pragma once
class Threading
{
public:
	Threading();
	virtual void DoWork(Observer* observer, Message* myMessage) = 0;
	int SleepFor = 10;
	std::thread thread1; 
private:
	void Run();
	// Which manager? MeshManager, ObjManager? Or maybe something else?
	Observer *observer;
	Message *myMessage;
	bool running = false;
protected:
	std::mutex mutexRun;
	std::mutex mutexDoWork;
};

class Thread : public Threading {

public:
	void DoWork(Observer* observer, Message* myMessage) override;
	
	std::thread thread2;
};

