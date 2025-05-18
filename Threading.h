#include <thread>
#include <mutex>
#include "Physics.h"
#include "MeshManager.h"
#pragma once
class Threading
{
public:
	Threading();
	virtual void DoWork(float deltatime) = 0;
private:
	void Run();
	std::thread thread1;
	std::mutex mtx;
	bool running = false;
};

