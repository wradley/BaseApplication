#include <mutex>
#include <deque>
#include <tuple>
#include <thread>
#include "TaskQueue.h"

#define MAX_QUEUE_SIZE 100

static std::atomic_bool _running;
static std::mutex _mtx;
static std::deque<App::TaskQueue::Pair*> *_queue;


namespace
{
	void DoTask()
	{
		bool hasData = false;
		App::TaskQueue::Pair *p = nullptr;
		{
			std::unique_lock<std::mutex> lock(_mtx);
			if (_queue->size() > 0)
			{
				p = _queue->back();
				_queue->pop_back();
				hasData = true;
			}
		}

		// if there is work to do
		if (hasData)
		{
			App::TaskQueue::Task &task = p->task;
			App::Object &param = p->param;

			// do the task
			task(param);
			p->status->store(true);
			delete p;
		}
		
		// if there is no work to do, sleep
		else std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}


App::TaskQueue::TaskStatus App::TaskQueue::Add(Task t, const Object & param)
{
	App::TaskQueue::Pair *p = new Pair(t, param);
	TaskStatus ret = p->status;
	bool done = false;
	while (!done)
	{
		{
			std::unique_lock<std::mutex> lock(_mtx);
			if (_queue->size() < MAX_QUEUE_SIZE)
			{
				_queue->push_front(p);
				done = true;
			}
		}
		
		if (!done) std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return ret;
}


void App::TaskQueue::Wait(TaskStatus task)
{
	while (task->load() == false)
		DoTask();
}


void App::TaskQueue::__START()
{
	_queue = new std::deque<App::TaskQueue::Pair*>;
	_running.store(true);
}


void App::TaskQueue::__INIT_WORKER()
{
	while (_running.load() == true)
		DoTask();
}


void App::TaskQueue::__STOP()
{
	_running.store(false);
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	_queue->clear();
	delete _queue;
}


App::TaskQueue::Pair::Pair(App::TaskQueue::Task t, const App::Object &p) : task(t), param(p), status(new std::atomic_bool)
{
	status->store(false);
}


App::TaskQueue::Pair::~Pair()
{}
