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
	virtual void DoWork(float deltatime) = 0;
	int SleepFor = 10;
	std::thread thread1;
private:
	void Run();
	
	
	bool running = false;
protected:
	std::mutex mutexRun;
	std::mutex mutexDoWork;
};

class Thread : public Threading {

public:
	void DoWork(float deltatime);
	MeshManager* myMeshManager;
	std::thread thread2;
};

