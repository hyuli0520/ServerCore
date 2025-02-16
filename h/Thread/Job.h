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
		m_callback;
	}

private:
	CallbackJob m_callback;
};

class JobSerializer : public enable_shared_from_this<JobSerializer>
{
public:
	void PushJob(CallbackJob&& callback)
	{
		Push(MakeShared<Job>(move(callback)));
	}

	template<typename T, typename Ret, typename... Args>
	void PushJob(Ret(T::* memFunc)(Args...), Args... args)
	{
		auto owner = static_pointer_cast<T>(shared_from_this());
		Push(MakeShared<Job>(owner, memFunc, forward<Args>(args)...));
	}

	void FlushJob();

private:
	void Push(shared_ptr<Job>&& job);

private:
	concurrent_queue<shared_ptr<Job>> m_jobs;
	atomic<int> m_jobCount = 0;
};