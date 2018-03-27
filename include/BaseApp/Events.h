#pragma once
#include <string>
#include "Object.h"
#include "AppTime.h"

namespace App
{
	namespace Events
	{
		typedef void(*Handler) (Object);

		void On(const std::string &event, Handler h);
		void Send(const std::string &event, Object o);

		// timed events
		void SendIn(Time t, const std::string &event, Object o);
		void SendAt(Time t, const std::string &event, Object o);

		// call once per frame to fire off timed events
		void __UPDATE();


		struct _QueueGroup
		{
			_QueueGroup(const std::string &eventname, Time atTime, Object o);
			~_QueueGroup();

			Time time;
			std::string event;
			Object obj;
		};
	}
}

