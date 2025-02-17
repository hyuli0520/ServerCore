#pragma once

class Engine
{
public:
	Engine();
	~Engine();

	inline ThreadManager* GetThreadManager() { return m_threadManager; }
	inline JobTimer* GetJobTimer() { return m_jobTimer; }

private:
	ThreadManager* m_threadManager = nullptr;
	JobTimer* m_jobTimer = nullptr;
};

extern class Engine* GEngine;