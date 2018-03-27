#include "Events.h"
#include <mutex>
#include <map>
#include <vector>
#include <deque>
#include "TaskQueue.h"


static std::mutex _mtx;
static std::map<std::string, std::vector<App::Events::Handler>> _handlers;
static std::deque<App::Events::_QueueGroup*> _toBeQueued;


void App::Events::On(const std::string & event, Handler h)
{
	std::lock_guard<std::mutex> lock(_mtx);
	_handlers[event].push_back(h);
}


void doEvent(App::Object o)
{
	App::Events::Handler handler = *((App::Events::Handler*)o.get("handler"));
	App::Object obj = o.getobject("object");
	handler(obj);
}


void sendToHandlers(App::Object o)
{
	std::string event = o.getstring("event");
	if (event.size() == 0) return;

	std::lock_guard<std::mutex> lock(_mtx);
	if (_handlers.find(event) != _handlers.end())
	{
		for (App::Events::Handler &handler : _handlers[event])
		{
			App::Object nOBJ;
			nOBJ.set("handler", &handler, [](void *d) {return d; }, [](void*) {});
			nOBJ.setobject("object", o.getobject("object"));
			App::TaskQueue::Add(doEvent, nOBJ);
		}
	}
}


void App::Events::Send(const std::string & event, Object o)
{
	App::Object nOBJ;
	nOBJ.setstring("event", event);
	nOBJ.setobject("object", o);
	App::TaskQueue::Add(sendToHandlers, nOBJ);
}


void App::Events::SendIn(Time t, const std::string & event, Object o)
{
	Time atTime;
	atTime += t;
	_QueueGroup *q = new _QueueGroup(event, atTime, o);
	std::lock_guard<std::mutex> lock(_mtx);
	_toBeQueued.push_back(q);
}


void App::Events::SendAt(Time t, const std::string & event, Object o)
{
	_QueueGroup *q = new _QueueGroup(event, t, o);
	std::lock_guard<std::mutex> lock(_mtx);
	_toBeQueued.push_back(q);
}


void App::Events::__UPDATE()
{
	Time start;
	std::lock_guard<std::mutex> lock(_mtx);
	for (_QueueGroup *q : _toBeQueued)
	{
		// if this event is ready
		if (q->time <= start)
			Send(q->event, q->obj);
	}
}


App::Events::_QueueGroup::_QueueGroup(const std::string &eventname, Time atTime, Object o) :
    time(atTime), event(eventname), obj(o)
{}


App::Events::_QueueGroup::~_QueueGroup()
{}
