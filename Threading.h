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
private:
	void Run();
	std::thread thread1;
	std::mutex mtx1;
	bool running = false;
	
};

class Thread : public Threading {

public:
	void DoWork(float deltatime);
	MeshManager* myMeshManager;
	std::thread thread2;
	std::mutex mtx2;
};

