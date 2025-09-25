#include "Threading.h"
#include <chrono>

Threading::Threading() :
	thread1(&Threading::Run, this)
{
	//Thread t1(Run);
	//float deltatime;
	
}

void Threading::Run()
{
	mutexRun.lock();
	//std::cout << "hello threading" << std::endl;
	running = true;
	auto lastTime = std::chrono::steady_clock::now();
	while (running)
	{

		const std::chrono::duration<double, std::milli> deltaTP{ std::chrono::steady_clock::now() - lastTime };
		const auto deltaMs = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTP);
		float deltatime = deltaTP.count() / 1000;
		DoWork(deltatime);

		//std::thread t1(void DoWork(float dt));
		//std::thread thread1(&DoWork, deltatime);
		//std::thread t3(&Threading::DoWork, deltatime);
		//std::thread t4(&DoWork);
		
		//t1.join(deltatime);
		

		std::this_thread::sleep_for(std::chrono::milliseconds(SleepFor));

		//t4.join();
		//thread1.join();
	}
	mutexRun.unlock();
}

float lastFrame = 0.0f;
Physics* Phys = new Physics();
void Thread::DoWork(float deltatime)
{
	
	if (Phys->TimeTicking)
	{
		double currentFrame = glfwGetTime();
		deltatime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
	Phys->Simulate(deltatime);
	//mutexDoWork.lock();
	//
	//std::unique_lock lock{ mutex };
	//std::cout << "hello DoWork" << std::endl;
	std::cout << "Started thread id=" << std::this_thread::get_id() << std::endl;
	  //thread2(*myMeshManager->myObjLoader);
	//
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	//mutexDoWork.unlock();
}
