#pragma once

using CallbackJob = function<void()>;

class Job
{
public:
	Job(CallbackJob&& callback) : m_callback(move(callback))
	{
	}

	template<typename T, typename Ret, typename... Args>
	Job(shared_ptr<T> owner, Ret(T::* memFunc)(Args...), Args&&... args)
	{
		m_callback = [owner, memFunc, args...]()
			{
				(owner.get()->*memFunc)(args...);
			};
	}

	void Execute()
	{
		m_callback();
	}

private:
	CallbackJob m_callback;
};

class JobSerializer : public enable_shared_from_this<JobSerializer>
{
public:
	void PushJob(CallbackJob&& callback);
	template<typename T, typename Ret, typename... Args>
	void PushJob(Ret(T::* memFunc)(Args...), Args... args);

	void TimerPushJob(unsigned long long tickAfter, CallbackJob&& callback);
	template<typename T, typename Ret, typename... Args>
	void TimerPushJob(unsigned long long tickAfter, Ret(T::* memFunc)(Args...), Args... args);

	void FlushJob();
	void Push(shared_ptr<Job> job);

private:
	concurrent_queue<shared_ptr<Job>> m_jobs;
	atomic<int> m_jobCount = 0;
};

struct JobData
{
	JobData() = default;
	JobData(unsigned long long executeTick, weak_ptr<JobSerializer> owner, shared_ptr<Job> job) : executeTick(executeTick), owner(owner), job(job)
	{
	}

	bool operator<(const JobData& other) const
	{
		return executeTick < other.executeTick;
	}

	unsigned long long executeTick = 0;
	weak_ptr<JobSerializer> owner;
	shared_ptr<Job> job;
};

class JobTimer
{
public:
	void Reserve(unsigned long long executeTick, weak_ptr<JobSerializer> owner, shared_ptr<Job> job);
	void Distribute(unsigned long long now);
	void Clear();

private:
	concurrent_priority_queue<JobData> m_datas;
};