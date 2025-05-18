#include "Threading.h"
#include <chrono>

Threading::Threading() :
	thread1(&Threading::Run, this)
{
	
}

void Threading::Run()
{
	running = true;
	auto lastTime = std::chrono::steady_clock::now();
	while (running)
	{ 
		
		const std::chrono::duration<double, std::milli> deltaTP{std::chrono::steady_clock::now() - lastTime};
		const auto deltaMs = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTP);
		float deltatime = deltaTP.count() / 1000;
		DoWork(deltatime);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	
	thread1.join();
}

