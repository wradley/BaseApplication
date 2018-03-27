#pragma once
#include <memory>
#include <atomic>
#include "Object.h"

namespace App
{
	namespace TaskQueue
	{
		typedef std::shared_ptr<std::atomic_bool> TaskStatus;
		typedef void(*Task) (Object);

		TaskStatus Add(Task, const Object &param);
		void Wait(TaskStatus taskstatus);

		void __START();
		void __INIT_WORKER();
		void __STOP();

		struct Pair
		{
			Pair(App::TaskQueue::Task t, const App::Object &);
			Pair(const Pair &p) = delete;
			Pair(Pair &&p) = delete;
			~Pair();

			Task task;
			Object param;
			TaskStatus status;
		};
	}
}
